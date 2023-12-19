# pragma once

#include "interfaces.hpp"
#include "memory_manager.hpp"
#include <time.h>

class TimesManager_t
{
  public:
    TimesManager_t();
    TimeState getTimeState();
    void updateTimeSate(TimeState timeState);
    void updateMoveTimes(MoveTimes moveTimes);
    void updateCurrentTime(tmElements_t time);
  private:
    TimeState timeState;
    void updateAlarm(MoveTimes times);
};

inline TimesManager_t TimesManager;