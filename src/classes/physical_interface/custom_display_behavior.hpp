#pragma once

#include <TM1637Display.h>
#include <functional>
#include "../async_handler.hpp"
#include <vector>

extern "C"
{
#include <stdlib.h>
#include <inttypes.h>
}

class CustomDisplayBehavior
{
public:
  CustomDisplayBehavior(uint8_t pinClk, uint8_t pinDIO);
  ~CustomDisplayBehavior();

  TM1637Display display;

  void begin();

  /// @brief blink the segments, if another blink is already happening it will override it
  /// @param segmentsToBlink segments
  /// @param offTime the off time in milliseconds
  /// @param onTime the on time in milliseconds
  /// @param timesToBlink the times to blink
  /// @param onEnd the function to call when the blinking ends
  void blinkSegments(uint8_t segmentsToBlink, unsigned long offTime, unsigned long onTime = 0, uint32_t timesToBlink = 1, std::function<void()> onEnd = []() {});
  
  /// @brief stop the blinking of the segments
  void blinkSegmentsOff();

  /// @brief blink the dots/colons on display
  /// @param dots Dot/Colon enable. The argument is a bitmask, with each bit corresponding to a dot
  ///        between the digits (or colon mark, as implemented by each module). i.e.
  ///        For displays with dots between each digit:
  ///        * 0.000 (0b10000000)
  ///        * 00.00 (0b01000000)
  ///        * 000.0 (0b00100000)
  ///        * 0.0.0.0 (0b11100000)
  ///        For displays with just a colon:
  ///        * 00:00 (0b01000000)
  ///        For displays with dots and colons colon:
  ///        * 0.0:0.0 (0b11100000)
  /// @param offTime the time the LEDs are off
  /// @param onTime the time the LEDs are on
  /// @param timesToBlink how many times to blink
  /// @param onEnd the function to call when the blinking ends
  void blinkDots(uint8_t dots, unsigned long offTime = 50, unsigned long onTime = 0, uint32_t timesToBlink = 1, std::function<void()> onEnd = []() {});

  /// @brief stop the blinking of the dots
  void blinkDotsOff();

  /// @brief blink the dots/colons on display periodically,
  /// for example blink-delay-blink-long_delay-blink-delay-blink-long_delay
  /// @param dots Dot/Colon enable. The argument is a bitmask, with each bit corresponding to a dot
  ///        between the digits (or colon mark, as implemented by each module). i.e.
  ///        For displays with dots between each digit:
  ///        * 0.000 (0b10000000)
  ///        * 00.00 (0b01000000)
  ///        * 000.0 (0b00100000)
  ///        * 0.0.0.0 (0b11100000)
  ///        For displays with just a colon:
  ///        * 00:00 (0b01000000)
  ///        For displays with dots and colons colon:
  ///        * 0.0:0.0 (0b11100000)
  /// @param offTime the time the LEDs are off
  /// @param onTime the time the LEDs are on
  /// @param timeBetween the long delay between blinks
  /// @param timesToBlinkInOnePeriod how many times to blink
  /// @param onEnd the function to call when the blinking ends
  /// @param periods how many periods to blink
  void blinkDotsPeriodically(uint8_t dots, uint32_t periods,unsigned long offTime=50, unsigned long onTime=0, unsigned long timeBetween=150, uint32_t timesToBlinkInOnePeriod=1, std::function<void()> onEnd = []() {});

  /// @brief scroll the segments
  /// @param segments the segments to scroll
  /// @param millisForOneMove the time for one move
  /// @param amount the amount to scroll
  /// @param onEnd the function to call when the scrolling ends
  void scrollSegmentsAnAmount(std::vector<uint8_t> segments, unsigned long millisForOneMove, int amount, std::function<void()> onEnd = []() {});
  void scrollSegmentsOff();

  /// @brief stop all activities, including blinking and scrolling
  void stopAllActivities();

protected:
  std::vector<uint8_t> segmentsToScroll;

  struct id
  {
    uint32_t on, off;
  };

  struct scrollData
  {
    int cycles = 0;
    int currentCycle = 0;
    std::vector<uint8_t> segments;
    int amount = 0;
    std::function<void()> onEnd = []() {};
    uint32_t asyncId;
  };

  id segmentsAsyncId = {0, 0};

  id dotsAsyncId = {0, 0};
  uint32_t dotsAsyncIdPeriodically = 0;

  scrollData scrollData;
};
