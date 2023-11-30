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
}



void ChickenDoor::saveMoveTimesToMemory(MoveTimes moveTimes)
{
  pref.putULong("openTime", makeTime(moveTimes.openTime));
  pref.putULong("closeTime", makeTime(moveTimes.closeTime));
  
  if(moveTimes.openTime.Hour==0 && moveTimes.openTime.Minute==0 && moveTimes.closeTime.Hour&&moveTimes.closeTime.Minute) 
    sunsetMode=true;
  else  
    sunsetMode=false;
}

void ChickenDoor::loadMoveTimesFromMemory()
{
  tmElements_t openTime, coloseTime;
  breakTime( pref.getULong("openTime", 0),openTime);
  breakTime( pref.getULong("closeTime", 0),coloseTime);
  moveTimes=MoveTimes{openTime, coloseTime};
  
  if(moveTimes.openTime.Hour==0 && moveTimes.openTime.Minute==0 && moveTimes.closeTime.Hour==0&&moveTimes.closeTime.Minute==0) 
    sunsetMode=true;
  else  
    sunsetMode=false;

  //print to serial all info in moveTimes
  Serial.println("openTime");
  Serial.println(moveTimes.openTime. Hour);
  Serial.println(moveTimes.openTime. Minute);
  Serial.println("closeTime");
  Serial.println(moveTimes.closeTime. Hour);
  Serial.println(moveTimes.closeTime. Minute);
  Serial.println("sunsetMode");
  Serial.println(sunsetMode);
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
  //print to serial all info in motorState
  Serial.println("bottomStep");
  Serial.println(motorState.calibrationState.bottomStep);
  Serial.println("topStep");
  Serial.println(motorState.calibrationState.topStep);
  Serial.println("currentStep");
  Serial.println(motorState.currentStep);
}