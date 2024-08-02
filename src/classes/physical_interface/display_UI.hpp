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
		/// @brief the time to wait before turning on/off the display
		unsigned int offTime=100, onTime=100;
		
		/// @brief  multiplier for the on/off time for display on different states
		uint8_t offShortMult=4, offLongMult=15, onTimeMult=4;
		uint32_t asyncIdForClock;

		/// @brief when the motor moves
		MoveTimes times;

		/// @brief if the display is on
		bool isOn=false;
		/// @brief if the ui is editing times
		bool isEditing=false;

		/// @brief pointer to the motor in the main class
		Motor* motor;
		/// @brief pointer to the times manager in the main class
		TimesManager* timesManager;
		/// @brief pointer to the sleep handler in the main class
		SleepHandler* sleepHandler;

		/// @brief the pointer configuration for the display in the main class
		DisplayUiConfig *config;

		/// @brief the current editing time
		FourDigitTime digits;
		/// @brief counter of 4 states for the 4 segments of the display
		StateCounter currentSelectedSegment;
		/// @brief counter of 3 states for the 3 different times to change: 
		/// 1. the opening time
		/// 2. the closing time
		/// 3. the current time
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
		
		/// @brief the display class, extended to have custom behaviors
		CustomDisplayBehavior display;
		
		Button button1;
		Button button2;
		Button buttonPwr;

		tmElements_t getTimeInElements();

};