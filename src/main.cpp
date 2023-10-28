#include "classes/chickenDoor.hpp"
#include "classes/async_handler.hpp"
#include "classes/interfaces.hpp"
#include "classes/physical_interface/button.hpp"

DisplayUiConfig displayUiConfig{
  5,//clk
  4,//dio
  15,//btn1 (left)
  16,//bnt2 (right)
  17//btn pwr
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