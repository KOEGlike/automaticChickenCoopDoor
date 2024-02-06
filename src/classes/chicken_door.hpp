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
#include "WiFi_handler.hpp"
#include "times_manager.hpp"
#include "sleep_handler.hpp"


class ChickenDoor{
  public:
    friend class Motor;
    ChickenDoor(DisplayUiConfig *displayUiConfig, MotorConfig *motorConfig, WiFiConfig *wifiConfig);
    void begin();
    Motor motor;
    WiFiHandler wifiHandler;
    TimesManager timesManager;
    #ifdef CONFIG_ESP32C3_BROWNOUT_DET
       Esp32C3SleepHandler sleepHandler;
    #elif defined(CONFIG_ESP32S3_BROWNOUT_DET)
       Esp32S3SleepHandler sleepHandler;
    #endif
  protected:
    DisplayUI displayUI;
    MemoryManager memoryManager;
    DisplayUiConfig* displayUiConfig;
    MotorConfig* motorConfig;
    WiFiConfig* wifiConfig;
    const uint minutesToSleep=1;
};

