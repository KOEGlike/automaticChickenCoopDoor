#ifndef MOTOR_HPP
#define MOTOR_HPP

#include <A4988.h>
#include "interfaces.hpp"
class Motor
{
  public:
  void startCalibration(uint8_t speed);
  void stopCalibration();
  void changeState(float procentage);
  protected:
  A4988 motor;
};

#endif