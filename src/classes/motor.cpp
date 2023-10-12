#include "motor.hpp"	
#include <cmath>
Motor::Motor(MotorConfig *config, MotorInterface *interface): 
m_motor{config->steps, config->dir, config->step, config->enable}, 
m_interface{interface}, calibrator{this}
{
}

void Motor::changeState(float percentage)
{
  percentage=percentage>1?1:percentage;
  percentage=percentage<0?0:percentage;
  moveSteps(std::floor(m_interface->getCalibrationState().movementLengthInSteps*percentage)-m_interface->getState());
}

void Motor::begin()
{
  m_motor.begin();
}

void Motor::moveSteps(long steps)
{
  m_interface->setState(m_interface->getState()+steps);
  m_motor.move(m_interface->getCalibrationState().upIsClocwise?steps:-steps);
}

float Motor::getState()
{
  return m_interface->getState();
}

MotorCalibrator::MotorCalibrator(Motor *motor)
{
  m_motor = motor;
  m_motor->m_interface->settingStateClosed();
}

void MotorCalibrator::start(long stepAmout, bool firstSetIsBottom)
{
  m_stepAmout = stepAmout;
  m_isDone=false;
  m_currentStep=0;
  m_firstSetIsBottom=firstSetIsBottom;
}


void MotorCalibrator::turn(bool isClockwise)
{
  if(m_isDone==true)return;
  m_currentStep+=isClockwise?m_stepAmout:-m_stepAmout;
  m_motor->m_motor.move(isClockwise?m_stepAmout:-m_stepAmout);
}



void MotorCalibrator::setFirstState()
{
  if(m_isDone==true)return;
  m_firstIsSet=true;
  m_motor->m_interface->setState(m_firstSetIsBottom?0:1);
  m_currentStep=0;
  return;
}

void MotorCalibrator::setSecondState()
{
  if(m_isDone==true)return;
  if(m_firstIsSet==false)return;
  m_upIsClockwise=m_currentStep>=0?true:false;
  m_motor->m_interface->setState(m_firstSetIsBottom?1:0);
  m_motor->m_interface->setCalibrationState(MotorCalibrationState(m_upIsClockwise, m_firstSetIsBottom?m_currentStep:-m_currentStep));
  m_isDone=true;
}