#ifndef CHICKEN_DOOR_HPP
#define STATE_COUNTER_HPP

#include <TimeLib.h>
#include <Arduino.h>
#include "driver/gpio.h"
#include <functional>
#include <Preferences.h>
#include <math.h>
#include<A4988.h>

#include "button.hpp"
#include "custom_display_behavior.hpp"
#include "four_didget_time.hpp"
#include "counter.hpp"

class ChickenDoor
{
  public:
    ChickenDoor(uint8_t clkPin,uint8_t dioPin, uint8_t btn1Pin, uint8_t btn2Pin);
    
    void checks() ;
  private:
  uint8_t btn1, btn2, clk, dio;
  unsigned char openTime=0, closeTime=0;
  bool globalPressed = false, isEditing=false;

  CustomDisplayBehavior display{clk, dio};
  Preferences preferences;
  FourDigitTime digits;
  StateCounter currentSelectedSegment{4};
  StateCounter currentChangingTime{3};

  void defalutForShowNumber(int num);

  int  digitValueRouter(int state);

  void setTimeRouter(int didgets, int state);

  void addToCurrentSegment();;
  void moveCursorForward();
  void ediitingTogle();
  void changeCurrentChangingTime();

  Button button1
  {
    btn1, &globalPressed, [&]() {   
      addToCurrentSegment();
    },
    [&]() {
      ediitingTogle();
    }};

  Button button2{
    btn2, &globalPressed, [&]() {
      moveCursorForward();
    },
    [&]() {
      changeCurrentChangingTime();
    }};

};

#endif