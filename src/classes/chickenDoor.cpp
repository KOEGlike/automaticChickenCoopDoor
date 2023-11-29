#include "ChickenDoor.hpp"


ChickenDoor::ChickenDoor(DisplayUiConfig *displayUiConfig, MotorConfig *motorConfig):
moveTimes{12,12,12,12},
interface{getTimes, updateTimes, updateCurrentTime, getCurrentTime, getMotor},
displayUI{&interface,displayUiConfig},
motorInterface{getMotorStatePtr, settingStateClosed, settingStateOpen, finishedCalibrating},
motor{motorConfig, &motorInterface}
{
}


void ChickenDoor::begin()
{
  pref.begin("ChickenDoor", false);
  displayUI.begin();
  motor.begin();
}



void ChickenDoor::saveMoveTimesToMemory(MoveTimes moveTimes)
{
  pref.putULong("openTime", makeTime(moveTimes.openTime));
  pref.putULong("closeTime", makeTime(moveTimes.closeTime));
}

void ChickenDoor::loadMoveTimesFromMemory()
{
  tmElements_t openTime, coloseTime;
  breakTime( pref.getULong("openTime", 0),openTime);
  breakTime( pref.getULong("closeTime", 0),coloseTime);
  moveTimes=MoveTimes{openTime, coloseTime};
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