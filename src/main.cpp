#include "classes/chickenDoor.hpp"
#include "classes/async_handler.hpp"
#include "classes/interfaces.hpp"

DisplayUiConfig displayUiConfig{4,5,6,7};
MotorConfig motorConfig{9,10,11,12,13};

ChickenDoor door(&displayUiConfig);

void setup() {
  Serial.begin(115200);
  
  Serial.println("Starting");
 door.begin();
  
}

void loop() {
Async.check();
}
