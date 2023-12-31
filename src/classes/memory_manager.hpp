#pragma once
#include <Preferences.h>
#include "interfaces.hpp"
#include <time.h>

class MemoryManager{
  public: 
    void begin();
    void saveTimeStateToMemory(TimeState timeState);
    TimeState loadTimeStateFromMemory();
    void saveMotorStateToMemory(MotorState motorState);
    MotorState loadMotorStateFromMemory();
  private:
    Preferences pref;

};