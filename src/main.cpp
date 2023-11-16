#include "classes/chickenDoor.hpp"
#include "classes/async_handler.hpp"
#include "classes/interfaces.hpp"
#include "classes/physical_interface/button.hpp"

DisplayUiConfig displayUiConfig{
  10,//clk
  11,//dio
  8,//btn1 (left)
  9,//bnt2 (right)
  3//btn pwr
  };
MotorConfig motorConfig{
  200,//stepper motor steps amount
  4,//dir pin
  5,//step pin
  7,//enable pin
  17,//m0
  16,//m1
  15//m2
  };

ChickenDoor door(&displayUiConfig, &motorConfig);

void setup() {
  Serial.begin(115200);
  ButtonManager.begin();
  door.begin();
}

void loop() 
{
  Async.check();
}

