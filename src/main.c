
#include "include/global.h"
#include "include/gflib.h"
#include "include/link.h"
#include "include/link_rfu.h"
#include "include/load_save.h"
#include "include/m4a.h"
#include "include/rtc.h"    // RTC code
#include "include/random.h"
#include "include/gba/flash_internal.h"
#include "include/help_system.h"
#include "include/new_menu_helpers.h"
#include "include/overworld.h"
#include "include/play_time.h"
#include "include/intro.h"
#include "include/battle_controllers.h"
#include "include/scanline_effect.h"
#include "include/save_failed_screen.h"
#include "include/quest_log.h"

extern void m4aSoundVSyncOff(void);

//static void UpdateLinkAndCallCallbacks(void);
//static void InitMainCallbacks(void);
//static void CallCallbacks(void);
//static void ReadKeys(void);
//void InitIntrHandlers(void);
//static void WaitForVBlank(void);
//void EnableVCountIntrAtLine150(void);


void EnableVCountIntrAtLine150(void)
{
    u16 gpuReg = (GetGpuReg(REG_OFFSET_DISPSTAT) & 0xFF) | (150 << 8);
    SetGpuReg(REG_OFFSET_DISPSTAT, gpuReg | DISPSTAT_VCOUNT_INTR);
    EnableInterrupts(INTR_FLAG_VCOUNT);
}

//--------------------------------------    hook     ---------------------------------------//
void EnableVCountIntrAtLine150_new(void)
{
    EnableVCountIntrAtLine150();            //0x08000598
    InitRFU();  // definir en archivo .LD   //0x080f86c4
#ifndef RTC_DEBUG
    RtcInit();  // RTC code hook            //
#endif
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

#ifndef RTC_DEBUG
    SiiRtcProtect();    // RTC code
#endif

    SoftReset(RESET_ALL & ~RESET_SIO_REGS);
}

//--------------------------------------    hook    ---------------------------------------//
//void DoSoftReset(void) //hook, compilar -> obtener ASM code -> realizar hook en la inyección.
//{
//    DoSoftReset_RTC();
//}
//--------------------------------------    hook    ---------------------------------------//
