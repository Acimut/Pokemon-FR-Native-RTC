#include "include/global.h"
#include "include/gflib.h"
#include "include/bike.h"
#include "include/clock.h"  // RTC code
#include "include/event_data.h"
#include "include/field_camera.h"
#include "include/field_effect_helpers.h"
#include "include/field_player_avatar.h"
#include "include/fieldmap.h"
#include "include/metatile_behavior.h"
#include "include/overworld.h"
#include "include/quest_log.h"
#include "include/script.h"
#include "include/task.h"
#include "include/constants/field_tasks.h"
#include "include/constants/metatile_labels.h"
#include "include/constants/songs.h"

#define tState           data[0]    // RTC code

void RunTimeBasedEvents(s16 *data)   // RTC code /new
{
    switch (tState)
    {
        case 0:
            if (*gMain.vblankCounter1 & 0x1000)
            {
                DoTimeBasedEvents();
                tState++;
            }
            break;
        case 1:
            if (!(*gMain.vblankCounter1 & 0x1000))
            {
                tState--;
            }
            break;
    }
}

void Task_RunTimeBasedEvents_new(u8 taskId)  //repuntear esta función.
{
    s16 *data = gTasks[taskId].data;

    if (!ScriptContext2_IsEnabled())
    {
        if (!QL_IS_PLAYBACK_STATE)
        {
#ifndef RTC_DEBUG
            RunTimeBasedEvents(data);   // RTC code /hook
#endif
            UpdateAmbientCry(&data[1], &data[2]);
        }
    }
}

#undef tState   // RTC code

