#include "times_manager.hpp"
#include "WiFiHandler.hpp"

TimesManager_t::TimesManager_t():timeState{MoveTimes{12,12,12,12}, true, true, 0}
{}

void TimesManager_t::updateMoveTimes(MoveTimes moveTimes)
{
 timeState.moveTimes=moveTimes;
  MemoryManager.saveTimeStateToMemory(timeState);
}

void TimesManager_t::updateTimeSate(TimeState timeState)
{
  this->timeState=timeState;
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

void TimesManager_t::updateAlarm(MoveTimes times)
{

}