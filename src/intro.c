#include "include/global.h"
#include "include/gflib.h"
#include "include/m4a.h"
#include "include/task.h"
#include "include/scanline_effect.h"
#include "include/libgcnmultiboot.h"
#include "include/new_menu_helpers.h"
#include "include/link.h"
#include "include/menu.h"
#include "include/save.h"
#include "include/new_game.h"
#include "include/title_screen.h"
#include "include/decompress.h"
#include "include/util.h"
#include "include/trig.h"
#include "include/load_save.h"  //RTC code
#include "include/constants/songs.h"

extern bool8 RunCopyrightScreen(void);

//sólo es llamada por InitMainCallbacks 080004c4 l 0000004c InitMainCallbacks
//repuntear aquí.
// en InitMainCallbacks 080004c4
// 0x080004d0 4809 ldr r0, [$080004f8] (=$080ec821)
// El hook se realiza aquí: 0x080004f8

//080ec820 g 00000044 c2_copyright_1
void c2_copyright_1_Hook(void)   // RTC code repuntear esta función 
{
    if (!RunCopyrightScreen())
    {
#ifndef RTC_DEBUG
        SeedRngAndSetTrainerId();   // RTC code hook
        SetSaveBlocksPointers();    // RTC code hook
#endif
        ResetMenuAndMonGlobals();
        Save_ResetSaveCounters();
        Save_LoadGameData(SAVE_NORMAL);
        if (gSaveFileStatus == SAVE_STATUS_EMPTY || gSaveFileStatus == SAVE_STATUS_INVALID)
            Sav2_ClearSetDefault();
        SetPokemonCryStereo(gSaveBlock2Ptr->optionsSound);
#ifndef RTC_DEBUG
        InitHeap(gHeap, HEAP_SIZE); // RTC code hook
#endif
    }
}
