#include "ChickenDoor.hpp"
#include "memory_manager.hpp"

ChickenDoor::ChickenDoor(DisplayUiConfig *displayUiConfig, MotorConfig *motorConfig):
motor{motorConfig},
displayUI{&motor ,displayUiConfig}
{
}


void ChickenDoor::begin()
{
  displayUI.begin();
  motor.begin();
  
  TimesManager.updateTimeSate(MemoryManager.loadTimeStateFromMemory());
  if(TimesManager.getTimeState().sunsetMode)
    TimesManager.getTimeState().moveTimes=WiFiHandler.sunsetTimes();
}

time_t ChickenDoor::syncFunc()
{
  if(TimesManager.getTimeState().autoTime)return makeTime(WiFiHandler.ipTime());
  tmElements_t tm=WiFiHandler.UTCTime();
  tm.Hour+=TimesManager.getTimeState().offset;
  return makeTime(tm);
}

void ChickenDoor::changeDoorState(float percentage)
{
   motor.changeState(percentage);
}



MotorState ChickenDoor::getMotorState()
{
  return motor.getMotorState();
}