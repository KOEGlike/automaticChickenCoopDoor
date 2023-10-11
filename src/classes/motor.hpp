#ifndef MOTOR_HPP
#define MOTOR_HPP

#include <A4988.h>
#include "interfaces.hpp"

class Motor;

class MotorCalibrator{
  public:
    MotorCalibrator(Motor *motor, MotorInterface *interface);
    void start(long stepAmout, bool firstSetIsBottom=true);
    void turnClockwise();
    void turnCounterClockwise();
    void setFirstState();
    void setSecondState();
    void end();
  protected:
    Motor *m_motor;
    MotorInterface *m_interface;
    long m_stepAmout, m_currentStep;
    bool m_upIsClockwise=true, m_firstSetIsBottom, m_isDone=true, m_firstIsSet=false;
};

class Motor
{
  public:
    Motor(MotorConfig config, MotorInterface *interface);
    void changeState(float procentage);
    void moveSteps(long steps);
    void begin();
    MotorCalibrator calibrator;
  protected:
    A4988 m_motor;
    MotorInterface *m_interfece;
};

#endif