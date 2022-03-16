#include "textos.h"    //acimut's code
#include "global.h"
#include "gflib.h"
#include "scanline_effect.h"
#include "task.h"
#include "save.h"
#include "event_data.h"
#include "menu.h"
#include "rtc.h"    // RTC code
#include "link.h"
#include "oak_speech.h"
//#include "overworld.h"
#include "quest_log.h"
#include "mystery_gift_menu.h"
//#include "strings.h"
#include "title_screen.h"
#include "help_system.h"
#include "pokedex.h"
#include "text_window.h"
#include "text_window_graphics.h"
#include "constants/songs.h"

enum MainMenuType
{
    MAIN_MENU_NEWGAME = 0,
    MAIN_MENU_CONTINUE,
    MAIN_MENU_MYSTERYGIFT
};

enum MainMenuWindow
{
    MAIN_MENU_WINDOW_NEWGAME_ONLY = 0,
    MAIN_MENU_WINDOW_CONTINUE,
    MAIN_MENU_WINDOW_NEWGAME,
    MAIN_MENU_WINDOW_MYSTERYGIFT,
    MAIN_MENU_WINDOW_ERROR,
    MAIN_MENU_WINDOW_COUNT
};

#define tMenuType  data[0]
#define tCursorPos data[1]

#define tUnused8         data[8]
#define tMGErrorMsgState data[9]
#define tMGErrorType     data[10]

extern void Task_SetWin0BldRegsNoSaveFileCheck(u8 taskId);
extern void Task_PrintMainMenuText(u8 taskId);
extern void LoadUserFrameToBg(u8 bgId);
extern void SetStdFrame0OnBg(u8 bgId);
extern void PrintSaveErrorStatus(u8 taskId, const u8 *str);
extern void MainMenu_EraseWindow(const struct WindowTemplate * template);

static void Task_WaitForBatteryDryErrorWindow(u8);  // RTC code

//08234618 l 00000030 sWindowTemplate
extern struct WindowTemplate sWindowTemplate[];


void Task_MainMenuCheckBattery(u8 taskId)    // RTC code /new
{
    if (!gPaletteFade.active)
    {
        SetGpuReg(REG_OFFSET_WIN0H, 0);
        SetGpuReg(REG_OFFSET_WIN0V, 0);
        SetGpuReg(REG_OFFSET_WININ, 0x0001);
        SetGpuReg(REG_OFFSET_WINOUT, 0x0021);
        SetGpuReg(REG_OFFSET_BLDCNT, BLDCNT_TGT1_BG0 | BLDCNT_TGT1_BG1 | BLDCNT_TGT1_BG2 | BLDCNT_TGT1_BG3 | BLDCNT_TGT1_OBJ | BLDCNT_TGT1_BD | BLDCNT_EFFECT_DARKEN);
        SetGpuReg(REG_OFFSET_BLDALPHA, BLDALPHA_BLEND(0, 0));
        SetGpuReg(REG_OFFSET_BLDY, 7);

        if (!(RtcGetErrorStatus() & RTC_ERR_FLAG_MASK))
        {
            if(gTasks[taskId].tMenuType == MAIN_MENU_NEWGAME) {
                LoadUserFrameToBg(0);
                gTasks[taskId].tMenuType = MAIN_MENU_NEWGAME;
                gTasks[taskId].func = Task_SetWin0BldRegsNoSaveFileCheck;
            }
            else {
                gTasks[taskId].func = Task_SetWin0BldRegsNoSaveFileCheck;
            }
        }
        else
        {
            SetStdFrame0OnBg(0);
            PrintSaveErrorStatus(taskId, gText_BatteryRunDry);
            gTasks[taskId].func = Task_WaitForBatteryDryErrorWindow;
        }
    }
}

static void Task_WaitForBatteryDryErrorWindow(u8 taskId)    // RTC code /new
{
    if (!gPaletteFade.active)
    {
        RunTextPrinters();
        if(gTasks[taskId].tUnused8 == 3)
        {
            if(!IsTextPrinterActive(MAIN_MENU_WINDOW_ERROR))
            {
                gTasks[taskId].func = Task_SetWin0BldRegsNoSaveFileCheck;
            }
        }
        else
        {
            if (!IsTextPrinterActive(MAIN_MENU_WINDOW_ERROR) && JOY_NEW(A_BUTTON))
            {
                ClearWindowTilemap(MAIN_MENU_WINDOW_ERROR);
                MainMenu_EraseWindow(&sWindowTemplate[MAIN_MENU_WINDOW_ERROR]);
                LoadUserFrameToBg(0);

                if (gTasks[taskId].tMenuType == MAIN_MENU_NEWGAME)
                    gTasks[taskId].func = Task_SetWin0BldRegsNoSaveFileCheck;
                else
                    gTasks[taskId].func = Task_PrintMainMenuText;
            }
        }
    }
}


/*
 * The entire screen is darkened slightly except at WIN0 to indicate
 * the player cursor position.
 */

//static 
void Task_SetWin0BldRegsAndCheckSaveFile_new(u8 taskId)
{
    if (!gPaletteFade.active)
    {
        SetGpuReg(REG_OFFSET_WIN0H, 0);
        SetGpuReg(REG_OFFSET_WIN0V, 0);
        SetGpuReg(REG_OFFSET_WININ, 0x0001);
        SetGpuReg(REG_OFFSET_WINOUT, 0x0021);
        SetGpuReg(REG_OFFSET_BLDCNT, BLDCNT_TGT1_BG0 | BLDCNT_TGT1_BG1 | BLDCNT_TGT1_BG2 | BLDCNT_TGT1_BG3 | BLDCNT_TGT1_OBJ | BLDCNT_TGT1_BD | BLDCNT_EFFECT_DARKEN);
        SetGpuReg(REG_OFFSET_BLDALPHA, BLDALPHA_BLEND(0, 0));
        SetGpuReg(REG_OFFSET_BLDY, 7);
        switch (gSaveFileStatus)
        {
        case SAVE_STATUS_OK:
            LoadUserFrameToBg(0);
            if (IsMysteryGiftEnabled() == TRUE)
            {
                gTasks[taskId].tMenuType = MAIN_MENU_MYSTERYGIFT;
            }
            else
            {
                gTasks[taskId].tMenuType = MAIN_MENU_CONTINUE;
            }
            //gTasks[taskId].func = Task_SetWin0BldRegsNoSaveFileCheck;
            gTasks[taskId].func = Task_MainMenuCheckBattery;//RTC CODE
            break;
        case SAVE_STATUS_INVALID:
            SetStdFrame0OnBg(0);
            gTasks[taskId].tMenuType = MAIN_MENU_NEWGAME;
            PrintSaveErrorStatus(taskId, gText_SaveFileHasBeenDeleted);
            break;
        case SAVE_STATUS_ERROR:
            SetStdFrame0OnBg(0);
            gTasks[taskId].tMenuType = MAIN_MENU_CONTINUE;
            PrintSaveErrorStatus(taskId, gText_SaveFileCorruptedPrevWillBeLoaded);
            if (IsMysteryGiftEnabled() == TRUE)
            {
                gTasks[taskId].tMenuType = MAIN_MENU_MYSTERYGIFT;
            }
            else
            {
                gTasks[taskId].tMenuType = MAIN_MENU_CONTINUE;
            }
            break;
        case SAVE_STATUS_EMPTY:
        default:
            LoadUserFrameToBg(0);
            gTasks[taskId].tMenuType = MAIN_MENU_NEWGAME;
            gTasks[taskId].func = Task_SetWin0BldRegsNoSaveFileCheck;
            break;
        case SAVE_STATUS_NO_FLASH:
            SetStdFrame0OnBg(0);
            gTasks[taskId].tMenuType = MAIN_MENU_NEWGAME;
            PrintSaveErrorStatus(taskId, gText_1MSubCircuitBoardNotInstalled);
            break;
        }
    }
}
