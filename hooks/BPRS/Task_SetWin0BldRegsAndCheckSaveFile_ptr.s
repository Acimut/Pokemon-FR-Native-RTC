
//main_menu.c

//RTC_DEBUG
//0800c4d0 l 00000164 Task_SetWin0BldRegsAndCheckSaveFile FR -> d1 c4 00 08
//0800c43c l 00000164 Task_SetWin0BldRegsAndCheckSaveFile RF -> 3D C4 00 08
.org 0x0800c434
Task_SetWin0BldRegsAndCheckSaveFile_Hook:
    .word Task_MainMenuCheckBattery|1
