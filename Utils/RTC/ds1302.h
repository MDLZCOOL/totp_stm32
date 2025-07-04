/**
 ******************************************************************************
 * @file         ds1302.c
 * @author       Aaron Escoboza
 * @brief        header file for DS1302 RTC driver
 * @link         GitGub : https://github.com/aaron-ev
 ******************************************************************************
 */
#ifndef __DS1302__H
#define __DS1302__H

#include "stm32f4xx_hal.h"
#include "stdint.h"
#include <string.h>

/************* Configuration section **************/
#define DS1302_GPIO_PORT            GPIOE
#define DS1302_PIN_SCLK             GPIO_PIN_4
#define DS1302_PIN_SDA              GPIO_PIN_5
#define DS1302_PIN_RST              GPIO_PIN_6
/************* Configuration section **************/

#define DS1302_RAM_SIZE             31

/**
 * Enumeration for days of the week
 */
typedef enum
{
    MONDAY =  1, /* Valid values 1 - 7*/
    TUESDAY,
    WEDNESDAY,
    THURSDAY,
    FRIDAY,
    SATURDAY,
    SUNDAY,
}Day;

/**
 * Enumeration for clock system (12/24)
 */
typedef enum 
{
    DS1302_CLK_SYSTEM_24,
    DS1302_CLK_SYSTEM_12,
}ClockSystem; 

/**
 * Enumeration for clock period (AM or PM)
 */
typedef enum 
{
    DS1302_CLK_AM_PERIOD,
    DS1302_CLK_PM_PERIOD,
}ClockPeriod;

/**
 * Structure for holding time data
 */
typedef struct
{
    Day day; /* Range: enum day values*/
    uint8_t sec; /* Range: 0-59 */
    uint8_t min; /* Range: 0-59 */
    uint8_t year; /* Range: 0 - 99 */
    uint8_t hour; /* Range: 1-12/0-23*/
    uint8_t date;  /* Range: 1 - 31 */
    uint8_t month; /* Range: 1 - 12 */
    ClockSystem clockSystem; /* 12 or 24 clock system */
    ClockPeriod clockPeriod; /* AM or PM*/
}Time_s;

void ds1302_init(void);

void ds1302_get_time(Time_s *time);
void ds1302_set_time(const Time_s *time);

void ds1302_clear_ram(void);
uint8_t ds1302_read_ram(const uint8_t addr);
void ds1302_write_ram(const uint8_t addr, uint8_t data);

ClockSystem ds1302_get_clock_system(void);
ClockPeriod ds1302_get_clock_period(void);

void ds1302_write_ram_burst(uint8_t len, uint8_t *buff);
void ds1302_read_ram_burst(uint8_t len, uint8_t *buff);

#endif
