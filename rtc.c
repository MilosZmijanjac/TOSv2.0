#include "rtc.h"
#include "kheap.h"
#include "common.h"



static RTC *rtc = 0;

#define CMOS_ADDRESS    0x70
#define CMOS_DATA       0x71

#define SECONDS_KEY     0x00
#define MINUTES_KEY     0x02
#define HOURS_KEY       0x04
#define DAYS_KEY        0x08
#define MONTHS_KEY      0x07
#define YEARS_KEY       0x09
#define CENTURIES_KEY   0x32

static u8int __rtc_checkIfUpdateIsInProgress(void)
{
    __asm__ __volatile__ ("cli");

    outb(CMOS_ADDRESS, 0x0A);
    u8int ret = inb(CMOS_DATA) & 0x80;

__asm__ __volatile__ ("sti");
    return ret;
}

static u8int __rtc_getRegisterValue(u8int reg)
{
__asm__ __volatile__ ("cli");

    while (__rtc_checkIfUpdateIsInProgress());

    outb(CMOS_ADDRESS, reg);
    u8int ret = inb(CMOS_DATA);

    __asm__ __volatile__ ("sti");

    return ret;
}

void rtc_init(void)
{
    rtc = (RTC*)kalloc(sizeof(RTC));

    rtc_read();
}

void rtc_read(void)
{
    if (rtc == 0)
        return;

    rtc->seconds    = __rtc_getRegisterValue(SECONDS_KEY);
    rtc->minutes    = __rtc_getRegisterValue(MINUTES_KEY);
    rtc->hours      = __rtc_getRegisterValue(HOURS_KEY);
    rtc->days       = __rtc_getRegisterValue(DAYS_KEY);
    rtc->months     = __rtc_getRegisterValue(MONTHS_KEY);
    rtc->years      = __rtc_getRegisterValue(YEARS_KEY);
    rtc->centuries  = __rtc_getRegisterValue(CENTURIES_KEY);

    u8int registerB = __rtc_getRegisterValue(0x0B);

    if (!(registerB & 0x04))
    {
        rtc->hours      = (rtc->hours       & 0x0F) + (rtc->hours       / 16) * 10;
        rtc->seconds    = (rtc->seconds     & 0x0F) + (rtc->seconds     / 16) * 10;
        rtc->minutes    = (rtc->minutes     & 0x0F) + (rtc->minutes     / 16) * 10;
        rtc->days       = (rtc->days        & 0x0F) + (rtc->days        / 16) * 10;
        rtc->months     = (rtc->months      & 0x0F) + (rtc->months      / 16) * 10;
        rtc->years      = (rtc->years       & 0x0F) + (rtc->years       / 16) * 10;
        rtc->centuries  = (rtc->centuries   & 0x0F) + (rtc->centuries   / 16) * 10;
    }

    if (!(registerB & 0x02) && (rtc->hours & 0x80))
        rtc->hours = ((rtc->hours & 0x7F) + 14) % 24;
}

RTC* rtc_getRTC(void)
{
    return rtc;
}

