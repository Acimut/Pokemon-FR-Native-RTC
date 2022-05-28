//palette.c

//08070474 g 0000005c TransferPlttBuffer

.org 0x08070490
    //r0 = gPlttBufferFaded
    //r1 = DnsTransferPlttBuffer
    //r2 = PLTT
    mov r3, r1  //90
    mov r1, r2  //92
    bl bx_r3_TransferPlttBuffer //94
    mov r3, #0  //98

.org 0x080704C0
    .word DnsTransferPlttBuffer|1   //gPlttBufferFaded//r1
    .word gPlttBufferFaded

bx_r3_TransferPlttBuffer:
.org 0x080704C8
    bx r3


//08070588 g 00000148 BeginNormalPaletteFade
/*.org 0x0807067A
    mov r8, r8//A
    mov r8, r8//C
    mov r8, r8//E
    mov r8, r8//0*/

.org 0x08070682
    bl 0x08070474   //TransferPlttBuffer


//play_time.c
//0805486c g 00000068 PlayTimeCounter_Update
.org 0x0805486c
.area 0x68, 0xFF
PlayTimeCounter_Update_hook:
    push {lr}
    ldr r3, =PlayTimeCounter_Update|1  
    bl bx_r3_PlayTimeCounter_Update
    pop {pc}
bx_r3_PlayTimeCounter_Update:
    bx r3
.pool
.endarea



//battle_main.c
//08011100 g 00000074 BattleMainCB2
.org 0x08011100
.area 0x74, 0xFF
BattleMainCB2_hook:
    push {lr}
    ldr r3, =BattleMainCB2|1  
    bl bx_r3_BattleMainCB2
    pop {pc}
bx_r3_BattleMainCB2:
    bx r3
.pool
.endarea


//overworld.c
//08056578 l 0000002e OverworldBasic
.org 0x08056578
.area 0x2e, 0xFF
OverworldBasic_hook:
    push {lr}
    ldr r3, =OverworldBasic|1  
    bl bx_r3_OverworldBasic
    pop {pc}
bx_r3_OverworldBasic:
    bx r3
.pool
.endarea

/*
//.c
//
.org 0x
.area 0x, 0xFF
_hook:
    push {lr}
    ldr r3, =|1  
    bl bx_r3_
    pop {pc}
bx_r3_:
    bx r3
.pool
.endarea
*/

