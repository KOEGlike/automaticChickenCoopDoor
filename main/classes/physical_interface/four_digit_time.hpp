#ifndef FOURDIGITTIME_HPP
#define FOURDIGITTIME_HPP

extern "C"
{
#include <stdlib.h>
#include <inttypes.h>
}
#include <cmath>
#include <functional>
#include "counter.hpp"

class FourDigitTime
{
public:
  /// @brief the constructor for the FourDigitTime class
  FourDigitTime();

  /// @brief sets the time
  /// @param hours how many hours
  /// @param minutes how many minutes
  void setTime(int hours, int minutes);

  /// @brief sets the digits HHMM
  /// @param digits the digits to set
  void setDigits(int digits);

  /// @brief gets the digits HHMM
  int getDigits();

  /// @brief mutates M2 by the amount of minutes
  /// @param minutes the amount of minutes to mutate by
  void mutateMinutes(int minutes);

  /// @brief placement is the digit to mutate, mutate is the amount to mutate by
  /// mutate means add or subtract the amount from the digit
  void mutateOneDigit(int placement, int mutate, bool stepOver = true);

protected:
  /// @brief whether to step over the next digit when mutating
  bool m_stepOver = true;

  /// @brief what happens when H1 is mutated
  /// @param amount the amount to mutate (add/subtract) by
  void H1OnMutate(int times);

  /// @brief what happens when H2 is mutated
  /// @param amount the amount to mutate (add/subtract) by
  void H2OnMutate(int times);

  /// @brief what happens when M1 is mutated
  /// @param amount the amount to mutate (add/subtract) by
  void M1OnMutate(int times);

  /// @brief what happens when M2 is mutated
  /// @param amount the amount to mutate (add/subtract) by
  void M2OnMutate(int times);

  /// @brief the first digit of the hour
  StateCounter H1;
  /// @brief the second digit of the hour
  StateCounter H2;
  /// @brief the first digit of the minute
  StateCounter M1;
  /// @brief the second digit of the minute
  StateCounter M2;
};

#endif