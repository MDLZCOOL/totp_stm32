#pragma once

#include "main.h"

void set_rtc_time_and_date(uint8_t hours, uint8_t minutes, uint8_t seconds,
                           uint8_t weekday, uint8_t date, uint8_t month, uint16_t year);

void get_rtc_time_and_date(uint8_t *hours, uint8_t *minutes, uint8_t *seconds,
                           uint8_t *weekday, uint8_t *date, uint8_t *month, uint16_t *year);

uint32_t get_unix_timestamp(RTC_TimeTypeDef *pTime, RTC_DateTypeDef *pDate);

uint32_t get_current_timestamp_and_datetime(uint8_t *hours, uint8_t *minutes, uint8_t *seconds,
                                            uint8_t *weekday, uint8_t *date, uint8_t *month, uint16_t *year);