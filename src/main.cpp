#include <TimeLib.h>
#include <Arduino.h>
#include "driver/gpio.h"
#include <functional>
#include <Preferences.h>
#include <math.h>
#include<A4988.h>


#include "classes/counter.hpp"
#include "classes/chickenDoor.hpp"
#include "classes/async_handler.hpp"

#define CLK 21
#define DIO 22
#define BTN1 19
#define BTN2 18

ChickenDoor *door= new ChickenDoor();

void setup() {
  Serial.begin(115200);
  
  Serial.println("Starting");
  //delay(500);
}

void loop() {
 
Async.check();
}
