#include "global.h"
#include "gflib.h"
#include "clock.h"  // RTC code
#include "rtc.h"    // RTC code
#include "script.h"
#include "mystery_event_script.h"
#include "event_data.h"
#include "random.h"
#include "item.h"
#include "overworld.h"
#include "field_screen_effect.h"
#include "quest_log.h"
#include "map_preview_screen.h"
#include "field_weather.h"
#include "field_tasks.h"
#include "field_fadetransition.h"
#include "field_player_avatar.h"
#include "script_movement.h"
#include "event_object_movement.h"
#include "event_object_lock.h"
#include "field_message_box.h"
#include "new_menu_helpers.h"
#include "script_menu.h"
#include "data.h"
#include "field_specials.h"
#include "constants/items.h"
#include "script_pokemon_util.h"
#include "pokemon_storage_system.h"
#include "party_menu.h"
#include "money.h"
#include "coins.h"
#include "battle_setup.h"
#include "shop.h"
#include "slot_machine.h"
#include "field_effect.h"
#include "fieldmap.h"
#include "field_door.h"
#include "constants/event_objects.h"

//extern u16 (*const gSpecials[])(void);
//extern u16 (*const gSpecialsEnd[])(void);
//extern const u8 *const gStdScripts[];
//extern const u8 *const gStdScriptsEnd[];

//static bool8 ScriptContext_NextCommandEndsScript(struct ScriptContext * ctx);
//static u8 ScriptContext_GetQuestLogInput(struct ScriptContext * ctx);

//struct ScriptContext * sQuestLogScriptContextPtr;
//u8 gSelectedObjectEvent;

// This is defined in here so the optimizer can't see its value when compiling
// script.c.
//void *const gNullScriptPtr = NULL;

//static const u8 sScriptConditionTable[6][3] =
//{
//  <  =  >
//    1, 0, 0, // <
//    0, 1, 0, // =
//    0, 0, 1, // >
//    1, 1, 0, // <=
//    0, 1, 1, // >=
//    1, 0, 1, // !=
//};

/**
 * XSE
 * 0x2C
 * cmd2c
*/
//0806a9d4 g 00000004 ScrCmd_initclock      d5 a9 06 08 -> 0x0815FA64
bool8 ScrCmd_initclock(struct ScriptContext * ctx)  // RTC code /hook /repoint  
{
    u8 hour = VarGet(ScriptReadHalfword(ctx));
    u8 minute = VarGet(ScriptReadHalfword(ctx));

    RtcInitLocalTimeOffset(hour, minute);
    return FALSE;
}

/**
 * XSE
 * 0x2D
 * checkdailyflags
*/
//0806a9d8 g 00000004 ScrCmd_dodailyevents  d9 a9 06 08 -> 0x0815FA68
bool8 ScrCmd_dotimebasedevents(struct ScriptContext * ctx)  // RTC code /hook /repoint /cambio de nombre desde: ScrCmd_dodailyevents
{
    DoTimeBasedEvents();
    return FALSE;
}

/**
 * XSE
 * 0x2E
 * resetvars
*/
//0806a9dc g 00000020 ScrCmd_gettime        dd a9 06 08 -> 0x0815FA6C
bool8 ScrCmd_gettime(struct ScriptContext * ctx)    // RTC code /hook /repoint
{
    RtcCalcLocalTime();
    gSpecialVar_0x8000 = gLocalTime.hours;
    gSpecialVar_0x8001 = gLocalTime.minutes;
    gSpecialVar_0x8002 = gLocalTime.seconds;
    return FALSE;
}
