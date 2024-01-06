#include "sleep_handler.hpp"
#include "driver/rtc_io.h"

SleepHandler::SleepHandler(TimesManager* timesManager, DisplayUiConfig* displayUiConfig)
{
  this->timesManager = timesManager;
  this->displayUiConfig = displayUiConfig;
}

void SleepHandler::sleepUntilNextAction()
{
  Serial.println("Going to sleep");
  rtc_gpio_pullup_en(displayUiConfig->btn3Pin);
  esp_sleep_enable_ext0_wakeup(displayUiConfig->btn3Pin, 0);
  Serial.println("time until next action "+String(timesManager->getTimeUntilNextAction()));

  esp_err_t err =  esp_sleep_enable_timer_wakeup(timesManager->getTimeUntilNextAction() *1000* 1000000);
  if(err != ESP_OK)
  {
    Serial.println("Error enabling timer wakeup");
  }
  else{
    Serial.println("Timer wakeup enabled");
  }
  Serial.flush();
  esp_deep_sleep_start();
}
void SleepHandler::begin()
{
  rtc_gpio_deinit(displayUiConfig->btn3Pin);

  esp_sleep_wakeup_cause_t wakeup_reason;

  wakeup_reason = esp_sleep_get_wakeup_cause();

  switch(wakeup_reason){
    case ESP_SLEEP_WAKEUP_EXT0 : Serial.println("Wakeup caused by external signal using RTC_IO"); break;
    case ESP_SLEEP_WAKEUP_EXT1 : Serial.println("Wakeup caused by external signal using RTC_CNTL"); break;
    case ESP_SLEEP_WAKEUP_TIMER : Serial.println("Wakeup caused by timer"); break;
    case ESP_SLEEP_WAKEUP_TOUCHPAD : Serial.println("Wakeup caused by touchpad"); break;
    case ESP_SLEEP_WAKEUP_ULP : Serial.println("Wakeup caused by ULP program"); break;
    default : Serial.printf("Wakeup was not caused by deep sleep: %d\n",wakeup_reason); break;
  }

}