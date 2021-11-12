.gba
.thumb
.open "BPRE.gba","build/rom_bpre.gba", 0x08000000


//------hooks----------------------------------------
.include "hooks/BPRE/EnableVCountIntrAtLine150_hook.s"
.include "hooks/BPRE/c2_copyright_1_Ptr.s"
.include "hooks/BPRE/DoSoftReset_hook.s"

//RTC_DEBUG
.include "hooks/BPRE/Task_SetWin0BldRegsAndCheckSaveFile_ptr.s"
.include "hooks/BPRE/title_screen_hook.s"
.include "hooks/BPRE/GetEvolutionTargetSpecies_n_others_hook.s"

//hook sabroso
.include "hooks/BPRE/NewGameInitData_jump.s"

.include "hooks/BPRE/DoTimeBasedEvents_hook.s"
.include "hooks/BPRE/Task_RunTimeBasedEvents_hook.s"
.include "hooks/BPRE/gScriptCmdTable_ptr.s"
.include "hooks/BPRE/gSpecials_ptr.s"


//------main-----------------------------------------
//aquí se insertará todo el código.
.align 4
.org insertinto
.importobj "src/siirtc_pokefirered.o"
.importobj "build/linked.o"
.close

