//title_screen.c


//SetTitleScreenScene_Cry hook
//en este punto, se agrega un salto para descartar parte del código
.org 0x08079254
SetTitleScreenScene_Cry_jump:
    b SetTitleScreenScene_Cry_jump + 0x3E
    //b 0x08079292


//08078fc4 l 000000dc SetTitleScreenScene_Run
//C5 8F 07 08 -> 0x083BFB90
.org 0x083BFB90
SetTitleScreenScene_Run_ptr:
    .word SetTitleScreenScene_Run_new|1
