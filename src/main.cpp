#include "classes/chickenDoor.hpp"
#include "classes/async_handler.hpp"
#include "classes/interfaces.hpp"
#include "classes/physical_interface/button.hpp"

DisplayUiConfig displayUiConfig{
  16,//clk
  15,//dio
  4,//btn1 (left)
  6,//bnt2 (right)
  5//btn pwr
  };
MotorConfig motorConfig{
  200,//stepper motor steps amount
  10,//dir pin
  12,//step pin
  13//enable pin 
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