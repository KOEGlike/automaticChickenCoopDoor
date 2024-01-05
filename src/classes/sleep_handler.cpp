#include "sleep_handler.hpp"
#include "driver/rtc_io.h"

SleepHandler::SleepHandler(TimesManager* timesManager, DisplayUiConfig* displayUiConfig)
{
  this->timesManager = timesManager;
  this->displayUiConfig = displayUiConfig;
}

void SleepHandler::sleepUntilNextAction()
{
  rtc_gpio_pullup_en(displayUiConfig->btn3Pin);
  esp_sleep_enable_ext0_wakeup(displayUiConfig->btn3Pin, 0);
  esp_sleep_enable_timer_wakeup(timesManager->getTimeUntilNextAction() * 1000000);
  esp_deep_sleep_start();
}