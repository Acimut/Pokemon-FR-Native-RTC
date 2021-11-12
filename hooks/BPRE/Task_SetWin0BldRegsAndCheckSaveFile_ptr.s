
//main_menu.c

//RTC_DEBUG
.org 0x0800c608
Task_SetWin0BldRegsAndCheckSaveFile_Hook:
    .word Task_MainMenuCheckBattery|1
