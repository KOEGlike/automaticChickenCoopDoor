#include "motor.hpp"	

Motor::Motor(MotorConfig config, MotorInterface interface): 
motor{config.steps, config.dir, config.step, config.enable, config.ms1,config.ms2,config.ms3}, 
m_interfece{interface}
{
 
}

void Motor::changeState(float percentage)
{
}

void Motor::begin()
{
  motor.begin();
}

void Motor::moveSteps(int steps)
{

}