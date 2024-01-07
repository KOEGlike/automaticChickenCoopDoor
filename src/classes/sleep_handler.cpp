#include "sleep_handler.hpp"
#include "driver/rtc_io.h"

SleepHandler::SleepHandler(TimesManager* timesManager,Motor* motor ,DisplayUiConfig* displayUiConfig)
{
  this->timesManager = timesManager;
  this->displayUiConfig = displayUiConfig;
  this->motor = motor;
}

void SleepHandler::sleepUntilNextAction()
{
  Serial.println("Going to sleep");
  gpio_num_t motorDriverEnablePin=motor->getConfig()->enable;
  digitalWrite(motorDriverEnablePin, HIGH);
  rtc_gpio_hold_en(motorDriverEnablePin);
  
  rtc_gpio_pullup_en(displayUiConfig->btn3Pin);
  esp_sleep_enable_ext0_wakeup(displayUiConfig->btn3Pin, 0);
  
  uint64_t microSecondsForTheSleepinessToGoAway= 30*1000*1000;
  uint64_t microSecondsForWakeUp=(uint64_t)timesManager->getTimeUntilNextAction() *1000* 1000 -microSecondsForTheSleepinessToGoAway;
  esp_err_t err =  esp_sleep_enable_timer_wakeup(microSecondsForWakeUp);
  if(err != ESP_OK)
  {
    Serial.println("Error enabling timer wakeup");
  }
  
  motor->disable();
  
  Serial.flush();
  esp_deep_sleep_start();
}
void SleepHandler::begin()
{
  gpio_hold_dis(motor->getConfig()->enable);
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