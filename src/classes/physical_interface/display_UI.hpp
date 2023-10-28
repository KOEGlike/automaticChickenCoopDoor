#ifndef DISPLAY_UI_HPP
#define DISPLAY_UI_HPP

#include <TimeLib.h>
#include <Arduino.h>
#include "driver/gpio.h"
#include <functional>

#include <math.h>


#include "button.hpp"
#include "custom_display_behavior.hpp"
#include "four_digit_time.hpp"
#include "counter.hpp"
#include "../async_handler.hpp"
#include "../interfaces.hpp"

class DisplayUI
{
  public:
    DisplayUI(ChickenDoorInterface *interface, DisplayUiConfig *config );
		void begin();
  protected:
		unsigned int offTime=100, onTime=100;
		uint8_t offShortMult=4, offLongMult=15, onTimeMult=4;

		ChickenDoorInterface *m_interface;
		MoveTimes times;
		bool isOn=false, isEditing=false;

		FourDigitTime digits;
		StateCounter currentSelectedSegment;
		StateCounter currentChangingTime;

		void defaultForShowNumber(int num);
		void switchDoorState();
		void onOffToggle();

		int  digitValueRouter(int state);
		void setTimeRouter(int digits, int state);
		void dotTimingRouter(int state);

		void mutateCurrentSegment(int amount);
		void moveCursor(bool forward);
		void editingToggle();
		void changeCurrentChangingTime();
		
		void startCalibration();
		void setCalibrationState();

		void btn1ShortFunc();
		void btn2ShortFunc();
		void btnPwrShortFunc();

		void btn1LongFunc();
		void btn2LongFunc();
		void btnPwrLongFunc();
		
		CustomDisplayBehavior display;
		
		Button button1;
		Button button2;
		Button buttonPwr;

};

#endif