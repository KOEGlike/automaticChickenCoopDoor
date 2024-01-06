#include "chicken_door.hpp"
#include "memory_manager.hpp"
#include "physical_interface/button.hpp"

ChickenDoor::ChickenDoor(DisplayUiConfig *displayUiConfig, MotorConfig *motorConfig, WiFiConfig* wifiConfig):
wifiHandler{wifiConfig},
timesManager{&wifiHandler, &memoryManager},
motor{&memoryManager,motorConfig},
sleepHandler{&timesManager, displayUiConfig},
displayUI{&timesManager,&motor ,displayUiConfig, &sleepHandler}

{
  this->displayUiConfig=displayUiConfig;
  this->motorConfig=motorConfig;
  this->wifiConfig=wifiConfig;
}


void ChickenDoor::begin()
{
  wifiHandler.begin();
  memoryManager.begin();
  setTime(SECS_PER_YEAR);
  const int idOpen=Alarm.alarmRepeat(1,[&]() {motor.changeState(1); Serial.println("open");});
  const int idClose=Alarm.alarmRepeat(1,[&]() {motor.changeState(0); Serial.println("close"); if(timesManager.getTimeState().sunsetMode) timesManager.updateMoveTimes(wifiHandler.sunsetTimes());});
  timesManager.begin(idOpen, idClose);
  displayUI.begin();
  motor.begin();
  sleepHandler.begin();
  Async.registerCallback(1*1000, -1, [&](){Alarm.serviceAlarms();});
  Async.registerCallback(30*1000, -1, [&](){if(ButtonManager.timeFromLastPress()>=minutesToSleep*60*1000) sleepHandler.sleepUntilNextAction(); Serial.println("sleep check");});
}