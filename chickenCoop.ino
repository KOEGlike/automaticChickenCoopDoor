#include <TimeLib.h>
#include <Arduino.h>
#include "driver/gpio.h"
#include <functional>
#include <Preferences.h>
#include <math.h>
#include<A4988.h>




#include "src/classes/counter.hpp"
#include "src/classes/chickenDoor.hpp"
#include "src/classes/async_handler.hpp"

#define CLK 21
#define DIO 22
#define BTN1 19
#define BTN2 18





ChickenDoor door();

void setup() {
  Serial.begin(115200);
  while (Serial.available() > 0){}
  Serial.println("Starting");
}

void loop() {
Async.check();
}
