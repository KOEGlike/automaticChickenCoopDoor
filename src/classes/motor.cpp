#include "motor.hpp"	
#include <cmath>
#include "memory_manager.hpp"

Motor::Motor(MemoryManager* memoryManager,MotorConfig* config): 
m_stepper{config->steps, config->dir, config->step, config->enable,config->m0, config->m1,config->m2},
calibrator{this}
{
  this->memoryManager=memoryManager;
  this->config=config;
}

MotorConfig* Motor::getConfig()\
{
  return config;
}

bool MotorCalibrator::isCalibrating()
{
  return !m_isDone;
}

void Motor::changeState(float percentage)
{
  int closed_step=motorState.calibrationState.bottomStep, open_step=motorState.calibrationState.topStep, current_step=motorState.currentStep;
  int number_of_steps=open_step-closed_step;
  int steps_to_move=std::floor(number_of_steps*percentage);
  moveSteps(steps_to_move-current_step +closed_step);
}

void Motor::begin()
{
 m_stepper.begin(motorRpm, 32);
 m_stepper.setEnableActiveState(LOW);
 m_stepper.enable();
 motorState= memoryManager->loadMotorStateFromMemory();
}

void Motor::moveSteps(long steps)
{
  int bottomStep=motorState.calibrationState.bottomStep, topStep=motorState.calibrationState.topStep, currentStep=motorState.currentStep;
  motorState.currentStep+=steps;
  m_stepper.move(steps);
  memoryManager-> saveMotorStateToMemory(motorState);
}

float Motor::getState()
{
  int closed_step=motorState.calibrationState.bottomStep, open_step=motorState.calibrationState.topStep, current_step=motorState.currentStep;
  int number_of_steps=open_step-closed_step;
  if(number_of_steps==0){return  1;}
  float percentage=(current_step-closed_step)/number_of_steps;
  return percentage;
}

void Motor::disable()
{
  m_stepper.disable();
}

void Motor::enable()
{
  m_stepper.enable();
}

MotorState Motor::getMotorState()
{
  return motorState;
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
  Serial.println("started");
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
  Serial.println("first set");
}

void MotorCalibrator::setSecondState()
{
  if(m_isDone==true)return;
  if(m_firstIsSet==false)return;
  m_motor->motorState= MotorState{MotorCalibrationState{m_firstSetIsBottom?first:m_currentStep, m_firstSetIsBottom?m_currentStep:first}, m_currentStep} ;
  m_isDone=true;
  Serial.println("second set");
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

bool MotorCalibrator::firstIsSet()
{
  return m_firstIsSet;
}