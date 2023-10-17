#include "classes/chickenDoor.hpp"
#include "classes/async_handler.hpp"
#include "classes/interfaces.hpp"
#include "classes/physical_interface/button.hpp"

//DisplayUiConfig displayUiConfig{4,5,6,7};
bool haha=false;
MotorConfig motorConfig
{
200, //step amount
16,//dirPin
17,//stepPin
18//enablePin
};
MotorCalibrationState calibState{true, 0};
uint currentState;
MotorInterface motorInterface{[&](){return currentState;}, [&](uint state){currentState = state;}, [&](){return calibState;}, [&](MotorCalibrationState state){calibState = state;}, [](){}, [](){}, [](){}};;
Motor motor{&motorConfig, &motorInterface};
Button btn1{9, 
[&](){motor.calibrator.start(5);}, 
[](){}, 
&haha};
Button btn2{8, 
[&](){motor.calibrator.turn(true);}, 
[&](){motor.calibrator.turn(false);}, 
&haha};
Button btn3{8, 
[&](){motor.calibrator.setFirstState();}, 
[&](){motor.calibrator.setSecondState();}, 
&haha};
//ChickenDoor door(&displayUiConfig, &motorConfig);

void setup() {
  Serial.begin(115200);
  ButtonManager.begin();
  btn1.begin();
  btn2.begin();
  btn3.begin();
  //door.begin();
}

void loop() 
{
  Async.check();
}