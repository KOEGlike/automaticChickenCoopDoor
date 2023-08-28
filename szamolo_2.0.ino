#include <TimeLib.h>
#include <Arduino.h>
#include <TM1637Display.h>
#include "driver/gpio.h"
#include <functional>
#include <Preferences.h>
#include <math.h>

#define _CLK 21
#define _DIO 22
#define BTN1 19
#define BTN2 18

class Button {
  protected:
    int _pin;
    bool* _globalPressed;
    std::function<void()> _longPress, _press;
    bool pressed = false;
    unsigned long millisForLongPress = 300, debounceInMillis = 2, pressedForMillis = 0, pressStartInMillies;

  public:
    Button(
      int pin, bool* globalPressed, std::function<void()> press = []() {}, std::function<void()> longPress = []() {}) {
      _pin = pin;
      _globalPressed = globalPressed;
      _longPress = longPress;
      _press = press;
      pinMode(_pin, INPUT_PULLUP);
    }

    void check() {
      if (digitalRead(_pin) == HIGH) {
        if (pressed == true) {
          pressedForMillis = millis() - pressStartInMillies;
          //Serial.println(pressedForMillis);
        }
        pressed = false;
        *_globalPressed = false;
      } else {
        if (pressed == false) {
          pressStartInMillies = millis();
        }
        if (*_globalPressed == false) {
          pressed = true;
          *_globalPressed = true;
        }
      }

      if (pressed == false && *_globalPressed == false && pressedForMillis >= debounceInMillis) {
        if (pressedForMillis < millisForLongPress) {
          _press();
        } else {
          _longPress();
        }
      }

      if (pressed == false) {
        pressedForMillis = 0;
      }
    }
};
 
class CustomDisplayBeheviar : public TM1637Display {
  protected:
    unsigned long blinkStartInMillis, _offTime, _onTime, blinkEnd;
    int timesBlinked=0, timesToBlink=-1;
    uint8_t segmentsThatBlink;
    bool isBlinking = false, isContinuouslyBlinking = false;
    std::function<void()> bilinkSegmentsAnAmountOnEndFunc=[](){};
    void blinkCheck() {
      if (millis() - blinkStartInMillis >= _offTime && isBlinking) {
        isBlinking = false;
        setSegments(currentSegments);
        blinkEnd = millis();
        timesBlinked++;
      }
      if (isContinuouslyBlinking && millis() - blinkEnd >= _onTime && isBlinking == false) {
        blinkSegments(segmentsThatBlink, _offTime);
      }
      if(timesToBlink>0 && timesBlinked==timesToBlink)
      {
        blinkSegmentsContinuouslyOff();
        timesToBlink=-1;
        bilinkSegmentsAnAmountOnEndFunc();
      }
      
    }

  public:
    CustomDisplayBeheviar(uint8_t pinClk, uint8_t pinDIO)
      : TM1637Display(pinClk, pinDIO) {}


    void blinkSegments(uint8_t segmentsToBlink, unsigned long offTime = 50) {
      if (isBlinking == true) {
        return;
      }
      isBlinking = true;
      uint8_t beforeBlinkSegments[4];
      memcpy(beforeBlinkSegments, currentSegments, segmentsLength);
      uint8_t segments[4];
      memcpy(segments, currentSegments, segmentsLength);
      if (segmentsToBlink & 0b1000) {
        segments[0] = 0;
      }
      if (segmentsToBlink & 0b0100) {
        segments[1] = 0;
      }
      if (segmentsToBlink & 0b0010) {
        segments[2] = 0;
      }
      if (segmentsToBlink & 0b0001) {
        segments[3] = 0;
      }
      blinkStartInMillis = millis();
      _offTime = offTime;
      setSegments(segments);
      memcpy(currentSegments, beforeBlinkSegments, segmentsLength);
    }

    void blinkSegmentsContinuouslyOn(uint8_t segmentsToBlink, unsigned long offTime = 50, unsigned long onTime = 50) {
      isContinuouslyBlinking = true;
      segmentsThatBlink = segmentsToBlink;
      _onTime = onTime;
      blinkSegments(segmentsThatBlink, offTime);
    }

    void blinkSegmentsContinuouslyOff() {
      isContinuouslyBlinking = false;
    }

    void bilinkSegmentsAnAmount(uint8_t segmentsToBlink,unsigned int amount,   unsigned long offTime = 50, unsigned long onTime = 50,std::function<void()> onEnd=[](){})
    {
      timesBlinked=0;
      timesToBlink=amount;
      bilinkSegmentsAnAmountOnEndFunc=onEnd;
      blinkSegmentsContinuouslyOn(segmentsToBlink, offTime,onTime);
    }

    void check() {
      blinkCheck();
    }
};
class FourDigitTime {
  protected:
      int fourDiget = 0;  // Represents the time in the format HHMM
      // Add the specified number of minutes to the current time
      void addMinutes(uint16_t minutes) {
          int hoursToAdd = minutes / 60;
          minutes -= hoursToAdd * 60;
          minutes += fourDiget % 100;

          // Handle carry-over if minutes exceed 60
          if (minutes >= 60) {
              hoursToAdd++;
              minutes -= 60;
          }

          int hours = fourDiget / 100 + hoursToAdd;

          // Ensure hours stay within 0-23 range
          if (hours >= 24) {
              hours -= 24;
          }

          fourDiget = hours * 100 + minutes;
      }

      // Subtract the specified number of minutes from the current time
      void subtractMinutes(int minutes) {
          int hoursToSubtract = minutes / 60;
          minutes -= hoursToSubtract * 60;

          minutes = fourDiget % 100 - minutes;

          // Handle borrow if minutes become negative
          if (minutes < 0) {
              hoursToSubtract++;
              minutes += 60;
          }

          int hours = fourDiget / 100 - hoursToSubtract;

          // Ensure hours stay within 0-23 range
          if (hours < 0) {
              hours += 24;
          }

          fourDiget = hours * 100 + minutes;
      }

  public:
      // Set the time using hours and minutes
      void setTime(int hours, int minutes) {
          fourDiget = 100 * hours + minutes;
      }

      void setDigits(int digits)
      {
          fourDiget=digits;
      }

      // Get the current time digits (HHMM format)
      int getDigits() {
          return fourDiget;
      }

      // Mutate the time by adding or subtracting minutes
      void mutateMinutes(int minutes) {
          if (minutes < 0) {
              subtractMinutes(-minutes);  // If minutes is negative, subtract them
          } else {
              addMinutes(minutes);        // If minutes is positive, add them
          }
      }
      
      void mutateOneDigit(int placement, int mutate)
      {
        if(placement>3)
        {
          return;
        }
        else if(placement==0)
        {
          mutateMinutes(mutate*600);
        }
        else if(placement==1)
        {
          mutateMinutes(mutate*60);
        }
        else if(placement==2)
        {
        mutateMinutes(mutate*10);
        }
        else if(placement==3)
        {
        mutateMinutes(mutate);
        }
      }
};

class StateCounter
{
  private:
    int state;
    int _amountOfSates;
  public:
    StateCounter(int amountOfSates)
    {
      state=amountOfSates;
      _amountOfSates=amountOfSates;
    }
    void add(uint8_t amount=1)
    {
      state=(amount+state)%_amountOfSates;
    }
    void subtract(uint8_t amount=1)
    {
      state=(state-amount)%_amountOfSates;
      if(state <0)
      {
         state=_amountOfSates+state;
      }
    }
    uint8_t getState()
    {
      return state;
    }
    uint8_t getStateInBitMask()
    {
        return 1 << (_amountOfSates - 1 - state);
    }
    void setState(uint8_t counterSate) 
    {
      if(counterSate>_amountOfSates-1)
      {
        resetState();
        return;
      }
      state=counterSate;
    }
    void resetState()
    {
      state=_amountOfSates;
    }
};

unsigned char openTime=0, closeTime=0;
bool globalPressed = false, isEditing=false;

CustomDisplayBeheviar display(_CLK, _DIO);
Preferences preferences;
FourDigitTime digits;
StateCounter currentSelectedSegment(4);
StateCounter currentChangingTime(3);

void defalutForShowNumber(int num)
{
  display.showNumberDecEx(num, 0b11100000, true);
}

int  digitValueRouter(int state)
{
  switch(state) {
  case 0:
    return hour(now())*100+minute(now());
  case 1:
    return openTime;
  case 2:
    return closeTime;
  default:
    return 0;
  }
}

void setTimeRouter(int didgets, int state)
{
  switch(state) {
  case 0:
    setTime(didgets/100, didgets%100, 0, 0, 0, 0)
    break;
  case 1:
     openTime=didgets;
     break;
  case 2:
     closeTime=didgets;
    break;
  }
}

Button button1(
  BTN1, &globalPressed, []() {   
    digits.mutateOneDigit(currentSelectedSegment.getState(), 1);
    defalutForShowNumber(digits.getDigits());
  },
  []() {
    if(isEditing==false){
    isEditing=true
    display.setBrightness(7);
    currentSelectedSegment.add();
    currentChangingTime.add();
    digits.setDigits(digitValueRouter(currentChangingTime.getState()));
    defalutForShowNumber(digits.getDigits());
    display.blinkSegmentsContinuouslyOn(currentSelectedSegment.getStateInBitMask(), 100, 100);
    }
    else
    {
      isEditing=false;
      preferences.putUChar("openTime",openTime);
      preferences.putUChar("closeTime",closeTime);
      display.blinkSegmentsContinuouslyOff();
      display.setBrightness(0);
    }
  });

Button button2(
  BTN2, &globalPressed, []() {
    currentSelectedSegment.add();
    display.blinkSegmentsContinuouslyOn(currentSelectedSegment.getStateInBitMask(), 100, 100);
  },
  []() {
    setTimeRouter(digits.getDigits(), currentChangingTime.getState());
    currentChangingTime.add();
    currentSelectedSegment.setState(0);
    digits.setDigits(digitValueRouter(currentChangingTime.getState()));
    defalutForShowNumber(digits.getDigits());
    display.blinkSegmentsContinuouslyOn(currentSelectedSegment.getStateInBitMask(), 100, 100);
  });



void setup() {
  Serial.begin(9600);
  preferences.begin("times", false); 
  
  openTime=preferences.getUChar("openTime",0);
  closeTime=preferences.getUChar("closeTime", 0);

}

void checks() {
  button1.check();
  button2.check();
  display.check();
}

void loop() {
  checks();
}
