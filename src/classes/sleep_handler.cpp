#include "sleep_handler.hpp"
#include "driver/rtc_io.h"

SleepHandler::SleepHandler(TimesManager* timesManager,Motor* motor )
{
  this->timesManager = timesManager;
  this->motor = motor;
}

void SleepHandler::setTimerWakeupReason() {
  uint64_t microSecondsForTheSleepinessToGoAway= 30*1000*1000;
  uint64_t microSecondsForWakeUp=(uint64_t)timesManager->getTimeUntilNextAction() *1000* 1000 -microSecondsForTheSleepinessToGoAway;
  esp_err_t err =  esp_sleep_enable_timer_wakeup(microSecondsForWakeUp);
  if(err != ESP_OK)
  {
    Serial.println("Error enabling timer wakeup");
  }
}

Esp32S3SleepHandler::Esp32S3SleepHandler(TimesManager* timesManager,Motor* motor ):
SleepHandler(timesManager, motor) {
  
}



void Esp32S3SleepHandler::sleepUntilNextAction () 
{
  Serial.println("Going to sleep");
  gpio_num_t motorDriverEnablePin=motor->getConfig()->enable;
  digitalWrite(motorDriverEnablePin, HIGH);
  rtc_gpio_hold_en(motorDriverEnablePin);
  
  
  onGoingToSleep();
  setTimerWakeupReason();
  
  motor->disable();
  
  Serial.flush();
  esp_deep_sleep_start();
}

void Esp32S3SleepHandler::addGPIOWakeupSource(int gpio, int gpioInputType) {
  addWakeupReason(
    WakeupReason{
      [](){},
      [](){}
    }
  );
}

void Esp32S3SleepHandler::begin() 
{
  onWakeup();
  gpio_hold_dis(motor->getConfig()->enable);

}

Esp32C3SleepHandler::Esp32C3SleepHandler(TimesManager* timesManager,Motor* motor ):
SleepHandler(timesManager, motor) {

}

void Esp32C3SleepHandler::sleepUntilNextAction () 
{
  Serial.println("Going to sleep");
  gpio_num_t motorDriverEnablePin=motor->getConfig()->enable;
  digitalWrite(motorDriverEnablePin, HIGH);
  //rtc_gpio_hold_en(motorDriverEnablePin);
  esp_sleep_enable_gpio_switch(true);
  onGoingToSleep();
  setTimerWakeupReason();
  
  motor->disable();
  
  Serial.flush();
  esp_deep_sleep_start();
}

void Esp32C3SleepHandler::addGPIOWakeupSource(int gpio, int gpioInputType) {
  addWakeupReason(
    WakeupReason{
      [](){},
      [](){}
    }
  );
}

void Esp32C3SleepHandler::begin() 
{
  onWakeup();
  gpio_hold_dis(motor->getConfig()->enable);
 // rtc_gpio_deinit(displayUiConfig->btn3Pin);
}