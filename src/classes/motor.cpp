#include "motor.hpp"	
#include <cmath>
Motor::Motor(MotorConfig config, MotorInterface *interface): 
m_motor{config.steps, config.dir, config.step, config.enable}, 
m_interfece{interface}
{
 
}

Motor::~Motor()
{
  delete currentMotorCalibrator;
}

void Motor::changeState(float percentage)
{
  percentage=percentage>1?1:percentage;
  percentage=percentage<0?0:percentage;
  moveSteps(std::floor(m_interfece->getCalibrationState().movementLengthInSteps*percentage));
}

void Motor::begin()
{
  m_motor.begin();
}

void Motor::moveSteps(long steps)
{
  m_interfece->setState(m_interfece->getState()+steps);
  m_motor.move(m_interfece->getCalibrationState().upIsClocwise?steps:-steps);
}

MotorCalibrator* Motor::calibrate(int stepAmout)
{ 
  delete currentMotorCalibrator;
  currentMotorCalibrator=new MotorCalibrator(this, m_interfece, stepAmout);
  return currentMotorCalibrator;
}

MotorCalibrator::MotorCalibrator(Motor *motor, MotorInterface *interface, long stepAmout)
{
  m_motor = motor;
  m_stepAmout = stepAmout;
  m_interface=interface;
  interface->settingStateClosed();
}


void MotorCalibrator::turnClockwise()
{
  if(m_motor->currentMotorCalibrator!=this&&m_motor->currentMotorCalibrator!=nullptr) return;
  m_currentStep+=m_upIsClockwise?m_stepAmout:-m_stepAmout;
  m_motor->moveSteps(m_stepAmout);
}

void MotorCalibrator::turnCounterClockwise()
{
  if(m_motor->currentMotorCalibrator!=this&&m_motor->currentMotorCalibrator!=nullptr) return;
  m_currentStep+=m_upIsClockwise?-m_stepAmout:m_stepAmout;
  m_motor->moveSteps(-m_stepAmout);
}

void MotorCalibrator::setClosedState()
{
  m_interface->setState(0);
  m_upIsClockwise=m_currentStep>=0?true:false;
  m_currentStep=0;
  firstIsSet=true;
  m_interface->settingStateOpen();
}

void MotorCalibrator::setOppenedState()
{
  if(!firstIsSet)
  {
    throw std::runtime_error("You must set the closed state first");
  }
  m_interface->setState(1);
  m_interface->setCalibrationState(MotorCalibrationState(m_upIsClockwise, m_currentStep));
  m_motor->currentMotorCalibrator=nullptr;
}

