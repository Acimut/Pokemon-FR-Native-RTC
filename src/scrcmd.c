#include "include/global.h"
#include "include/gflib.h"
#include "include/clock.h"  // RTC code
#include "include/rtc.h"    // RTC code
#include "include/script.h"
#include "include/mystery_event_script.h"
#include "include/event_data.h"
#include "include/random.h"
#include "include/item.h"
#include "include/overworld.h"
#include "include/field_screen_effect.h"
#include "include/quest_log.h"
#include "include/map_preview_screen.h"
#include "include/field_weather.h"
#include "include/field_tasks.h"
#include "include/field_fadetransition.h"
#include "include/field_player_avatar.h"
#include "include/script_movement.h"
#include "include/event_object_movement.h"
#include "include/event_object_lock.h"
#include "include/field_message_box.h"
#include "include/new_menu_helpers.h"
#include "include/script_menu.h"
#include "include/data.h"
#include "include/field_specials.h"
#include "include/constants/items.h"
#include "include/script_pokemon_util.h"
#include "include/pokemon_storage_system.h"
#include "include/party_menu.h"
#include "include/money.h"
#include "include/coins.h"
#include "include/battle_setup.h"
#include "include/shop.h"
#include "include/slot_machine.h"
#include "include/field_effect.h"
#include "include/fieldmap.h"
#include "include/field_door.h"
#include "include/constants/event_objects.h"

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
#ifndef RTC_DEBUG
    u8 hour = VarGet(ScriptReadHalfword(ctx));
    u8 minute = VarGet(ScriptReadHalfword(ctx));

    RtcInitLocalTimeOffset(hour, minute);
#endif
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
#ifndef RTC_DEBUG
    DoTimeBasedEvents();
#endif
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
#ifndef RTC_DEBUG
    RtcCalcLocalTime();
    gSpecialVar_0x8000 = gLocalTime.hours;
    gSpecialVar_0x8001 = gLocalTime.minutes;
    gSpecialVar_0x8002 = gLocalTime.seconds;
#else
    gSpecialVar_0x8000 = 0;
    gSpecialVar_0x8001 = 0;
    gSpecialVar_0x8002 = 0;
#endif
    return FALSE;
}
