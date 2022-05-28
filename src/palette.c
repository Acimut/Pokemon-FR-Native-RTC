#include "global.h"
#include "gflib.h"
//#include "util.h"
//#include "decompress.h"
//#include "task.h"
#include "dns.h"

/**
 * 2022-05-16
 * ACIMUT:
 * Compilar estas 2 funciones y luego
 * comparar con las originales en ASM.
 * Luego, ver si es posible sólo hacer
 * el cambio desde un hook en ASM.
 * #Estas 2 funciones son llamadas
 * #en varias partes de la inyección.
*/

enum
{
    NORMAL_FADE,
    FAST_FADE,
    HARDWARE_FADE,
};

#define NUM_PALETTE_STRUCTS 16

//EWRAM
extern u32 sPlttBufferTransferPending;

//static 
extern void UpdateBlendRegisters(void);


//08070474 g 0000005c TransferPlttBuffer
void TransferPlttBuffer_new(void)
{
    if (!gPaletteFade.bufferTransferDisabled)
    {
        void *src = gPlttBufferFaded;
        void *dest = (void *)PLTT;
        //DmaCopy16(3, src, dest, PLTT_SIZE);
        DnsTransferPlttBuffer(src, dest);  //Does 16b Dma Transfer
        sPlttBufferTransferPending = 0;
        if (gPaletteFade.mode == HARDWARE_FADE && gPaletteFade.active)
            UpdateBlendRegisters();
    }
}

//08070588 g 00000148 BeginNormalPaletteFade
bool8 BeginNormalPaletteFade_new(u32 selectedPalettes, s8 delay, u8 startY, u8 targetY, u16 blendColor)
{
    u8 temp;
    u16 color = blendColor;

    if (gPaletteFade.active)
    {
        return FALSE;
    }
    else
    {
        gPaletteFade.deltaY = 2;
        if (delay < 0)
        {
            gPaletteFade.deltaY += (delay * -1);
            delay = 0;
        }
        gPaletteFade_selectedPalettes = selectedPalettes;
        gPaletteFade.delayCounter = delay;
        gPaletteFade_delay = delay;
        gPaletteFade.y = startY;
        gPaletteFade.targetY = targetY;
        gPaletteFade.blendColor = color;
        gPaletteFade.active = TRUE;
        gPaletteFade.mode = NORMAL_FADE;
        if (startY < targetY)
            gPaletteFade.yDec = FALSE;
        else
            gPaletteFade.yDec = TRUE;
        UpdatePaletteFade();
        temp = gPaletteFade.bufferTransferDisabled;
        gPaletteFade.bufferTransferDisabled = FALSE;
        //CpuCopy32(gPlttBufferFaded, (void *)PLTT, PLTT_SIZE);
        TransferPlttBuffer_new();   //Fix DNS flickering
        sPlttBufferTransferPending = 0;
        if (gPaletteFade.mode == HARDWARE_FADE && gPaletteFade.active)
            UpdateBlendRegisters();
        gPaletteFade.bufferTransferDisabled = temp;
        return TRUE;
    }
}


