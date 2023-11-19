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
  displayUI.begin();
  motor.begin();
}
