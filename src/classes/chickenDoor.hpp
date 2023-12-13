#pragma once

#include "physical_interface/display_UI.hpp"
#include "interfaces.hpp"
#include "motor.hpp"
#include <TimeLib.h>
#include <functional>
#include <Arduino.h>
#include <TimeAlarms.h>
#include <Preferences.h>
#include <TimeAlarms.h>
#include "WiFiHandler.hpp"
#include "times_manager.hpp"

class Motor;
class MoveTimes;
class DisplayUiConfig;
class MotorConfig;
class MotorState;
class MotorCalibrator;
class DisplayUI;

class ChickenDoor{
  

  public:
    friend class Motor;

    ChickenDoor(DisplayUiConfig *displayUiConfig, MotorConfig *motorConfig);

    void changeDoorState(float percentage);
    float getDoorOpennessInPercentage();
    MotorState getMotorState();
    TimesManager timesManager;
    time_t syncFunc();
    void begin();
    Motor motor;
    MotorCalibrator calibrator;
  protected:
   
    TimeState timeState;
    DisplayUI displayUI;

    
    
};

