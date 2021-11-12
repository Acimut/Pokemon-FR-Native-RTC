#include "include/global.h"
#include "include/event_data.h"
#include "include/rtc.h"
#include "include/time_events.h"
#include "include/field_specials.h"
// #include "lottery_corner.h"
// #include "dewford_trend.h"
// #include "tv.h"
#include "include/field_weather.h"
// #include "berry.h"
#include "include/main.h"
#include "include/overworld.h"
#include "include/wallclock.h"

static void UpdatePerDay(struct Time *localTime);
static void UpdatePerMinute(struct Time *localTime);

static void InitTimeBasedEvents(void)
{
    FlagSet(FLAG_SYS_CLOCK_SET);
    RtcCalcLocalTime();
    gSaveBlock2Ptr->lastBerryTreeUpdate = gLocalTime;
    VarSet(VAR_DAYS, gLocalTime.days);
}

void DoTimeBasedEvents(void)
{
    if (FlagGet(FLAG_SYS_CLOCK_SET)) // && !InPokemonCenter()
    {
        RtcCalcLocalTime();
        UpdatePerDay(&gLocalTime);
        UpdatePerMinute(&gLocalTime);
    }
}

static void UpdatePerDay(struct Time *localTime)
{
    u16 *days = GetVarPointer(VAR_DAYS);
    u16 daysSince;

    if (*days != localTime->days && *days <= localTime->days)
    {
        daysSince = localTime->days - *days;
        ClearDailyFlags();
        // UpdateDewfordTrendPerDay(daysSince);
        // UpdateTVShowsPerDay(daysSince);
        // UpdateWeatherPerDay(daysSince);
        UpdatePartyPokerusTime(daysSince);
        // UpdateMirageRnd(daysSince);
        // UpdateBirchState(daysSince);
        // UpdateFrontierManiac(daysSince);
        // UpdateFrontierGambler(daysSince);
        // SetShoalItemFlag(daysSince);
        // SetRandomLotteryNumber(daysSince);
        *days = localTime->days;
    }
}

static void UpdatePerMinute(struct Time *localTime)
{
    struct Time difference;
    int minutes;

    CalcTimeDifference(&difference, &gSaveBlock2Ptr->lastBerryTreeUpdate, localTime);
    minutes = 24 * 60 * difference.days + 60 * difference.hours + difference.minutes;
    if (minutes != 0)
    {
        if (minutes >= 0)
        {
            // BerryTreeTimeUpdate(minutes);
            gSaveBlock2Ptr->lastBerryTreeUpdate = *localTime;
        }
    }
}

static void ReturnFromStartWallClock(void)
{
    InitTimeBasedEvents();
    SetMainCallback2(CB2_ReturnToFieldContinueScriptPlayMapMusic);
}
//special 0x9A
void StartWallClock(void)
{
    SetMainCallback2(CB2_StartWallClock);
    gMain.savedCallback = ReturnFromStartWallClock;
}
