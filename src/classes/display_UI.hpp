#ifndef DISPLAY_UI_HPP
#define DISPLAY_UI_HPP

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


class DisplayUI
{
  public:
    DisplayUI(std::function<void(unsigned int openTime, unsigned int closeTime)> onSetTime,uint8_t clkPin,uint8_t dioPin, uint8_t btn1Pin, uint8_t btn2Pin);
  private:
		unsigned int offTime=100, onTime=100;
		uint8_t offShortMult=4, offLongMult=15, onTimeMult=4;

		std::function<void(unsigned int openTime, unsigned int closeTime)> m_onSetTime;

		unsigned int openTime=0, closeTime=0;
		tmElements_t currentTime;
		bool globalPressed = false, isEditing=false;

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
		
		uint8_t btn1, btn2, clk, dio;
		CustomDisplayBehavior display{21, 22};
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