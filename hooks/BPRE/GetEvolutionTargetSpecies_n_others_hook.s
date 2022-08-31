//pokemon.c
.org 0x08042ec4
.area 0x2f0//, 0xFF
GetEvolutionTargetSpecies_hook:
    push {lr}
    lsl r1, r1, #0x18
    lsr r1, r1, #0x18
    lsl r2, r2, #0x10
    lsr r2, r2, #0x10
    ldr r3, =GetEvolutionTargetSpecies_new|1  
    bl bx_r3_GetEvolutionTargetSpecies
    pop {pc}
bx_r3_GetEvolutionTargetSpecies:
    bx r3
.pool

//overworld.c
//0807b140 g 00000034 SetSav1WeatherFromCurrMapHeader
SetSav1WeatherFromCurrMapHeader_Hook:
    push {lr}                                        //2 bytes
    ldr r3, =SetSav1WeatherFromCurrMapHeader_new|1  //2 bytes
    bl bx_r3_SetSav1WeatherFromCurrMapHeader        //4 bytes
    pop {pc}                                        //2 bytes
bx_r3_SetSav1WeatherFromCurrMapHeader:
    bx r3
.pool
//overworld.c
//08054e40 l 00000028 Overworld_ResetStateOnContinue
Overworld_ResetStateOnContinue_Hook:
    push {lr}
    ldr r3, =Overworld_ResetStateOnContinue_new|1
    bl bx_r3_Overworld_ResetStateOnContinue
    pop {pc}
bx_r3_Overworld_ResetStateOnContinue:
    bx r3

.pool

//08056644 g 00000060 CB2_NewGame
//en overword.c se llama a esta función NewGameInitData
//a travez de un bl en 08056652
NewGameInitData_hook:
    push{lr}
    ldr r3, =NewGame_RTC|1
    bl bx_r3_NewGameInitData_hook
    pop {pc}
bx_r3_NewGameInitData_hook:
    bx r3
.pool
.endarea

