#ifndef MOTOR_HPP
#define MOTOR_HPP

#include <A4988.h>
#include "interfaces.hpp"

class Motor;

class MotorCalibrator{
  public:
    MotorCalibrator(Motor *motor, MotorInterface *interface,  long stepAmout, bool isDone=false);
    void moveUp();
    void moveDown();
    void setUpper();
    void setLower();
    void finish();
  protected:
    Motor *m_motor;
    MotorInterface *m_interface;
    long m_stepAmout, m_stepCounter=0, m_movementLengthInSteps;
    bool m_isDone=false;
};

class Motor
{
  public:
    Motor(MotorConfig config, MotorInterface interface);
    void changeState(float procentage);
    void moveSteps(long steps);
    void begin();
    bool isCalibarting=false;
    MotorCalibrator calibrate(int stepAmout);
  protected:
    A4988 m_motor;
    MotorInterface m_interfece;
};

#endif