#include "global.h"
#include "play_time.h"
#include "rtc.h"
#include "day_div.h"

//static IWRAM 
extern u8 sPlayTimeCounterState;

enum
{
    STOPPED,
    RUNNING,
    MAXED_OUT,
};


void PlayTimeCounter_Update(void)
{
    if (sPlayTimeCounterState != RUNNING)
        return;

    gSaveBlock2Ptr->playTimeVBlanks++;

    if (gSaveBlock2Ptr->playTimeVBlanks < 60)
        return;

    gSaveBlock2Ptr->playTimeVBlanks = 0;
    gSaveBlock2Ptr->playTimeSeconds++;

    if (!(gSaveBlock2Ptr->playTimeSeconds % MIN_PER_HOUR))
        RtcCalcLocalTime();

    if (gSaveBlock2Ptr->playTimeSeconds < 60)
        return;

    gSaveBlock2Ptr->playTimeSeconds = 0;
    gSaveBlock2Ptr->playTimeMinutes++;

    //RtcCalcLocalTime(); //Forces gLocalTime refresh once per minute (useful for DNS)
    
    if (gSaveBlock2Ptr->playTimeMinutes < 60)
        return;

    gSaveBlock2Ptr->playTimeMinutes = 0;
    gSaveBlock2Ptr->playTimeHours++;

    if (gSaveBlock2Ptr->playTimeHours > 999)
        PlayTimeCounter_SetToMax();

}

