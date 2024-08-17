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
  protected:
    std::shared_ptr<DisplayUiConfig> displayUiConfig;
    std::shared_ptr<MotorConfig> motorConfig;
    std::shared_ptr<WiFiConfig> wifiConfig;
    std::shared_ptr<MemoryManager> memoryManager;
    const uint minutesToSleep = 8, sleepCheckIntervalSec = 30;
  public:
    friend class Motor;
    ChickenDoor(std::shared_ptr<DisplayUiConfig> displayUiConfig, std::shared_ptr<MotorConfig> motorConfig, std::shared_ptr<WiFiConfig> wifiConfig);
    void begin();
    std::shared_ptr<WiFiHandler> wifiHandler;
    std::shared_ptr<TimesManager> timesManager;
    std::shared_ptr<Motor> motor;
   // #ifdef CONFIG_ESP32C3_BROWNOUT_DET
      std::shared_ptr<Esp32C3SleepHandler> sleepHandler;
    //#elif defined(CONFIG_ESP32S3_BROWNOUT_DET)
    //  std::shared_ptr<Esp32S3SleepHandler> sleepHandler;
    //#endif
  protected:
    DisplayUI displayUI;
};

