
.org 0x08000594
.area 0x28, 0xFF
EnableVCountIntrAtLine150_hook:
    push {lr}
    ldr r3, =EnableVCountIntrAtLine150_new|1
    bl bx_r3_EnableVCountIntrAtLine150
    pop {pc}
bx_r3_EnableVCountIntrAtLine150:
    bx r3
.pool
.endarea
