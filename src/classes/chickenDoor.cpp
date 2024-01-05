#include "ChickenDoor.hpp"
#include "memory_manager.hpp"

ChickenDoor::ChickenDoor(DisplayUiConfig *displayUiConfig, MotorConfig *motorConfig, WiFiConfig* wifiConfig):
WiFiHandler{wifiConfig},
TimesManager{&WiFiHandler, &MemoryManager},
motor{&MemoryManager,motorConfig},
displayUI{&TimesManager,&motor ,displayUiConfig}
{
}


void ChickenDoor::begin()
{
  WiFiHandler.begin();
  MemoryManager.begin();
  setTime(SECS_PER_YEAR);
  const int idOpen=Alarm.alarmRepeat(1,[&]() {motor.changeState(1); Serial.println("open");});
  const int idClose=Alarm.alarmRepeat(1,[&]() {motor.changeState(0); Serial.println("close"); if(TimesManager.getTimeState().sunsetMode) TimesManager.updateMoveTimes(WiFiHandler.sunsetTimes());});
  TimesManager.begin(idOpen, idClose);
  displayUI.begin();
  motor.begin();
  Async.registerCallback(100, -1, [&](){Alarm.serviceAlarms();});
}