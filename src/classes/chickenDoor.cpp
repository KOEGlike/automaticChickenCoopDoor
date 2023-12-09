#include "ChickenDoor.hpp"


ChickenDoor::ChickenDoor(DisplayUiConfig *displayUiConfig, MotorConfig *motorConfig):
moveTimes{12,12,12,12},
displayUI{this,displayUiConfig},
motor{this,motorConfig},
calibrator{&motor}
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

void ChickenDoor::saveMoveTimesToMemory()
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
  tmElements_t openTime, closeTime;
  breakTime( pref.getULong("openTime", 0),openTime);
  breakTime( pref.getULong("closeTime", 0),closeTime);
  moveTimes=MoveTimes{openTime, closeTime};
  
  sunsetMode=pref.getBool("sunsetMode", true);
  autoTime=pref.getBool("autoTime", true);
  offset=pref.getInt("offset", 0);
}

void ChickenDoor::saveMotorStateToMemory()
{
  pref.putInt("bottomStep", motorState.calibrationState.bottomStep);
  pref.putInt("topStep", motorState.calibrationState.topStep);
  pref.putInt("currentStep", motorState.currentStep);
}

void ChickenDoor::loadMotorStateFromMemory()
{
  motorState=MotorState{MotorCalibrationState{pref.getInt("bottomStep", 0), pref.getInt("topStep", 0)},pref.getInt("currentStep", 0)};
}

void ChickenDoor::changeDoorState(float percentage)
{
   motor.changeState(percentage);
}

void ChickenDoor::updateMoveTimes(MoveTimes moveTimes)
{
  this->moveTimes=moveTimes;
  saveMoveTimesToMemory();
}

void ChickenDoor::updateCurrentTime(tmElements_t time)
{
  setTime(makeTime(time)); 
  if(time.Hour==0&&time.Minute==0)
  {
    pref.putBool("autoTime", true);
    autoTime=true;
   }
  else
  {
    autoTime=false;
    offset=time.Hour-WiFiHandler.UTCTime().Hour;
    pref.putBool("autoTime", false);
    pref.putInt("offset", offset);
  }
}

MoveTimes ChickenDoor::getMoveTimes()
{
  return moveTimes;
}


MotorState ChickenDoor::getMotorState()
{
  return motorState;
}

bool ChickenDoor::getSunsetMode()
{
  return sunsetMode;
}

bool ChickenDoor::getAutoTime()
{
  return autoTime;
}

void ChickenDoor::updateMotorState(MotorState state)
{
  motorState=state;
  saveMotorStateToMemory();
}

void ChickenDoor::addToCurrentStep(int step)
{
  motorState.currentStep+=step;
  pref.putInt("currentStep", motorState.currentStep);
}