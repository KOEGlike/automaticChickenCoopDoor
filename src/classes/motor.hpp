#ifndef MOTOR_HPP
#define MOTOR_HPP

#include <A4988.h>
#include "interfaces.hpp"
class Motor
{
  public:
  Motor(MotorConfig config, MotorInterface interface);
  void changeState(float procentage);
  void moveSteps(int steps);
  void begin();
  protected:
  A4988 motor;
  MotorInterface m_interfece;
};

#endif