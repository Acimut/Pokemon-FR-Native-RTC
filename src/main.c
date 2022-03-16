
#include "global.h"
#include "gflib.h"
#include "link.h"
#include "link_rfu.h"
#include "load_save.h"
#include "m4a.h"
#include "rtc.h"    // RTC code
#include "random.h"
#include "gba/flash_internal.h"
#include "help_system.h"
#include "new_menu_helpers.h"
#include "overworld.h"
#include "play_time.h"
#include "intro.h"
#include "battle_controllers.h"
#include "scanline_effect.h"
#include "save_failed_screen.h"
#include "quest_log.h"

extern void m4aSoundVSyncOff(void);

//static void UpdateLinkAndCallCallbacks(void);
//static void InitMainCallbacks(void);
//static void CallCallbacks(void);
//static void ReadKeys(void);
//void InitIntrHandlers(void);
//static void WaitForVBlank(void);
//void EnableVCountIntrAtLine150(void);


//--------------------------------------    hook     ---------------------------------------//

void EnableVCountIntrAtLine150_new(void)
{
    u16 gpuReg = (GetGpuReg(REG_OFFSET_DISPSTAT) & 0xFF) | (150 << 8);
    SetGpuReg(REG_OFFSET_DISPSTAT, gpuReg | DISPSTAT_VCOUNT_INTR);
    EnableInterrupts(INTR_FLAG_VCOUNT);
    RtcInit();  // RTC code hook            //
}


//--------------------------------------    hook    ---------------------------------------//


void DoSoftReset_RTC(void)
{
    REG_IME = 0;
    m4aSoundVSyncOff();
    ScanlineEffect_Stop();
    DmaStop(1);
    DmaStop(2);
    DmaStop(3);
    SiiRtcProtect();    // RTC code
    SoftReset(RESET_ALL & ~RESET_SIO_REGS);
}

//--------------------------------------    hook    ---------------------------------------//
//void DoSoftReset(void) //hook, compilar -> obtener ASM code -> realizar hook en la inyección.
//{
//    DoSoftReset_RTC();
//}
//--------------------------------------    hook    ---------------------------------------//
