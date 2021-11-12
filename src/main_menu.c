#include "textos.h"    //acimut's code
#include "include/global.h"
#include "include/gflib.h"
#include "include/scanline_effect.h"
#include "include/task.h"
#include "include/save.h"
#include "include/event_data.h"
#include "include/menu.h"
#include "include/rtc.h"    // RTC code
#include "include/link.h"
#include "include/oak_speech.h"
//#include "overworld.h"
#include "include/quest_log.h"
#include "include/mystery_gift_menu.h"
//#include "include/strings.h"
#include "include/title_screen.h"
#include "include/help_system.h"
#include "include/pokedex.h"
#include "include/text_window.h"
#include "include/text_window_graphics.h"
#include "include/constants/songs.h"

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