#include "rtc_utils.h"

#define IS_LEAP_YEAR(year) (((year % 4 == 0) && (year % 100 != 0)) || (year % 400 == 0))

const uint8_t days_in_month[] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

void set_rtc_time_and_date(uint8_t hours, uint8_t minutes, uint8_t seconds,
                           uint8_t weekday, uint8_t date, uint8_t month, uint16_t year)
{
    RTC_TimeTypeDef sTime = {0};
    RTC_DateTypeDef sDate = {0};

    sTime.Hours = hours;
    sTime.Minutes = minutes;
    sTime.Seconds = seconds;
    sTime.DayLightSaving = RTC_DAYLIGHTSAVING_NONE;
    sTime.StoreOperation = RTC_STOREOPERATION_RESET;

    sDate.WeekDay = weekday;
    sDate.Month = month;
    sDate.Date = date;
    sDate.Year = year - 2000;

    if (HAL_RTC_SetTime(&hrtc, &sTime, RTC_FORMAT_BIN) != HAL_OK)
    {
        Error_Handler();
    }

    if (HAL_RTC_SetDate(&hrtc, &sDate, RTC_FORMAT_BIN) != HAL_OK)
    {
        Error_Handler();
    }

    // HAL_RTCEx_BKUPWrite(&hrtc, RTC_BKP_DR1, 0x32F2);
}

void get_rtc_time_and_date(uint8_t *hours, uint8_t *minutes, uint8_t *seconds,
                           uint8_t *weekday, uint8_t *date, uint8_t *month, uint16_t *year)
{
    RTC_TimeTypeDef sTime = {0};
    RTC_DateTypeDef sDate = {0};

    if (HAL_RTC_GetTime(&hrtc, &sTime, RTC_FORMAT_BIN) != HAL_OK)
    {
        Error_Handler();
    }

    if (HAL_RTC_GetDate(&hrtc, &sDate, RTC_FORMAT_BIN) != HAL_OK)
    {
        Error_Handler();
    }

    *hours = sTime.Hours;
    *minutes = sTime.Minutes;
    *seconds = sTime.Seconds;

    *weekday = sDate.WeekDay;
    *date = sDate.Date;
    *month = sDate.Month;
    *year = sDate.Year + 2000;
}

uint32_t get_unix_timestamp(RTC_TimeTypeDef *pTime, RTC_DateTypeDef *pDate)
{
    uint32_t timestamp = 0;
    uint16_t year = pDate->Year + 2000;
    uint8_t month = pDate->Month;
    uint8_t day = pDate->Date;
    uint8_t hour = pTime->Hours;
    uint8_t minute = pTime->Minutes;
    uint8_t second = pTime->Seconds;

    for (uint16_t y = 1970; y < year; y++)
    {
        timestamp += (IS_LEAP_YEAR(y) ? 366 : 365) * 24 * 60 * 60;
    }

    for (uint8_t m = 1; m < month; m++)
    {
        timestamp += days_in_month[m] * 24 * 60 * 60;
        if (m == 2 && IS_LEAP_YEAR(year))
        {
            timestamp += 24 * 60 * 60;
        }
    }

    timestamp += (day - 1) * 24 * 60 * 60;
    timestamp += hour * 60 * 60;
    timestamp += minute * 60;
    timestamp += second;

    return timestamp;
}

uint32_t get_current_timestamp_and_datetime(uint8_t *hours, uint8_t *minutes, uint8_t *seconds,
                                            uint8_t *weekday, uint8_t *date, uint8_t *month, uint16_t *year)
{
    get_rtc_time_and_date(hours, minutes, seconds,
                           weekday, date, month, year);

    RTC_TimeTypeDef sTime = {0};
    RTC_DateTypeDef sDate = {0};

    sTime.Hours = *hours;
    sTime.Minutes = *minutes;
    sTime.Seconds = *seconds;
    sTime.DayLightSaving = RTC_DAYLIGHTSAVING_NONE;
    sTime.StoreOperation = RTC_STOREOPERATION_RESET;

    sDate.WeekDay = *weekday;
    sDate.Month = *month;
    sDate.Date = *date;
    sDate.Year = *year - 2000;

    return get_unix_timestamp(&sTime, &sDate);
}