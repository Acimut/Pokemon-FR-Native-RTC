//main.c
//usado para saltar InitRFU(); que ahora es llamado en el hook EnableVCountIntrAtLine150

.org 0x080003d6 //AgbMain();
bl_RtcInit:
    b bl_RtcInit + 4
    //b 0x080003da//bl_CheckForFlashMemory:

.org 0x08000598
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
