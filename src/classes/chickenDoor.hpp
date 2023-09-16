#ifndef CHICKEN_DOOR_HPP
#define CHICKEN_DOOR_HPP

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
#include "async_handler.hpp"


class ChickenDoor
{
  	public:
    	ChickenDoor(uint8_t clkPin,uint8_t dioPin, uint8_t btn1Pin, uint8_t btn2Pin);
  	private:
		unsigned int offTime=100, onTime=100;
		uint8_t offShortMult=4, offLongMult=10, onTimeMult=4;

		uint8_t btn1, btn2, clk, dio;
		unsigned int openTime=0, closeTime=0;
		bool globalPressed = false, isEditing=false;

		CustomDisplayBehavior display{21, 22};
		Preferences preferences;
		FourDigitTime digits;
		StateCounter currentSelectedSegment{4};
		StateCounter currentChangingTime{3};

		void defalutForShowNumber(int num);
		
		int  digitValueRouter(int state);
		void setTimeRouter(int didgets, int state);
		void dotTimeingRouter(int state);

		void addToCurrentSegment();;
		void moveCursorForward();
		void editingTogle();
		void changeCurrentChangingTime();

		Button button1
		{
		19, [&]() {   
			addToCurrentSegment();
		},
		[&]() {
			editingTogle();
		}, &globalPressed};

		Button button2{
		18, [&]() {
			moveCursorForward();
		},
		[&]() {
			changeCurrentChangingTime();
		}, &globalPressed};

};

#endif