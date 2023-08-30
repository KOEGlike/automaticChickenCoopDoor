#ifndef FOURDIGITTIME_HPP
#define FOURDIGITTIME_HPP


class FourDigitTime {
    protected:
        int fourDigit = 0;  // Represents the time in the format HHMM

        void addMinutes(uint16_t minutes);
        void subtractMinutes(int minutes);

    public:
        void setTime(int hours, int minutes);
        void setDigits(int digits);
        int getDigits();
        void mutateMinutes(int minutes);
        void mutateOneDigit(int placement, int mutate);
};

#endif