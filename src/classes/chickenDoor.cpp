#include "ChickenDoor.hpp"


ChickenDoor::ChickenDoor(DisplayUiConfig *displayUiConfig, MotorConfig *motorConfig):
moveTimes{12,12,12,12},
interface{getTimes, updateTimes, updateCurrentTime, getCurrentTime, getMotor},
displayUI{&interface,displayUiConfig},
motorInterface{getMotorStatePtr, updateMotorState ,settingStateClosed, settingStateOpen, finishedCalibrating},
motor{motorConfig, &motorInterface}
{
}


void ChickenDoor::begin()
{
  pref.begin("ChickenDoor", false);
  displayUI.begin();
  motor.begin();
  loadMotorStateFromMemory();
  loadMoveTimesFromMemory();
  if(sunsetMode)
    moveTimes=WiFiHandler.sunsetTimes();
}

time_t ChickenDoor::syncFunc()
{
  if(autoTime)return makeTime(WiFiHandler.ipTime());
  tmElements_t tm=WiFiHandler.UTCTime();
  tm.Hour+=offset;
  return makeTime(tm);
}

void ChickenDoor::saveMoveTimesToMemory(MoveTimes moveTimes)
{
  pref.putULong("openTime", makeTime(moveTimes.openTime));
  pref.putULong("closeTime", makeTime(moveTimes.closeTime));
  
  if(moveTimes.openTime.Hour==0 && moveTimes.openTime.Minute==0 && moveTimes.closeTime.Hour&&moveTimes.closeTime.Minute)
  { 
    pref.putBool("sunsetMode", true);
    sunsetMode=true;
  }  
  else  
  {
    pref.putBool("sunsetMode", false);
    sunsetMode=false;
  }
}

void ChickenDoor::loadMoveTimesFromMemory()
{
  tmElements_t openTime, coloseTime;
  breakTime( pref.getULong("openTime", 0),openTime);
  breakTime( pref.getULong("closeTime", 0),coloseTime);
  moveTimes=MoveTimes{openTime, coloseTime};
  
  sunsetMode=pref.getBool("sunsetMode", true);
  autoTime=pref.getBool("autoTime", true);
  offset=pref.getInt("offset", 0);
}

void ChickenDoor::saveMotorStateToMemory(MotorState motorState)
{
  pref.putInt("bottomStep", motorState.calibrationState.bottomStep);
  pref.putInt("topStep", motorState.calibrationState.topStep);
  pref.putInt("currentStep", motorState.currentStep);
}

void ChickenDoor::loadMotorStateFromMemory()
{
  motorState=MotorState{MotorCalibrationState{pref.getInt("bottomStep", 0), pref.getInt("topStep", 0)},pref.getInt("currentStep", 0)};
}