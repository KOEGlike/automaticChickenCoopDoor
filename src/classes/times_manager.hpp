# pragma once

#include "interfaces.hpp"
#include "memory_manager.hpp"
#include <time.h>

class TimesManager
{
  public:
    TimesManager(TimeState *timeState);
    
    TimeState getTimeState();
    void updateTimeSate(TimeState timeState);
    void updateMoveTimes(MoveTimes moveTimes);
    void updateCurrentTime(tmElements_t time);
  private:
    TimeState *timeState;
};