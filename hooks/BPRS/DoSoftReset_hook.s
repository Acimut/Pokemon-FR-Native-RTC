//main.c
.org 0x080008d4
.area 0x6C, 0xFF
DoSoftReset_hook:
    push {lr}
    ldr r3, =DoSoftReset_RTC|1  
    bl bx_r3_DoSoftReset
    pop {pc}
bx_r3_DoSoftReset:
    bx r3
.pool
.endarea
