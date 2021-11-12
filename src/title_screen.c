#include "include/global.h"
#include "include/gflib.h"
#include "include/task.h"
#include "include/new_menu_helpers.h"
#include "include/m4a.h"
#include "include/scanline_effect.h"
#include "include/graphics.h"
#include "include/help_system.h"
#include "include/intro.h"
#include "include/load_save.h"
#include "include/new_game.h"
#include "include/save.h"
#include "include/event_data.h" // RTC code
#include "include/main_menu.h"
#include "include/clear_save_data_screen.h"
#include "include/reset_rtc_screen.h"   // RTC code
#include "include/berry_fix_program.h"
#include "include/decompress.h"
#include "include/constants/songs.h"

enum TitleScreenScene
{
    TITLESCREENSCENE_INIT = 0,
    TITLESCREENSCENE_FLASHSPRITE,
    TITLESCREENSCENE_FADEIN,
    TITLESCREENSCENE_RUN,
    TITLESCREENSCEEN_RESTART,
    TITLESCREENSCENE_CRY
};

//#if   defined(FIRERED)  // RTC code mod
#define TITLE_SPECIES SPECIES_CHARIZARD
//#elif defined(LEAFGREEN)
//#define TITLE_SPECIES SPECIES_VENUSAUR
//#endif

//static EWRAM_DATA u8 sTitleScreenTimerTaskId = 0;


extern void Task_TitleScreenTimer(u8 taskId);
extern void Task_TitleScreenMain(u8 taskId);
extern void SetTitleScreenScene(s16 * data, u8 a1);
extern void SetGpuRegsForTitleScreenRun(void);
extern void Task_TitleScreen_BlinkPressStart(u8 taskId);
extern void CB2_FadeOutTransitionToSaveClearScreen(void);
extern void CB2_FadeOutTransitionToBerryFix(void);
extern void Task_FlameOrLeafSpawner(u8 taskId);
extern u8 CreateSlashSprite(void);
extern void ScheduleHideSlashSprite(u8 spriteId);

//static void CB2_GoToResetRtcScreen(void);                   // RTC code /unused
/*static */void CB2_FadeOutTransitionToResetRtcScreen(void);    // RTC code


#define KEYSTROKE_DELSAVE (B_BUTTON | SELECT_BUTTON | DPAD_UP)
#define KEYSTROKE_RESET_RTC (B_BUTTON | SELECT_BUTTON | DPAD_LEFT)  // RTC code
#define KEYSTROKE_BERRY_FIX (B_BUTTON | SELECT_BUTTON)

//08078fc4 l 000000dc SetTitleScreenScene_Run
void SetTitleScreenScene_Run_new(s16 * data) // RTC code repuntear para hacer hook a esta función
{
    switch (data[1])
    {
    case 0:
        SetHelpContext(HELPCONTEXT_TITLE_SCREEN);
        CreateTask(Task_TitleScreen_BlinkPressStart, 0);
        CreateTask(Task_FlameOrLeafSpawner, 5);
        SetGpuRegsForTitleScreenRun();
        data[6] = CreateSlashSprite();
        HelpSystem_Enable();
        data[1]++;
        // fallthrough
        //aquí falta un break;
        //break;
    case 1:
        if (JOY_HELD(KEYSTROKE_DELSAVE) == KEYSTROKE_DELSAVE)
        {
            ScheduleHideSlashSprite(data[6]);
            DestroyTask(FindTaskIdByFunc(Task_TitleScreenMain));
            SetMainCallback2(CB2_FadeOutTransitionToSaveClearScreen);
        }
#ifndef RTC_DEBUG
        else if (JOY_HELD(KEYSTROKE_RESET_RTC) == KEYSTROKE_RESET_RTC && CanResetRTC() == TRUE) // RTC code new
        {                                                           // RTC code
            ScheduleHideSlashSprite(data[6]);                       // RTC code
            DestroyTask(FindTaskIdByFunc(Task_TitleScreenMain));    // RTC code
            SetMainCallback2(CB2_FadeOutTransitionToResetRtcScreen);// RTC code
        }                                                           // RTC code
#endif
        else if (JOY_HELD(KEYSTROKE_BERRY_FIX) == KEYSTROKE_BERRY_FIX)
        {
            ScheduleHideSlashSprite(data[6]);
            DestroyTask(FindTaskIdByFunc(Task_TitleScreenMain));
            SetMainCallback2(CB2_FadeOutTransitionToBerryFix);
        }
        else if (JOY_NEW(A_BUTTON | START_BUTTON))
        {
            SetTitleScreenScene(data, TITLESCREENSCENE_CRY);
        }
        else if (!FuncIsActiveTask(Task_TitleScreenTimer))
        {
            SetTitleScreenScene(data, TITLESCREENSCEEN_RESTART);
        }
        break;
    }
}

//static 
void CB2_FadeOutTransitionToResetRtcScreen(void) // RTC code new
{                                                       // RTC code
    if (!UpdatePaletteFade())                           // RTC code
    {                                                   // RTC code
        m4aMPlayAllStop();                              // RTC code
        SetMainCallback2(CB2_InitResetRtcScreen);       // RTC code
    }                                                   // RTC code
}                                                       // RTC code


//080791c0 l 00000108 SetTitleScreenScene_Cry
/*
La manera de hacer hook aquí es la siguiente:
borrar los bytes desde 0x08079254 hasta 0x08079291

static void SetTitleScreenScene_Cry(s16 * data)
{
    switch (data[1])
    {
    case 0:
        if (!gPaletteFade.active)
        {
            PlayCry1(TITLE_SPECIES, 0);
            ScheduleHideSlashSprite(data[6]);
            data[2] = 0;
            data[1]++;
        }
        break;
    case 1:
        if (data[2] < 90)
            data[2]++;
        else if (!IsSlashSpriteHidden(data[6]))
        {
            BeginNormalPaletteFade(0x0FFFFFFF, 0, 0, 0x10, RGB_WHITE);
            SignalEndTitleScreenPaletteSomethingTask();
            FadeOutBGM(4);
            data[1]++;
        }
        break;
    case 2:
        if (!gPaletteFade.active)
        {   // RTC code //realizar hook a esta parte del código.
            // These are commented out as they’ve been relocated to intro.c.
            // This also allows RTC reset to work without file corruption.
            // It also has the side effect of allowing you to run flags
            // and functions as early as the intro.

            // SeedRngAndSetTrainerId();    +
            // SetSaveBlocksPointers();     +
            // ResetMenuAndMonGlobals();
            // Save_ResetSaveCounters();
            // Save_LoadGameData(SAVE_NORMAL);
            // if (gSaveFileStatus == SAVE_STATUS_EMPTY || gSaveFileStatus == SAVE_STATUS_INVALID)
            //     Sav2_ClearSetDefault();
            // SetPokemonCryStereo(gSaveBlock2Ptr->optionsSound);
            // InitHeap(gHeap, HEAP_SIZE);  +
            SetMainCallback2(CB2_InitMainMenu);
            DestroyTask(FindTaskIdByFunc(Task_TitleScreenMain));
        }
        break;
    }
}
*/
