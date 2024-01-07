#include "times_manager.hpp"
#include <TimeAlarms.h>

TimesManager::TimesManager(WiFiHandler* wifiHandler, MemoryManager* memoryManager):
//timeState{MoveTimes{0,0,0,0},0, true,0}
timeState{MoveTimes{0,0,21,44},false, true,0}
{
  this->wifiHandler=wifiHandler;
  this->memoryManager=memoryManager;
}

TimesManager::TimesManager(WiFiHandler* wifiHandler, MemoryManager, TimeState timeState):timeState{MoveTimes{0,0,0,0},true, true,0}
{
  this->timeState=timeState;
  this->wifiHandler=wifiHandler;
  this->memoryManager=memoryManager;
}

void TimesManager::begin(int openAlarmId, int closeAlarmId)
{
  this->openAlarmId=openAlarmId;
  this->closeAlarmId=closeAlarmId;
  
  //timeState=memoryManager->loadTimeStateFromMemory();
  if(timeState.sunsetMode)
  {
    timeState .moveTimes=wifiHandler->sunsetTimes();
  }
  setTime(makeTime(wifiHandler->ipTime()));
  updateAlarm();
}

time_t TimesManager::getTimeUntilNextAction()
{
  time_t open=Alarm.getNextTrigger(openAlarmId), close=Alarm.getNextTrigger(closeAlarmId);
  return min(open, close) -now();
}

void TimesManager::updateMoveTimes(MoveTimes moveTimes)
{
 timeState.moveTimes=moveTimes;
  memoryManager->saveTimeStateToMemory(timeState);
  updateAlarm();
}

void TimesManager::updateTimeSate(TimeState timeState)
{
  this->timeState=timeState;
  memoryManager->saveTimeStateToMemory(timeState);
  updateAlarm();
}

void TimesManager::updateCurrentTime(tmElements_t time)
{
  tmElements_t tm;
  breakTime(getCurrentTime(), tm);
  tm.Hour=time.Hour;
  tm.Minute=time.Minute;
  setTime(makeTime(time)); 
  if(time.Hour==0&&time.Minute==0)
  {
   timeState.autoTime=true;
   }
  else
  {
   timeState.autoTime=false;
   timeState.offset=time.Hour-wifiHandler->UTCTime().Hour;
  }
  memoryManager->saveTimeStateToMemory(timeState);
}

TimeState TimesManager::getTimeState()
{
  return timeState;
}

void TimesManager::updateAlarm()
{
  Alarm.write(openAlarmId, AlarmHMS(timeState.moveTimes.openTime.Hour, timeState.moveTimes.openTime.Minute, timeState.moveTimes.openTime.Second));
  Alarm.write(closeAlarmId, AlarmHMS(timeState.moveTimes.closeTime.Hour, timeState.moveTimes.closeTime.Minute, timeState.moveTimes.closeTime.Second));
}

time_t TimesManager::getCurrentTime()
{
  Serial.println("sync");
  if(timeState.autoTime)return makeTime(wifiHandler->ipTime());
  tmElements_t tm=wifiHandler->UTCTime();
  tm.Hour+=timeState.offset;
  return makeTime(tm);
}

TimeElements TimesManager::getCurrentTimeElements()
{
  TimeElements timeElements;
  breakTime(getCurrentTime(), timeElements);
  return timeElements;
}