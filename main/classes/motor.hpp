#pragma once

#include <A4988.h>
#include<DRV8825.h>
#include "interfaces.hpp"
#include "memory_manager.hpp"
#include <memory>

class Motor;
class MotorCalibrator{
  public:
    MotorCalibrator(Motor* motor);
    void start( bool firstSetIsBottom=true);
    void turn(int amountOfSteps,bool isClockwise);
    void setFirstState();
    void setSecondState();
    void setState();
    long getCurrentStep();
    bool isCalibrating();
    bool firstIsSet();
    friend class Motor;
  protected:
    Motor* m_motor;    
    int  m_currentStep=0, first;
    bool  m_firstSetIsBottom, m_isDone=true, m_firstIsSet=false;
};

class Motor
{
  public:
    Motor(std::shared_ptr<MemoryManager> memoryManager,std::shared_ptr<MotorConfig> config);
    void changeState(float percentage);
    float getState();
    void begin();
    void enable();
    void disable();
    bool getActiveState();
    std::shared_ptr<MotorConfig> getConfig();
    MotorState getMotorState();
    friend class MotorCalibrator;
    MotorCalibrator calibrator;
  protected:
    void moveSteps(long steps);
    const uint16_t motorRpm=200;
    A4988 m_stepper;
    MotorState motorState;
    std::shared_ptr<MemoryManager> memoryManager;
    std::shared_ptr<MotorConfig> config;
};