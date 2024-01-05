#include "memory_manager.hpp"


void MemoryManager::begin()
{
  pref.begin("ChickenDoor", false);
}

void MemoryManager::saveTimeStateToMemory(TimeState timeState)
{
  pref.putULong("openTime", makeTime(timeState.moveTimes.openTime));
  pref.putULong("closeTime", makeTime(timeState.moveTimes.closeTime));
  pref.putBool("sunsetMode", timeState.sunsetMode);
  pref.putBool("autoTime", timeState.autoTime);
  pref.putInt("offset", timeState.offset);
}

TimeState MemoryManager::loadTimeStateFromMemory()
{
  tmElements_t openTime, closeTime;
  breakTime( pref.getULong("openTime", 0),openTime);
  breakTime( pref.getULong("closeTime", 0),closeTime); 
  return TimeState{MoveTimes{openTime, closeTime}, pref.getBool("sunsetMode", true), pref.getBool("autoTime", true), pref.getInt("offset", 0)};
}

void MemoryManager::saveMotorStateToMemory(MotorState motorState)
{
  pref.putInt("bottomStep", motorState.calibrationState.bottomStep);
  pref.putInt("topStep", motorState.calibrationState.topStep);
  pref.putInt("currentStep", motorState.currentStep);
}

MotorState MemoryManager::loadMotorStateFromMemory()
{
  return MotorState{MotorCalibrationState{pref.getInt("bottomStep", 0), pref.getInt("topStep", 0)},pref.getInt("currentStep", 0)};
}