
//08259754 g 00004060 gEvolutionTable
//Borrar la antigua gEvolutionTable:
.org 0x08259754
.area 0x4060, 0xFF
.endarea


// 080ce748 l 00000194 CreateShedinja
// repuntear gEvolutionTable en esta función:
.org 0x080CE8C4
    .word gEvolutionTable


//08045970 l 00000080 GetEggSpecies
//hacer hook para reemplazar esta función:
.org 0x08045970
.area 0x80, 0xFF
GetEggSpecies_hook:
    push {lr}
    //lsl r0, r0, #0x10 //u16 species
    //lsr r0, r0, #0x10
    ldr r3, =GetEggSpecies_new|1
    bl bx_r3_GetEggSpecies_hook
    pop {pc}
bx_r3_GetEggSpecies_hook:
    bx r3
.pool
.endarea

