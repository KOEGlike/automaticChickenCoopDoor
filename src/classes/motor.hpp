#ifndef MOTOR_HPP
#define MOTOR_HPP

#include <A4988.h>
#include "interfaces.hpp"

class Motor;

class MotorCalibrator{
  public:
    MotorCalibrator(Motor *motor, MotorInterface *interface,  long stepAmout);
    void turnClockwise();
    void turnCounterClockwise();
    void setOppenedState();
    void setClosedState();
  protected:
    Motor *m_motor;
    MotorInterface *m_interface;
    long m_stepAmout, m_currentStep;
    bool m_upIsClockwise=true, firstIsSet=false;
};

class Motor
{
  public:
    Motor(MotorConfig config, MotorInterface *interface);
    ~Motor();
    void changeState(float procentage);
    void moveSteps(long steps);
    void begin();
    MotorCalibrator *currentMotorCalibrator=nullptr;
    MotorCalibrator* calibrate(int stepAmout);
  protected:
    A4988 m_motor;
    MotorInterface *m_interfece;
};

#endif