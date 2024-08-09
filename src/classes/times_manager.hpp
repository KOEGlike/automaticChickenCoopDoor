# pragma once

#include "interfaces.hpp"
#include "memory_manager.hpp"
#include <time.h>
#include "WiFi_handler.hpp"
class TimesManager
{
  public:
    TimesManager(std::shared_ptr<WiFiHandler> wifiHandler, std::shared_ptr<MemoryManager> memoryManager);
    TimesManager(std::shared_ptr<WiFiHandler> wifiHandler, MemoryManager, TimeState timeState);
    TimeState getTimeState();
    time_t getTimeUntilNextAction();
    void begin(int openAlarmId, int closeAlarmId);
    void updateTimeSate(TimeState timeState);
    void updateMoveTimes(MoveTimes moveTimes);
    void updateCurrentTime(tmElements_t time);
    time_t getCurrentTime();
    TimeElements getCurrentTimeElements();
  private:
    TimeState timeState;
    void updateAlarm();
    int openAlarmId, closeAlarmId;
    std::shared_ptr<WiFiHandler> wifiHandler;
    std::shared_ptr<MemoryManager> memoryManager;
};

  