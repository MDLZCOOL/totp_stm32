/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2025 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H
#define __MAIN_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32f4xx_hal.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "ds1302.h"

/* USER CODE END Includes */

/* Exported types ------------------------------------------------------------*/
/* USER CODE BEGIN ET */

/* USER CODE END ET */

/* Exported constants --------------------------------------------------------*/
/* USER CODE BEGIN EC */

/* USER CODE END EC */

/* Exported macro ------------------------------------------------------------*/
/* USER CODE BEGIN EM */

/* USER CODE END EM */

/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);

/* USER CODE BEGIN EFP */
extern SPI_HandleTypeDef hspi1;
extern SPI_HandleTypeDef hspi2;
extern I2C_HandleTypeDef hi2c3;
extern Time_s syncTime;
extern Time_s systemTime;
extern int sync_state; // 0 refer OK, 1 refer fail
extern int err_times;
void SPI1_SetSpeed(uint8_t SpeedSet);
  uint32_t struct_time_timestamp(Time_s *time);
/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
#define DS1302_SCK_Pin GPIO_PIN_4
#define DS1302_SCK_GPIO_Port GPIOE
#define DS1302_IO_Pin GPIO_PIN_5
#define DS1302_IO_GPIO_Port GPIOE
#define DS1302_CE_Pin GPIO_PIN_6
#define DS1302_CE_GPIO_Port GPIOE
#define LCD_PWR_Pin GPIO_PIN_1
#define LCD_PWR_GPIO_Port GPIOA
#define LCD_CS_Pin GPIO_PIN_2
#define LCD_CS_GPIO_Port GPIOA
#define LCD_DC_Pin GPIO_PIN_3
#define LCD_DC_GPIO_Port GPIOA
#define LCD_RESET_Pin GPIO_PIN_4
#define LCD_RESET_GPIO_Port GPIOA
#define LED1_Pin GPIO_PIN_2
#define LED1_GPIO_Port GPIOB
#define W25Q_CS_Pin GPIO_PIN_15
#define W25Q_CS_GPIO_Port GPIOE
#define TP_INT_Pin GPIO_PIN_7
#define TP_INT_GPIO_Port GPIOC
#define TP_RESET_Pin GPIO_PIN_8
#define TP_RESET_GPIO_Port GPIOC

/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
