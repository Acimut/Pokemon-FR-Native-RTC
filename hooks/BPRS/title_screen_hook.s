//title_screen.c


//SetTitleScreenScene_Cry hook
//en este punto, se agrega un salto para descartar parte del código
.org 0x0807928C
SetTitleScreenScene_Cry_jump:
    b SetTitleScreenScene_Cry_jump + 0x3E
    //b 0x08079292

//083bfb84 l 00000018 sSceneFuncs (tabla de punteros)
//08078fc4 l 000000dc SetTitleScreenScene_Run   FR
//C5 8F 07 08 -> 0x083BFB90 FR
//08078ffc l 000000dc SetTitleScreenScene_Run   RF
//FD 8F 07 08   -> 0x083BB280 RF
.org 0x083BB280
SetTitleScreenScene_Run_ptr:
    .word SetTitleScreenScene_Run_new|1
