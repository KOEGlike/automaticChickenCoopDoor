#include "times_manager.hpp"
#include "WiFiHandler.hpp"
#include <TimeAlarms.h>

TimesManager_t::TimesManager_t():timeState{MoveTimes{12,12,12,12}, true, true, 0}
{}

void TimesManager_t::begin(int openAlarmId, int closeAlarmId)
{
  this->openAlarmId=openAlarmId;
  this->closeAlarmId=closeAlarmId;
}

void TimesManager_t::updateMoveTimes(MoveTimes moveTimes)
{
 timeState.moveTimes=moveTimes;
  MemoryManager.saveTimeStateToMemory(timeState);
  updateAlarm();
}

void TimesManager_t::updateTimeSate(TimeState timeState)
{
  this->timeState=timeState;
  MemoryManager.saveTimeStateToMemory(timeState);
  updateAlarm();
}

void TimesManager_t::updateCurrentTime(tmElements_t time)
{
  setTime(makeTime(time)); 
  if(time.Hour==0&&time.Minute==0)
  {
   timeState.autoTime=true;
   }
  else
  {
   timeState.autoTime=false;
   timeState.offset=time.Hour-WiFiHandler.UTCTime().Hour;
  }
  MemoryManager.saveTimeStateToMemory(timeState);
}

TimeState TimesManager_t::getTimeState()
{
  return timeState;
}

void TimesManager_t::updateAlarm()
{
  Alarm.write(openAlarmId, makeTime(timeState.moveTimes .openTime));
  Alarm.write(closeAlarmId, makeTime(timeState.moveTimes .openTime));
}