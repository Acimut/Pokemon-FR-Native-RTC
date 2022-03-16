#include "global.h"
#include "main.h"
#include "script.h"

#include "overworld.h"
#include "rtc.h"        // RTC code
#include "wallclock.h"  // RTC code


/*
08055dc4 g 000000b4 Overworld_PlaySpecialMapMusic   ptr-> c5 5d 05 08 ->0x0815ffc4

    def_special Overworld_PlaySpecialMapMusic
	def_special StartWallClock                  //RTC   ptr->0x0815ffc8
	def_special Special_ViewWallClock           //RTC   ptr->0x0815ffcc
	def_special NullFieldSpecial
	def_special StartOldManTutorialBattle

    /.../

080a0ec4 g 00000028 EnterSafariMode                 ptr-> c5 0e 0a 08 ->0x08160094
080a0eec g 00000020 ExitSafariMode                  ptr-> ed 0e 0a 08 ->0x08160098

    def_special NullFieldSpecial
	def_special EnterSafariMode
	def_special ExitSafariMode
	def_special GetWeekCount                    //RTC   ptr->0x0816009c
	def_special NullFieldSpecial
	def_special NullFieldSpecial
	def_special NullFieldSpecial

*/
//special 0x9B
void Special_ViewWallClock(void)    // RTC code /new /special
{
    gMain.savedCallback = CB2_ReturnToField;
    SetMainCallback2(CB2_ViewWallClock);
    ScriptContext2_Enable();
}
//special 0xCF
u16 GetWeekCount(void)  // RTC code /new /special
{
    u16 weekCount = gLocalTime.days / 7;
    if (weekCount > 9999)
    {
        weekCount = 9999;
    }
    return weekCount;
}
