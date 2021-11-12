//field_tasks.c
//0806e83c l 00000040 Task_RunTimeBasedEvents
.org 0x0806e83c
.area 0x40, 0xFF
Task_RunTimeBasedEvents_hook:
    push {lr}
    lsl r0, r0, #0x18
    lsr r0, r0, #0x18
    ldr r3, =Task_RunTimeBasedEvents_new|1  
    bl bx_r3_Task_RunTimeBasedEvents
    pop {pc}
bx_r3_Task_RunTimeBasedEvents:
    bx r3
.pool
.endarea
