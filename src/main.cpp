#include <TimeLib.h>
#include <Arduino.h>
#include "driver/gpio.h"
#include <functional>
#include <Preferences.h>
#include <math.h>
#include<A4988.h>

#include "classes/chickenDoor.hpp"
#include "classes/async_handler.hpp"

DisplayUiConfig displayUiConfig{4,5,6,7};

ChickenDoor *door= new ChickenDoor(displayUiConfig);

void setup() {
  Serial.begin(115200);
  
  Serial.println("Starting");
  delay(500);
  
}

void loop() {
 
Async.check();
}
