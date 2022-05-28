#ifndef GUARD_DAY_DIV_UTIL_H
#define GUARD_DAY_DIV_UTIL_H

/*enum
{
    DAY_DIV_NULL,
    DAY_DIV_12H,
    DAY_DIV_8H,
    DAY_DIV_6H,
    DAY_DIV_4H,
    DAY_DIV_2H,
    DAY_DIV_END
};*/

#define DAY_DIV_NULL    0
#define DAY_DIV_12H     12
#define DAY_DIV_8H      8
#define DAY_DIV_6H      6
#define DAY_DIV_4H      4
#define DAY_DIV_2H      2

/**
 * Define las horas en que se dividirá un día.
 * Para efectos prácticos = 1 día (24h) / DAY_DIV_?H
 * así, DAY_DIV_4H divide un día en 6 días.
 * Tendrá relevancia con el DNS y las evoluciones.
*/
#define DAY_MODE DAY_DIV_4H

#define DAY_PER_24 (24 / DAY_MODE)
#define MIN_PER_HOUR (60 / DAY_PER_24)

extern struct Time gDayTime;// IWRAM [8 bytes]   /align  0x03007700;

void DayDiv_Update(void);

#endif // GUARD_DAY_DIV_UTIL_H