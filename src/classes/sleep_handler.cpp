#include "sleep_handler.hpp"
#include "driver/rtc_io.h"

SleepHandler::SleepHandler(std::shared_ptr<TimesManager> timesManager, std::shared_ptr<Motor> motor )
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

#ifdef CONFIG_ESP32S3_BROWNOUT_DET

Esp32S3SleepHandler::Esp32S3SleepHandler(std::shared_ptr<TimesManager> timesManager,std::shared_ptr<Motor> motor ):
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



void Esp32S3SleepHandler::addGPIOWakeupSource(gpio_num_t gpio, bool gpioInputType) {
  addWakeupReason(
    WakeupReason{
      [&](){esp_sleep_enable_ext0_wakeup(gpio, gpioInputType);},
      [gpio](){rtc_gpio_deinit(gpio);}
    }
  );
}


void Esp32S3SleepHandler::begin() 
{
  onWakeup();
  gpio_hold_dis(motor->getConfig()->enable);

}

#elif defined(CONFIG_ESP32C3_BROWNOUT_DET)

Esp32C3SleepHandler::Esp32C3SleepHandler(std::shared_ptr<TimesManager> timesManager,std::shared_ptr<Motor> motor ):
SleepHandler(timesManager, motor) {

}



void Esp32C3SleepHandler::sleepUntilNextAction () 
{
  Serial.println("Going to sleep");
  gpio_num_t motorDriverEnablePin=motor->getConfig()->enable;
  digitalWrite(motorDriverEnablePin, HIGH);
  gpio_hold_en(motorDriverEnablePin);
  onGoingToSleep();
  setTimerWakeupReason();
  
  motor->disable();
  
  Serial.flush();
  esp_deep_sleep_start();
}

void Esp32C3SleepHandler::addGPIOWakeupSource(gpio_num_t gpio, bool gpioInputType) {
  addWakeupReason(
    WakeupReason{
      [&](){ gpio_deep_sleep_wakeup_enable(gpio, gpioInputType?GPIO_INTR_HIGH_LEVEL:GPIO_INTR_LOW_LEVEL);},
      [gpio](){gpio_deep_sleep_wakeup_disable(gpio);}
    }
  );
}

void Esp32C3SleepHandler::begin() 
{
  onWakeup();
  gpio_hold_dis(motor->getConfig()->enable);
  gpio_deep_sleep_hold_dis();
}

#endif