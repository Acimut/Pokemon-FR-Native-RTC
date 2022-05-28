#include "global.h"
#include "day_div.h"
#include "rtc.h"

void DayDiv_Update(void)
{
    //s16 days;
    s8 hours;
    s8 minutes;
    s8 seconds;

    //days = gLocalTime.days;
    hours = gLocalTime.hours;
    minutes = gLocalTime.minutes;
    seconds = gLocalTime.seconds;

    gDayTime.hours = (hours % DAY_MODE) * DAY_PER_24 + (minutes / MIN_PER_HOUR);
    gDayTime.minutes = ((minutes % MIN_PER_HOUR) * DAY_PER_24) + (seconds / MIN_PER_HOUR);
    gDayTime.seconds = (seconds % MIN_PER_HOUR) * DAY_PER_24;
}



