#pragma once

#include <TimeLib.h>
#include <Arduino.h>
#include "driver/gpio.h"
#include <functional>

#include <math.h>

#include "../times_manager.hpp"
#include "button.hpp"
#include "custom_display_behavior.hpp"
#include "four_digit_time.hpp"
#include "counter.hpp"
#include "../async_handler.hpp"
#include "../interfaces.hpp"
#include "../motor.hpp"
#include "../times_manager.hpp"
#include "../sleep_handler.hpp"

class DisplayUiConfig;
class ChickenDoor;
class MoveTimes;

class DisplayUI
{
  public:
    DisplayUI(TimesManager* timesManager,Motor*motor, DisplayUiConfig *config, SleepHandler* sleepHandler);
		void begin();
		DisplayUiConfig* getConfig();
  protected:
		unsigned int offTime=100, onTime=100;
		uint8_t offShortMult=4, offLongMult=15, onTimeMult=4;
		uint32_t asyncIdForClock;

		MoveTimes times;
		bool isOn=false, isEditing=false;

		Motor* motor;
		TimesManager* timesManager;
		SleepHandler* sleepHandler;

		DisplayUiConfig *config;

		FourDigitTime digits;
		StateCounter currentSelectedSegment;
		StateCounter currentChangingTime;

		void defaultForShowNumber(int num);
		void switchDoorState();
		void onOffToggle();

		int  digitValueRouter(int state);
		void setTimeRouter(int digits, int state);
		void dotTimingRouter(int state);
		void textValueRouter(int state);

		void mutateCurrentSegment(int amount);
		void moveCursor(bool forward);
		void editingToggle();
		void changeCurrentChangingTime();
		
		void startCalibration();
		void setCalibrationState();
		void calibrationTurn(uint steps, bool isClockwise);

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

		tmElements_t getTimeInElements();

};