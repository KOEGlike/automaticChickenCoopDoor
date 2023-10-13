#ifndef MOTOR_HPP
#define MOTOR_HPP

#include <A4988.h>
#include "interfaces.hpp"

class Motor;
class MotorConfig;
class MotorInterface;
class MotorCalibrator{
  public:
    MotorCalibrator(Motor *motor);
    void start(long stepAmout, bool firstSetIsBottom=true);
    void turn(bool isClockwise);
    void setFirstState();
    void setSecondState();
  protected:
    Motor *m_motor;
    long m_stepAmout, m_currentStep;
    bool m_upIsClockwise=true, m_firstSetIsBottom, m_isDone=true, m_firstIsSet=false;
};

class Motor
{
  public:
    Motor(MotorConfig *config, MotorInterface *interface);
    void changeState(float procentage);
    void moveSteps(long steps);
    float getState();
    void begin();
    friend class MotorCalibrator;
    MotorCalibrator calibrator;
  protected:
    A4988 m_stepper;
    MotorInterface *m_interface;
};

#endif