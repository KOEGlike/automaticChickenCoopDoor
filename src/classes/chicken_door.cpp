#include "chicken_door.hpp"
#include "memory_manager.hpp"
#include "physical_interface/button.hpp"

#include "chicken_door.hpp"
#include "memory_manager.hpp"
#include "physical_interface/button.hpp"

ChickenDoor::ChickenDoor(std::shared_ptr<DisplayUiConfig> displayUiConfig, std::shared_ptr<MotorConfig> motorConfig, std::shared_ptr<WiFiConfig> wifiConfig): 
  wifiConfig(wifiConfig),
  motorConfig(motorConfig),
  displayUiConfig(displayUiConfig),
  displayUI(timesManager, motor, displayUiConfig, sleepHandler) // Initialize displayUI to nullptr first
{
  Serial.println("Initializing WiFiHandler...");
  wifiHandler = std::make_shared<WiFiHandler>(this->wifiConfig);
  Serial.println("WiFiHandler initialized.");

  Serial.println("Initializing MemoryManager...");
  memoryManager = std::make_shared<MemoryManager>();
  Serial.println("MemoryManager initialized.");

  Serial.println("Initializing TimesManager...");
  timesManager = std::make_shared<TimesManager>(this->wifiHandler, this->memoryManager);
  Serial.println("TimesManager initialized.");

  Serial.println("Initializing Motor...");
  motor = std::make_shared<Motor>(this->memoryManager, this->motorConfig);
  Serial.println("Motor initialized.");

  Serial.println("Initializing SleepHandler...");
  sleepHandler = std::make_shared<Esp32C3SleepHandler>(this->timesManager, this->motor);
  Serial.println("SleepHandler initialized.");

  Serial.println("Initializing DisplayUI...");
  displayUI = DisplayUI(this->timesManager, this->motor, this->displayUiConfig, this->sleepHandler);
  Serial.println("DisplayUI initialized.");
}

void ChickenDoor::begin()
{
  wifiHandler->begin();
  memoryManager->begin();
  
  setTime(SECS_PER_YEAR);
  const int idOpen=Alarm.alarmRepeat(1,[&]() {motor->changeState(1); Serial.println("open");});
  const int idClose=Alarm.alarmRepeat(1,[&]() {motor->changeState(0); Serial.println("close"); if(timesManager->getTimeState().sunsetMode) timesManager->updateMoveTimes(wifiHandler->sunsetTimes());});
  timesManager->begin(idOpen, idClose);
  
  displayUI.begin();
  motor->begin();
  sleepHandler->begin();

  
  
  Async.registerCallback(1*1000, -1, [&](){Alarm.serviceAlarms();});
  Async.registerCallback(sleepCheckIntervalSec*1000, -1, [&](){if(ButtonManager.timeFromLastPress()>=minutesToSleep*minutesToSleep*1000) sleepHandler->sleepUntilNextAction(); Serial.println("sleep check");});
}