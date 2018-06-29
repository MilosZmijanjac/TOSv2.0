#ifndef RTC_H
#define RTC_H

#include "common.h"

typedef struct rtc
{
    u8int seconds;
    u8int minutes;
    u8int hours;
    u8int days;
    u8int months;
    u8int years;
    u8int centuries;
} RTC;

void rtc_init(void);
void rtc_read(void);
RTC* rtc_getRTC(void);

#endif

