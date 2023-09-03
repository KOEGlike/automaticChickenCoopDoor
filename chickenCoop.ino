#include <TimeLib.h>
#include <Arduino.h>
#include "driver/gpio.h"
#include <functional>
#include <Preferences.h>
#include <math.h>
#include<A4988.h>

#include "src/classes/button.hpp"
#include "src/classes/custom_display_behavior.hpp"
#include "src/classes/four_didget_time.hpp"
#include "src/classes/counter.hpp"
#include "src/classes/chickenDoor.hpp"

#define CLK 21
#define DIO 22
#define BTN1 19
#define BTN2 18

ChickenDoor door(21, 22, 19, 18);

void setup() {
  Serial.begin(9600);
}

void loop() {
  door.checks();
}
