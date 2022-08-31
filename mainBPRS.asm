.gba
.thumb
.open "BPRS.gba","build/rom_bprs.gba", 0x08000000

//------hooks----------------------------------------
.include "hooks/BPRS/EnableVCountIntrAtLine150_hook.s"
.include "hooks/BPRS/c2_copyright_1_Ptr.s"
.include "hooks/BPRS/DoSoftReset_hook.s"


.include "hooks/BPRS/Task_SetWin0BldRegsAndCheckSaveFile_ptr.s"
.include "hooks/BPRS/title_screen_hook.s"
.include "hooks/BPRS/GetEvolutionTargetSpecies_n_others_hook.s"

//hook sabroso
.include "hooks/BPRS/NewGameInitData_jump.s"

.include "hooks/BPRS/DoTimeBasedEvents_hook.s"
.include "hooks/BPRS/Task_RunTimeBasedEvents_hook.s"
.include "hooks/BPRS/gScriptCmdTable_ptr.s"
.include "hooks/BPRS/gSpecials_ptr.s"

.include "hooks/BPRS/evolution_hooks.s"

.include "hooks/BPRE/dns_hook.s"

//------main-----------------------------------------
//aquí se insertará todo el código.
.align 4
.org insertinto
.importobj "build/linked.o"
.close

