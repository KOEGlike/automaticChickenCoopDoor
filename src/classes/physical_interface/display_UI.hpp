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
    DisplayUI(
		std::shared_ptr<TimesManager> timesManager,
		std::shared_ptr<Motor> motor, 
		std::shared_ptr<DisplayUiConfig> config, 
		std::shared_ptr<SleepHandler> sleepHandler
	);
	void begin();
	std::shared_ptr<DisplayUiConfig> getConfig();
  protected:
		/// @brief the time to wait before turning on/off the display
		unsigned int offTime=100, onTime=100;
		
		/// @brief  multiplier for the on/off time for display on different states
		uint8_t offShortMult=4, offLongMult=15, onTimeMult=4;
		TaskHandle_t asyncIdForClock;

		/// @brief when the motor moves
		MoveTimes times;

		/// @brief if the display is on
		bool isOn=false;
		/// @brief if the ui is editing times
		bool isEditing=false;

		/// @brief pointer to the motor in the main class
		std::shared_ptr<Motor> motor;
		/// @brief pointer to the times manager in the main class
		std::shared_ptr<TimesManager> timesManager;
		/// @brief pointer to the sleep handler in the main class
		std::shared_ptr<SleepHandler> sleepHandler;

		/// @brief the pointer configuration for the display in the main class
		std::shared_ptr<DisplayUiConfig>config;

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
		/// @brief switch the door state, open/close it
		void switchDoorState();
		/// @brief turn on or off the display
		void onOffToggle();
		
		/// @brief enable the clock, show the current time
		void enableClock();
		/// @brief disable the clock, stop showing the current time
		void disableClock();

		/// @brief gets the time of : current time(0), open time(1), close time(2) 
		/// in a format of HHMM
		/// @param state the state of the time to get
		int  digitValueRouter(int state);
		/// @brief sets the time of : current time(0), open time(1), close time(2) on the display
		/// in a format of HHMM
		/// @param digits the time to set
		/// @param state the state of the time to set
		void setTimeRouter(int digits, int state);
		/// @brief  change how many times the dots blink then delay
		/// @param state the state of the time to change
		void dotTimingRouter(int state);
		/// @brief display the text for the current time(0), open time(1), close time(2)
		/// @param state the state of the time to display
		void textValueRouter(int state);

		/// @brief change the current segment
		/// @param amount the amount to change the segment
		void mutateCurrentSegment(int amount);
		/// @brief move the cursor
		/// @param forward is true if the cursor is moving forward is false if the cursor is moving backward
		void moveCursor(bool forward);
		/// @brief edits the open && close && current time
		void editingToggle();
		/// @brief change the current type time, so close, open or current time, it will loop
		void changeCurrentChangingTime();
		
		/// @brief start the motor calibration
		void startCalibration();
		/// @brief set the calibration state, so if the motor is at 35 steps then it will set the curent state(open/close) to 35
		void setCalibrationState();
		/// @brief turn the motor a amount of steps for calibration
		/// @param steps the amount of steps to turn
		/// @param isClockwise true if the motor is turning clockwise, false if the motor is turning counter clockwise
		void calibrationTurn(uint steps, bool isClockwise);

		/// @brief what happens when btn1 is pressed a single time shortly
		void btn1ShortFunc();
		/// @brief what happens when btn2 is pressed a single time shortly
		void btn2ShortFunc();
		/// @brief what happens when pwr-btn is pressed a single time shortly
		void btnPwrShortFunc();

		/// @brief what happens when btn1 is pressed a single time for a long time
		void btn1LongFunc();
		/// @brief what happens when btn2 is pressed a single time for a long time
		void btn2LongFunc();
		/// @brief what happens when pwr-btn is pressed a single time for a long time
		void btnPwrLongFunc();
		
		/// @brief the display class, extended to have custom behaviors
		CustomDisplayBehavior customDisplay;
		
		uint button1, button2, buttonPwr;

		tmElements_t getTimeInElements();

};