#include "motor.hpp"	

Motor::Motor(MotorConfig config, MotorInterface interface): 
m_motor{config.steps, config.dir, config.step, config.enable, config.ms1,config.ms2,config.ms3}, 
m_interfece{interface}
{
 
}

void Motor::changeState(float percentage)
{

}

void Motor::begin()
{
  m_motor.begin();
}

void Motor::moveSteps(long steps)
{
  m_motor.move(steps);
}

MotorCalibrator Motor::calibrate(int stepAmout)
{ 
  if(isCalibarting)
  {
    return MotorCalibrator(this,&m_interfece,stepAmout, true);
  }
  isCalibarting=true;
  return MotorCalibrator(this,&m_interfece,stepAmout);
}

MotorCalibrator::MotorCalibrator(Motor *motor, MotorInterface *interface, long stepAmout, bool isDone)
{
  m_motor = motor;
  m_stepAmout = stepAmout;
  m_interface=interface;
  m_isDone=isDone;
}

void MotorCalibrator::finish()
{
  m_isDone=true;
  m_motor->isCalibarting=false;
}

void MotorCalibrator::moveDown()
{
  if(m_isDone) return;
  m_stepCounter+=m_stepAmout;
  m_motor->moveSteps(m_stepAmout);
}

void MotorCalibrator::moveUp()
{
  if(m_isDone) return;
  m_stepCounter=m_stepCounter-m_stepAmout>=0?m_stepCounter-m_stepAmout:0;
  m_motor->moveSteps(m_stepAmout);
}

void MotorCalibrator::setLower()
{
  
}

void MotorCalibrator::setUpper()
{
  m_stepCounter=0;
}