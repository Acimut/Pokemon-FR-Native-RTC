
//main_menu.c

.org 0x0800c434
Task_SetWin0BldRegsAndCheckSaveFile_hook:
    .word Task_SetWin0BldRegsAndCheckSaveFile_new|1
