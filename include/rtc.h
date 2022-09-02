#ifndef GUARD_RTC_UTIL_H
#define GUARD_RTC_UTIL_H

#include "siirtc.h"

#define RTC_INIT_ERROR         0x0001
#define RTC_INIT_WARNING       0x0002

#define RTC_ERR_12HOUR_CLOCK   0x0010
#define RTC_ERR_POWER_FAILURE  0x0020
#define RTC_ERR_INVALID_YEAR   0x0040
#define RTC_ERR_INVALID_MONTH  0x0080
#define RTC_ERR_INVALID_DAY    0x0100
#define RTC_ERR_INVALID_HOUR   0x0200
#define RTC_ERR_INVALID_MINUTE 0x0400
#define RTC_ERR_INVALID_SECOND 0x0800

#define RTC_ERR_FLAG_MASK      0x0FF0

extern struct Time gLocalTime;      // IWRAM [8 bytes]   /align  0x030074d0;
extern struct Time gLocalTime_copy; // IWRAM [8 bytes]   /align  0x030074d0;

void RtcDisableInterrupts(void);
void RtcRestoreInterrupts(void);
u32 ConvertBcdToBinary(u8 bcd);
bool8 IsLeapYear(u32 year);
u16 ConvertDateToDayCount(u8 year, u8 month, u8 day);
u16 RtcGetDayCount(struct SiiRtcInfo *rtc);
void RtcInit(void);
u16 RtcGetErrorStatus(void);
void RtcGetInfo(struct SiiRtcInfo *rtc);
void RtcGetDateTime(struct SiiRtcInfo *rtc);
void RtcGetStatus(struct SiiRtcInfo *rtc);
void RtcGetRawInfo(struct SiiRtcInfo *rtc);
u16 RtcCheckInfo(struct SiiRtcInfo *rtc);
void RtcReset(void);
void FormatDecimalTime(u8 *dest, s32 hour, s32 minute, s32 second);
void FormatHexTime(u8 *dest, s32 hour, s32 minute, s32 second);
void FormatHexRtcTime(u8 *dest);
void FormatDecimalDate(u8 *dest, s32 year, s32 month, s32 day);
void FormatHexDate(u8 *dest, s32 year, s32 month, s32 day);
void RtcCalcTimeDifference(struct SiiRtcInfo *rtc, struct Time *result, struct Time *t);
void RtcCalcLocalTime(void);
void RtcInitLocalTimeOffset(s32 hour, s32 minute);
void RtcCalcLocalTimeOffset(s32 days, s32 hours, s32 minutes, s32 seconds);
void CalcTimeDifference(struct Time *result, struct Time *t1, struct Time *t2);
u32 RtcGetMinuteCount(void);
u32 RtcGetLocalDayCount(void);


#define DAY_TIME_DEFAULT 24
#define DAY_TIME_12H     12
#define DAY_TIME_8H      8
#define DAY_TIME_6H      6
#define DAY_TIME_4H      4
#define DAY_TIME_2H      2

/**
 * DAY_MODE:
 * Define las horas en que se dividirá un día.
 * Para efectos prácticos = 1 día (24h) / DAY_TIME_?H
 * Esto quiere decir, que un día pasa en 4 horas.
 * Así, DAY_TIME_4H divide un día en 6 días.
 * 
 * Afecta el DNS y las evoluciones.
*/
#define DAY_MODE DAY_TIME_2H

#define DAY_PER_24 (24 / DAY_MODE)
#define MIN_PER_HOUR (60 / DAY_PER_24)

u8 GetCurrentDayOfWeek(void);
u8 GetCurrentHour(void);
u8 GetCurrentMinutes(void);
void acimut_time_update(struct Time *t_src, struct Time *t_dst);


#endif // GUARD_RTC_UTIL_H
