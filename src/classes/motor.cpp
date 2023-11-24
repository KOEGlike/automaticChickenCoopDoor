#include "motor.hpp"	
#include <cmath>
Motor::Motor(MotorConfig *config, MotorInterface *interface): 
m_stepper{config->steps, config->dir, config->step, config->enable,config->m0, config->m1,config->m2}, 
m_interface{interface}, calibrator{this}
{}

bool MotorCalibrator::isCalibrating()
{
  return !m_isDone;
}

void Motor::changeState(float percentage)
{
  int closed_step=m_interface->getMotorStatePtr()->calibrationState.bottomStep, open_step=m_interface->getMotorStatePtr()->calibrationState.topStep, current_step=m_interface->getMotorStatePtr()->currentStep;
  int number_of_steps=open_step-closed_step;
  int steps_to_move=std::floor(number_of_steps*percentage);
  moveSteps(steps_to_move-current_step +closed_step);
}

void Motor::begin()
{
 m_stepper.begin(motorRpm, 32);
 m_stepper.enable();
}

void Motor::moveSteps(long steps)
{
  int bottomStep=m_interface->getMotorStatePtr()->calibrationState.bottomStep, topStep=m_interface->getMotorStatePtr()->calibrationState.topStep, currentStep=m_interface->getMotorStatePtr()->currentStep;
  m_interface->getMotorStatePtr()->currentStep=currentStep+steps;
  m_stepper.move(steps);
}

float Motor::getState()
{
  int closed_step=m_interface->getMotorStatePtr()->calibrationState.bottomStep, open_step=m_interface->getMotorStatePtr()->calibrationState.topStep, current_step=m_interface->getMotorStatePtr()->currentStep;
  int number_of_steps=open_step-closed_step;
  float percentage=(current_step-closed_step)/number_of_steps;
  return percentage;
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

long MotorCalibrator::getCurrentStep()
{
  return m_currentStep;
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
  first=m_currentStep;
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
  *m_motor->m_interface->getMotorStatePtr() =MotorState{MotorCalibrationState{m_firstSetIsBottom?first:m_currentStep, m_firstSetIsBottom?m_currentStep:first}, m_currentStep};
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