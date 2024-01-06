# pragma once
#include "times_manager.hpp"
#include "interfaces.hpp"
class SleepHandler
{
  public:
    SleepHandler(TimesManager* timesManager, DisplayUiConfig* displayUiConfig);
    void sleepUntilNextAction();
    void begin();
  private:
    TimesManager* timesManager;
    DisplayUiConfig* displayUiConfig;
};