#include "chicken_door.hpp"
#include "memory_manager.hpp"
#include "physical_interface/button.hpp"

#include "chicken_door.hpp"
#include "memory_manager.hpp"
#include "physical_interface/button.hpp"

ChickenDoor::ChickenDoor(std::shared_ptr<DisplayUiConfig> displayUiConfig, std::shared_ptr<MotorConfig> motorConfig, std::shared_ptr<WiFiConfig> wifiConfig): 
  displayUiConfig(displayUiConfig),
  motorConfig(motorConfig),
  wifiConfig(wifiConfig),
  memoryManager(std::make_shared<MemoryManager>()),
  wifiHandler(std::make_shared<WiFiHandler>(wifiConfig)), 
  timesManager(std::make_shared<TimesManager>(wifiHandler, memoryManager)),
  motor(std::make_shared<Motor>(memoryManager, motorConfig)), 
  sleepHandler(std::make_shared<Esp32C3SleepHandler>(timesManager, motor)),
  displayUI(timesManager, motor, displayUiConfig, sleepHandler)
{}

void ChickenDoor::begin()
{
  Serial.print("ssid: ");
  Serial.println(wifiConfig->ssid);
  wifiHandler->begin();
  memoryManager->begin();
  
  setTime(SECS_PER_YEAR);
  const int idOpen = Alarm.alarmRepeat(1, [&]() { motor->changeState(1); Serial.println("open"); });
  const int idClose = Alarm.alarmRepeat(1, [&]() { motor->changeState(0); Serial.println("close"); if (timesManager->getTimeState().sunsetMode) timesManager->updateMoveTimes(wifiHandler->sunsetTimes()); });
  timesManager->begin(idOpen, idClose);
  motor->begin();
  sleepHandler->begin();
  displayUI.begin();
  
  Async.registerCallback("service alarms", 1 * 1000, -1, [&]() { Alarm.serviceAlarms(); });
  Async.registerCallback(
    "sleep check",
    sleepCheckIntervalSec * 1000, 
    -1, 
    [&]() {
      if (ButtonManager.timeFromLastPress() >= minutesToSleep * minutesToSleep * 1000) 
        sleepHandler->sleepUntilNextAction(); 
      Serial.println("sleep check");
    }
  );
}