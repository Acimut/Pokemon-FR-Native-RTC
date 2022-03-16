#include "global.h"
#include "gflib.h"
#include "m4a.h"
#include "task.h"
#include "scanline_effect.h"
#include "libgcnmultiboot.h"
#include "new_menu_helpers.h"
#include "link.h"
#include "menu.h"
#include "save.h"
#include "new_game.h"
#include "title_screen.h"
#include "decompress.h"
#include "util.h"
#include "trig.h"
#include "load_save.h"  //RTC code
#include "constants/songs.h"

extern bool8 RunCopyrightScreen(void);

//sólo es llamada por InitMainCallbacks 080004c4 l 0000004c InitMainCallbacks
//repuntear aquí.
// en InitMainCallbacks 080004c4
// 0x080004d0 4809 ldr r0, [$080004f8] (=$080ec821)
// El hook se realiza aquí: 0x080004f8

//080ec820 g 00000044 c2_copyright_1    fire red
//080ecb2c g 00000044 c2_copyright_1    rojo fuego
void c2_copyright_1_Hook(void)   // RTC code repuntear esta función 
{
    if (!RunCopyrightScreen())
    {
        SeedRngAndSetTrainerId();   // RTC code hook
        SetSaveBlocksPointers();    // RTC code hook
        ResetMenuAndMonGlobals();
        Save_ResetSaveCounters();
        Save_LoadGameData(SAVE_NORMAL);
        if (gSaveFileStatus == SAVE_STATUS_EMPTY || gSaveFileStatus == SAVE_STATUS_INVALID)
            Sav2_ClearSetDefault();
        SetPokemonCryStereo(gSaveBlock2Ptr->optionsSound);
        InitHeap(gHeap, HEAP_SIZE); // RTC code hook
    }
}
