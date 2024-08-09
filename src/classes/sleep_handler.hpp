# pragma once
#include "times_manager.hpp"
#include "interfaces.hpp"
#include "motor.hpp"

struct WakeupReason{
  WakeupReason(std::function<void()> onGoingToSleep, std::function<void()> onWakeup) {
    this->onGoingToSleep = onGoingToSleep;
    this->onWakeup = onWakeup;
  }
  std::function<void()> onGoingToSleep;
  std::function<void()> onWakeup;
};

class SleepHandler
{
  public:
    SleepHandler(std::shared_ptr<TimesManager> timesManager,std::shared_ptr<Motor> motor );
    virtual void sleepUntilNextAction()=0;
    virtual void begin()=0;
    void addWakeupReason(WakeupReason wakeupReason) {
      wakeupReasons.push_back(wakeupReason);
    }
    virtual void addGPIOWakeupSource(gpio_num_t gpio, bool gpioInputType=INPUT)=0;
  protected:
    std::shared_ptr<TimesManager> timesManager;
    std::shared_ptr<Motor> motor;
    std::vector<WakeupReason> wakeupReasons;
    
    void setTimerWakeupReason();

    void onWakeup() {
      for(auto& wakeupReason : wakeupReasons) {
        wakeupReason.onWakeup();
      }
    }
    void onGoingToSleep() {
      for(auto& wakeupReason : wakeupReasons) {
        wakeupReason.onGoingToSleep();
      }
    }
};

#ifdef CONFIG_ESP32C3_BROWNOUT_DET

class Esp32C3SleepHandler :public SleepHandler {
  public:
    Esp32C3SleepHandler(std::shared_ptr<TimesManager> timesManager,std::shared_ptr<Motor> motor);
    void sleepUntilNextAction() override;
    void begin() override;
    void addGPIOWakeupSource(gpio_num_t gpio, bool gpioInputType=INPUT) override;
    
};
#elif defined(CONFIG_ESP32S3_BROWNOUT_DET)
class Esp32S3SleepHandler :public SleepHandler {
  public:
    Esp32S3SleepHandler(std::shared_ptr<TimesManager> timesManager,std::shared_ptr<Motor> motor);
    void sleepUntilNextAction() override;
    void begin() override;
    void addGPIOWakeupSource(gpio_num_t gpio, bool gpioInputType=INPUT) override;
};
#endif
