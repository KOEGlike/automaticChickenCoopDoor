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


class ChickenDoor{
  public:
    friend class Motor;
    ChickenDoor(DisplayUiConfig *displayUiConfig, MotorConfig *motorConfig, WiFiConfig *wifiConfig);
    void begin();
    Motor motor;
    WiFiHandler_t WiFiHandler;
    TimesManager_t TimesManager;
  protected:
    DisplayUI displayUI;
    MemoryManager_t MemoryManager;
};

