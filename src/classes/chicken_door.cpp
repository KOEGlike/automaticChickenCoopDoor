#include "chicken_door.hpp"
#include "memory_manager.hpp"

ChickenDoor::ChickenDoor(DisplayUiConfig *displayUiConfig, MotorConfig *motorConfig, WiFiConfig* wifiConfig):
wifiHandler{wifiConfig},
timesManager{&wifiHandler, &MemoryManager},
motor{&MemoryManager,motorConfig},
displayUI{&timesManager,&motor ,displayUiConfig},
sleepHandler{&timesManager, displayUiConfig}
{
  this->displayUiConfig=displayUiConfig;
  this->motorConfig=motorConfig;
  this->wifiConfig=wifiConfig;
}


void ChickenDoor::begin()
{
  wifiHandler.begin();
  MemoryManager.begin();
  setTime(SECS_PER_YEAR);
  const int idOpen=Alarm.alarmRepeat(1,[&]() {motor.changeState(1); Serial.println("open");});
  const int idClose=Alarm.alarmRepeat(1,[&]() {motor.changeState(0); Serial.println("close"); if(timesManager.getTimeState().sunsetMode) timesManager.updateMoveTimes(wifiHandler.sunsetTimes());});
  timesManager.begin(idOpen, idClose);
  displayUI.begin();
  motor.begin();
  Async.registerCallback(100, -1, [&](){Alarm.serviceAlarms();});
}