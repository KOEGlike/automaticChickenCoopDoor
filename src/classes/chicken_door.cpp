#include "chicken_door.hpp"
#include "memory_manager.hpp"
#include "physical_interface/button.hpp"

ChickenDoor::ChickenDoor(DisplayUiConfig displayUiConfig, MotorConfig motorConfig, WiFiConfig wifiConfig): 
  displayUiConfig(std::make_shared<DisplayUiConfig>(displayUiConfig)), 
  motor(std::make_shared<Motor>(std::make_shared<MemoryManager>(),std::make_shared<MotorConfig>(motorConfig))), 
  wifiHandler(std::make_shared<WiFiHandler>(wifiConfig)), 
  timesManager(std::make_shared<TimesManager>()),
  sleepHandler(std::make_shared<Esp32C3SleepHandler>()),
  memoryManager(std::make_shared<MemoryManager>()),
  displayUI(this->timesManager,this->motor,this->displayUiConfig,this->sleepHandler)
{}


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