#include "ChickenDoor.hpp"
#include "memory_manager.hpp"

ChickenDoor::ChickenDoor(DisplayUiConfig *displayUiConfig, MotorConfig *motorConfig):
timeState{MoveTimes{12,12,12,12}, true, true, 0},
motor{motorConfig},
calibrator{&motor},
timesManager{&timeState},
displayUI{&timesManager,&motor ,&calibrator,displayUiConfig}
{
}


void ChickenDoor::begin()
{
  displayUI.begin();
  motor.begin();
  
  timeState= MemoryManager.loadTimeStateFromMemory();
  if(timeState.sunsetMode)
    timeState.moveTimes=WiFiHandler.sunsetTimes();
}

time_t ChickenDoor::syncFunc()
{
  if(timeState.autoTime)return makeTime(WiFiHandler.ipTime());
  tmElements_t tm=WiFiHandler.UTCTime();
  tm.Hour+=timeState.offset;
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