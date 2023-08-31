#include "four_didget_time.hpp"
extern "C" {
  #include <stdlib.h>
  #include <inttypes.h>
}

void FourDigitTime::addMinutes(uint16_t minutes) {
    int hoursToAdd = minutes / 60;
    minutes -= hoursToAdd * 60;
    minutes += fourDigit % 100;

    if (minutes >= 60) {
        hoursToAdd++;
        minutes -= 60;
    }

    int hours = fourDigit / 100 + hoursToAdd;

    if (hours >= 24) {
        hours -= 24;
    }

    fourDigit = hours * 100 + minutes;
}

void FourDigitTime::subtractMinutes(int minutes) {
    int hoursToSubtract = minutes / 60;
    minutes -= hoursToSubtract * 60;

    minutes = fourDigit % 100 - minutes;

    if (minutes < 0) {
        hoursToSubtract++;
        minutes += 60;
    }

    int hours = fourDigit / 100 - hoursToSubtract;

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

void FourDigitTime::mutateOneDigit(int placement, int mutate) {
    if (placement > 3) {
        return;
    } else if (placement == 0) {
        mutateMinutes(mutate * 600);
    } else if (placement == 1) {
        mutateMinutes(mutate * 60);
    } else if (placement == 2) {
        mutateMinutes(mutate * 10);
    } else if (placement == 3) {
        mutateMinutes(mutate);
    }
}
