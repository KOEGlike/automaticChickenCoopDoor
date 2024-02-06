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
    SleepHandler(TimesManager* timesManager,Motor* motor );
    virtual void sleepUntilNextAction()=0;
    virtual void begin()=0;
    void addWakeupReason(WakeupReason wakeupReason) {
      wakeupReasons.push_back(wakeupReason);
    }
    virtual void addGPIOWakeupSource(int gpio, int gpioInputType=INPUT)=0;
  protected:
    TimesManager* timesManager;
    Motor* motor;
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

class Esp32S3SleepHandler :public SleepHandler {
  public:
    Esp32S3SleepHandler(TimesManager* timesManager,Motor* motor);
    void sleepUntilNextAction() override;
    void begin() override;
    void addGPIOWakeupSource(int gpio, int gpioInputType=INPUT) override;
};

class Esp32C3SleepHandler :public SleepHandler {
  public:
    Esp32C3SleepHandler(TimesManager* timesManager,Motor* motor);
    void sleepUntilNextAction() override;
    void begin() override;
    void addGPIOWakeupSource(int gpio, int gpioInputType=INPUT) override;
};