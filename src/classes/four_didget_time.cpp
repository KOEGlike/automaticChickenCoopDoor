#include "four_didget_time.hpp"
extern "C" {
  #include <stdlib.h>
  #include <inttypes.h>
}
#include <cmath>
#include <functional>
#include "counter.hpp"

void FourDigitTime::addMinutes(uint16_t minutes) {
    uint16_t hoursToAdd = minutes / 60;
    minutes -= hoursToAdd * 60;
    minutes += fourDigit % 100;

    if (minutes >= 60) {
        hoursToAdd++;
        minutes -= 60;
    }

    uint16_t hours = fourDigit / 100 + hoursToAdd;

    if (hours >= 24) {
        hours -= 24;
    }

    fourDigit = hours * 100 + minutes;
}

void FourDigitTime::subtractMinutes(uint16_t minutes) {
    uint16_t hoursToSubtract = minutes / 60;
    minutes -= hoursToSubtract * 60;

    minutes = fourDigit % 100 - minutes;

    if (minutes < 0) {
        hoursToSubtract++;
        minutes += 60;
    }

    uint16_t hours = fourDigit / 100 - hoursToSubtract;

    if (hours < 0) {
        hours += 24;
    }

    fourDigit = hours * 100 + minutes; 
}

void FourDigitTime::setTime(int hours, int minutes) {
    fourDigit = 100 * hours + minutes;
}

void FourDigitTime::setDigits(int digits) {
    fourDigit = digits;
}

int FourDigitTime::getDigits() {
    return fourDigit;
}

void FourDigitTime::mutateMinutes(int minutes) {
    if (minutes < 0) {
        subtractMinutes(-minutes);
    } else {
        addMinutes(minutes);
    }
}

void FourDigitTime::mutateOneDigit(int placement, int mutate,bool stepover=true) {
     switch (placement) {
    case 0:
        mutateMinutes(mutate * 600);
        break;
    case 1:
        mutateMinutes(mutate * 60);
        break;
    case 2:
        mutateMinutes(mutate * 10);
        break;
    case 3:
        mutateMinutes(mutate);
        break;
}

}

void FourDigitTime::mutateMinutesWithoutStepover(uint16_t mutate, uint8_t placement){
switch (placement) {
    case 0:
        uint16_t maxValue=(fourDigit/100)%10>4?1:2;
        if(fourDigit/1000+mutate<0)
        {
            fourDigit=fourDigit-(fourDigit/1000)*1000+(maxValue+(fourDigit/1000+mutate)%(maxValue+1));
            break;
        }
        fourDigit=fourDigit-(fourDigit/1000)*1000+(fourDigit/1000+mutate)%(maxValue+1);
        break;
    case 1:
    case 3:
        const int num=(int)(fourDigit % (int)(pow(10, placement + 1)))/(int)(pow(10, placement));
        if (num+mutate> 9) 
        {
            fourDigit=fourDigit-num*(int)(pow(10, placement))+((num+mutate)%(9+1));
        }

        break;
    case 2:

        break;
}
}

