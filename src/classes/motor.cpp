#include "motor.hpp"	
#include <cmath>
Motor::Motor(MotorConfig *config, MotorInterface *interface): 
m_stepper{config->steps, config->dir, config->step, config->enable}, 
m_interface{interface}, calibrator{this}
{}

bool MotorCalibrator::isCalibrating()
{
  return !m_isDone;
}

void Motor::changeState(float percentage)
{
  percentage=percentage>1?1:percentage;
  percentage=percentage<0?0:percentage;
  moveSteps(std::floor(m_interface->getCalibrationState().movementLengthInSteps*percentage)-m_interface->getState());
}

void Motor::begin()
{
 m_stepper.begin(120);
 m_stepper.enable();
}

void Motor::moveSteps(long steps)
{
  m_interface->setState(m_interface->getState()+steps);
  m_stepper.move(m_interface->getCalibrationState().upIsClockwise?steps:-steps);
}

float Motor::getState()
{
  return m_interface->getState();
}

MotorCalibrator::MotorCalibrator(Motor *motor){
  m_motor=motor;
}

void MotorCalibrator::start(bool firstSetIsBottom)
{
  if(m_isDone==false)return;
  m_isDone=false;
  m_currentStep=0;
  m_firstSetIsBottom=firstSetIsBottom;
  if(firstSetIsBottom)
  {
    m_motor->m_interface->settingStateClosed();
  }
  else
  {
    m_motor->m_interface->settingStateOpen();
  }
}


void MotorCalibrator::turn(int amountOfSteps,bool isClockwise)
{
  if(m_isDone==true)return;
  m_currentStep+=isClockwise?amountOfSteps:-amountOfSteps;
  m_motor->m_stepper.move(isClockwise?amountOfSteps:-amountOfSteps);
}



void MotorCalibrator::setFirstState()
{
  if(m_isDone==true)return;
  m_firstIsSet=true;
  m_motor->m_interface->setState(m_firstSetIsBottom?0:1);
  m_currentStep=0;
  if(m_firstSetIsBottom)
  {
    m_motor->m_interface->settingStateOpen();
  }
  else
  {
    m_motor->m_interface->settingStateClosed();
  }
}

void MotorCalibrator::setSecondState()
{
  if(m_isDone==true)return;
  if(m_firstIsSet==false)return;
  m_upIsClockwise=m_currentStep>=0?true:false;
  m_motor->m_interface->setState(m_firstSetIsBottom?1:0);
  m_motor->m_interface->setCalibrationState(MotorCalibrationState(m_upIsClockwise, m_firstSetIsBottom?m_currentStep:-m_currentStep));
  m_isDone=true;
  m_motor->m_interface->finishedCalibrating();
}

void MotorCalibrator::setState()
{
  if(m_isDone==true)return;
  if(m_firstIsSet==false)
  {
    setFirstState();
  }
  else{
    setSecondState();
  }
}