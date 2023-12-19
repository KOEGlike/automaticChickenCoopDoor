#pragma once

#include <A4988.h>
#include<DRV8825.h>
#include "interfaces.hpp"

class Motor;
class MotorConfig;
class ChickenDoor;
class MotorCalibrator{
  public:
    MotorCalibrator(Motor *motor);
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
    Motor *m_motor;
    int  m_currentStep=0, first;
    bool  m_firstSetIsBottom, m_isDone=true, m_firstIsSet=false;
};

class Motor
{
  public:
    Motor(MotorConfig* config);
    void changeState(float percentage);
    float getState();
    void begin();
    MotorState getMotorState();
    friend class MotorCalibrator;
    MotorCalibrator calibrator;
  protected:
    void moveSteps(long steps);
    const uint16_t motorRpm=200;
    DRV8825 m_stepper;
    MotorState motorState;
};