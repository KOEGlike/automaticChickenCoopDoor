# pragma once
#include "times_manager.hpp"
#include "interfaces.hpp"
#include "motor.hpp"
class SleepHandler
{
  public:
    SleepHandler(TimesManager* timesManager,Motor* motor ,DisplayUiConfig* displayUiConfig);
    void sleepUntilNextAction();
    void begin();
  private:
    TimesManager* timesManager;
    DisplayUiConfig* displayUiConfig;
    Motor* motor;
};