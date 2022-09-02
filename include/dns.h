#ifndef GUARD_DNS_UTILS_H
#define GUARD_DNS_UTILS_H

#define DNS_PAL_EXCEPTION   FALSE
#define DNS_PAL_ACTIVE      TRUE

  /*******************************************************/
 /*********    Day and Night Configuration     **********/
/********************************************************
 * You can customize the DNS by editing the following   *
 * timelapses and the filters used to change the        *
 * palette colours.                                     *
 * In addition to that, you can also configure which    *
 * palettes are affected by the system, as well as      *
 * establishing sprite palettes exceptions by its TAG.  *
 * 
 * It is highly recommended to read the following config*
 * options, to understand how the dns works.            *
 * ******************************************************/

/* Timelapses */
enum
{
    TIME_MIDNIGHT,
    TIME_DAWN,
    TIME_DAY,
    TIME_SUNSET,
    TIME_NIGHTFALL,
    TIME_NIGHT
};

/* End hours for each of the timelapses */
#define MIDNIGHT_END_HOUR   5       //  = 00 - 05   //  old = 7  : 00 - 07
#define DAWN_END_HOUR       7       //  = 05 - 07   //  old = 8  : 07 - 08
#define DAY_END_HOUR        17      //  = 07 - 17   //  old = 19 : 08 - 19
#define SUNSET_END_HOUR     18      //  = 17 - 18   //  old = 20 : 19 - 20
#define NIGHTFALL_END_HOUR  19      //  = 18 - 19   //  old = 21 : 20 - 21
#define NIGHT_END_HOUR      0       //  = 19 - 00   //  old = 0  : 21 - 00

/* Start and end hour of the lightning system.
 * This system is generally used for building's windows. */
#define LIGHTNING_START_HOUR    NIGHTFALL_END_HOUR
#define LIGHTNING_END_HOUR      MIDNIGHT_END_HOUR



struct LightingColour {
    u8 paletteNum;
    u8 colourNum;
    u16 lightColour;
};

struct DnsPalExceptions {
    bool8 pal[32];
};

void DnsTransferPlttBuffer(void *src, void *dest);
void DnsApplyFilters();
u8 GetDnsTimeLapse(u8 hour);
bool8 IsNight(void);
u8 GetCurrentTimeLapse(void);

#endif /* GUARD_DNS_UTILS_H */

