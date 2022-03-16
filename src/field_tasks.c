#include "global.h"
#include "gflib.h"
#include "bike.h"
#include "clock.h"  // RTC code
#include "event_data.h"
#include "field_camera.h"
#include "field_effect_helpers.h"
#include "field_player_avatar.h"
#include "fieldmap.h"
#include "metatile_behavior.h"
#include "overworld.h"
#include "quest_log.h"
#include "script.h"
#include "task.h"
#include "constants/field_tasks.h"
#include "constants/metatile_labels.h"
#include "constants/songs.h"

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
            RunTimeBasedEvents(data);   // RTC code /hook
            UpdateAmbientCry(&data[1], &data[2]);
        }
    }
}

#undef tState   // RTC code

