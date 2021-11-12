#include "include/global.h"
#include "include/event_data.h"
#include "include/item_menu.h"
#include "include/quest_log.h"

#define NUM_DAILY_FLAGS   (DAILY_FLAGS_END - DAILY_FLAGS_START + 1) // RTC code /new
#define DAILY_FLAGS_SIZE    (NUM_DAILY_FLAGS / 8)                   // RTC code /new

void ClearDailyFlags(void)  // RTC code /new
{
    memset(gSaveBlock1Ptr->flags + (DAILY_FLAGS_START / 8), 0, DAILY_FLAGS_SIZE);
}

void DisableResetRTC(void)
{
    VarSet(VAR_RESET_RTC_ENABLE, 0);        // RTC code update //actualización estética, no hay que compilarlo
    FlagClear(FLAG_SYS_RESET_RTC_ENABLE);   // ...
}

void EnableResetRTC(void)
{
    VarSet(VAR_RESET_RTC_ENABLE, 0x0920);   // ...
    FlagSet(FLAG_SYS_RESET_RTC_ENABLE);     // ...
}

bool32 CanResetRTC(void)
{
    if (!FlagGet(FLAG_SYS_RESET_RTC_ENABLE))    // ...
        return FALSE;
    if (VarGet(VAR_RESET_RTC_ENABLE) != 0x0920) // ...
        return FALSE;
    return TRUE;
}