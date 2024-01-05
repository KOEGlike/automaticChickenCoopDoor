# pragma once

#include "interfaces.hpp"
#include "memory_manager.hpp"
#include <time.h>
#include "WiFi_handler.hpp"
class TimesManager_t
{
  public:
    TimesManager_t(WiFiHandler_t* WiFiHandler, MemoryManager_t* MemoryManager);
    TimeState getTimeState();
    void begin(int openAlarmId, int closeAlarmId);
    void updateTimeSate(TimeState timeState);
    void updateMoveTimes(MoveTimes moveTimes);
    void updateCurrentTime(tmElements_t time);
    time_t syncFunc();
  private:
    TimeState timeState;
    void updateAlarm();
    int openAlarmId, closeAlarmId;
    WiFiHandler_t* WiFiHandler;
    MemoryManager_t* MemoryManager;
};

  