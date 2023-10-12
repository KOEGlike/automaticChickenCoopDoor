#include "ChickenDoor.hpp"


ChickenDoor::ChickenDoor(DisplayUiConfig *displayUiConfig, MotorConfig *motorConfig):
moveTimes{12,12,12,12},
interface{getTimes, updateTimes, updateCurrentTime, getCurrentTime, getMotor},
displayUI{&interface,displayUiConfig},
motorInterface{getMotorState, setMotorState, getMotorCalibrationState, setMotorCalibrationState, settingStateClosed, settingStateOpen, finishedCalibrating},
motor{motorConfig, &motorInterface}
{
 // Serial.println("ChickenDoor constructor"); 
}


void ChickenDoor::begin()
{
  displayUI.begin();
  motor.begin();
}
