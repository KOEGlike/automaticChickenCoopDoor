#ifndef MOTOR_HPP
#define MOTOR_HPP

#include <A4988.h>
#include "interfaces.hpp"
class Motor
{
  public:
  Motor(MotorConfig config, MotorInterface interface);
  void startCalibration(uint8_t speed);
  void stopCalibration();
  void changeState(float procentage);
  void begin();
  protected:
  A4988 motor;
  MotorInterface m_interfece;
};

#endif