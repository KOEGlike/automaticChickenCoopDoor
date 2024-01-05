# pragma once
#include "times_manager.hpp"
#include "interfaces.hpp"
class SleepHandler
{
  public:
    SleepHandler(TimesManager* timesManager, DisplayUiConfig* displayUiConfig);
    void sleepUntilNextAction();
  private:
    TimesManager* timesManager;
    DisplayUiConfig* displayUiConfig;
};