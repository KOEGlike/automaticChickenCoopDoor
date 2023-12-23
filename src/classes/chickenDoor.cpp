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
  displayUI.begin();
  motor.begin();
  WiFiHandler.begin();
  MemoryManager.begin();
  const int idOpen=Alarm.alarmRepeat(0,[&]() {motor.changeState(1);});
  const int idClose=Alarm.alarmRepeat(0,[&]() {motor.changeState(0); Serial.println("close"); if(TimesManager.getTimeState().sunsetMode) TimesManager.updateMoveTimes(WiFiHandler.sunsetTimes());});
  TimesManager.begin(idClose, idClose);
}