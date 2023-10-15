#include "classes/chickenDoor.hpp"
#include "classes/async_handler.hpp"
#include "classes/interfaces.hpp"
#include "classes/physical_interface/button.hpp"

DisplayUiConfig displayUiConfig{4,5,6,7};
MotorConfig motorConfig{9,10,11,12,13};

ChickenDoor door(&displayUiConfig, &motorConfig);

void setup() {
  Serial.begin(115200);
  ButtonManager.begin();
  door.begin();
}

void loop() {
Async.check();
}
