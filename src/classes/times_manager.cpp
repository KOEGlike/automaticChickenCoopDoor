#include "times_manager.hpp"
#include <TimeAlarms.h>

TimesManager_t::TimesManager_t(WiFiHandler_t* WiFiHandler, MemoryManager_t* MemoryManager):timeState{MoveTimes{0,0,14,39}, false, true,0}
{
  this->WiFiHandler=WiFiHandler;
  this->MemoryManager=MemoryManager;
}

void TimesManager_t::begin(int openAlarmId, int closeAlarmId)
{
  this->openAlarmId=openAlarmId;
  this->closeAlarmId=closeAlarmId;
  timeState=MemoryManager->loadTimeStateFromMemory();
  if(timeState.sunsetMode)
  {
    timeState .moveTimes=WiFiHandler->sunsetTimes();
  }
  updateAlarm();
  Serial.println(timeState.moveTimes.openTime.Hour);
  Serial.println(timeState.moveTimes.openTime.Minute);
  Serial.println(timeState.moveTimes.closeTime.Hour);
  Serial.println(timeState.moveTimes.closeTime.Minute);
  TimeElements tm;
  breakTime(now(), tm);
  Serial.println(tm.Hour);
  Serial.println(tm.Minute);
  breakTime(Alarm.read(openAlarmId), tm);
  Serial.println(tm.Hour);
  Serial.println(tm.Minute);
  breakTime(Alarm.read(closeAlarmId), tm);
  Serial.println(tm.Hour);
  Serial.println(tm.Minute);
}

void TimesManager_t::updateMoveTimes(MoveTimes moveTimes)
{
 timeState.moveTimes=moveTimes;
  MemoryManager->saveTimeStateToMemory(timeState);
  updateAlarm();
}

void TimesManager_t::updateTimeSate(TimeState timeState)
{
  this->timeState=timeState;
  MemoryManager->saveTimeStateToMemory(timeState);
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
   timeState.offset=time.Hour-WiFiHandler->UTCTime().Hour;
  }
  MemoryManager->saveTimeStateToMemory(timeState);
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

time_t TimesManager_t::syncFunc()
{
  if(timeState.autoTime)return makeTime(WiFiHandler->ipTime());
  tmElements_t tm=WiFiHandler->UTCTime();
  tm.Hour+=timeState.offset;
  return makeTime(tm);
}