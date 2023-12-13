#include "times_manager.hpp"
#include "WiFiHandler.hpp"

TimesManager::TimesManager(TimeState* timeState)
{
  this->timeState = timeState; 
}

void TimesManager::updateMoveTimes(MoveTimes moveTimes)
{
 timeState->moveTimes=moveTimes;
  MemoryManager.saveTimeStateToMemory(*timeState);
}

void TimesManager::updateCurrentTime(tmElements_t time)
{
  setTime(makeTime(time)); 
  if(time.Hour==0&&time.Minute==0)
  {
   timeState->autoTime=true;
   }
  else
  {
   timeState->autoTime=false;
   timeState->offset=time.Hour-WiFiHandler.UTCTime().Hour;
  }
  MemoryManager.saveTimeStateToMemory(*timeState);
}

TimeState TimesManager::getTimeState()
{
  return *timeState;
}