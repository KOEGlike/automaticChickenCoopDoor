#ifndef MOTOR_HPP
#define MOTOR_HPP

#include <A4988.h>
#include<DRV8825.h>
#include "interfaces.hpp"

class Motor;
class MotorConfig;
class MotorInterface;
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
    Motor(MotorConfig *config, MotorInterface *interface);
    void changeState(float procentage);
    float getState();
    void begin();
    friend class MotorCalibrator;
    MotorCalibrator calibrator;
  protected:
    void moveSteps(long steps);
    const uint16_t motorRpm=200;
    DRV8825 m_stepper;
    MotorInterface *m_interface;
};

#endif