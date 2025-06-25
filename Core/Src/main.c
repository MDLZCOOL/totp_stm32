/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
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
/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "fatfs.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include <stdio.h>
#include <sys/errno.h>
#include "SEGGER_RTT.h"

#include "lvgl.h"
#include "lv_port_disp.h"
#include "lv_port_indev.h"
#include "gui_guider.h"

#include "TOTP.h"
#include <time.h>

#include "app_usb_msc.h"
#include "ffconf.h"
#include "ff.h"
#include "file_opera.h"
#include "w25flash.h"

#include "base32.h"
#include "ds1302.h"
#include "usbd_core.h"
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
#define BLK_ON HAL_GPIO_WritePin(LCD_PWR_GPIO_Port, LCD_PWR_Pin, GPIO_PIN_SET);
#define BLK_OFF HAL_GPIO_WritePin(LCD_PWR_GPIO_Port, LCD_PWR_Pin, GPIO_PIN_RESET);
#define printf(...) SEGGER_RTT_printf(0, ##__VA_ARGS__)
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
I2C_HandleTypeDef hi2c3;

RTC_HandleTypeDef hrtc;

SPI_HandleTypeDef hspi1;
SPI_HandleTypeDef hspi2;
DMA_HandleTypeDef hdma_spi1_rx;
DMA_HandleTypeDef hdma_spi1_tx;

PCD_HandleTypeDef hpcd_USB_OTG_FS;

/* USER CODE BEGIN PV */
uint8_t hours, minutes, seconds;
uint8_t weekday, date, month;
uint16_t year;
RTC_TimeTypeDef sTime;
RTC_DateTypeDef sDate;
uint32_t current_timestamp;
lv_ui guider_ui;
uint8_t hmacKey[] = {0x87, 0xa8, 0xfa, 0x14, 0x93, 0x6c, 0x4e, 0x64, 0x91, 0x0e};
uint8_t testbase32[128] = {0};
Time_s syncTime = {.clockSystem = DS1302_CLK_SYSTEM_24};
Time_s systemTime = {.clockSystem = DS1302_CLK_SYSTEM_24};
int sync_state = 3; // 0 refer OK, 1 refer fail, 3 refer init
int err_times = 0;
/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_DMA_Init(void);
static void MX_SPI1_Init(void);
static void MX_RTC_Init(void);
static void MX_USB_OTG_FS_PCD_Init(void);
static void MX_I2C3_Init(void);
static void MX_SPI2_Init(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */
int _write(int file, char* ptr, int len)
{
  if (file == 1 /* stdout */ || file == 2 /* stderr */)
  {
    return SEGGER_RTT_Write(0, ptr, len);
  }
  errno = EBADF;
  return -1;
}

void update_table(lv_obj_t * obj)
{
  // row 1
  lv_table_set_cell_value(obj,1,0,"0");
  lv_table_set_cell_value(obj,1,1,"1");
  // lv_table_set_cell_value(obj,1,2,"2");

  // row 2
  lv_table_set_cell_value(obj,2,0,"0");
  lv_table_set_cell_value(obj,2,1,"1");
  // lv_table_set_cell_value(obj,2,2,"2");

  // row 3
  lv_table_set_cell_value(obj,3,0,"0");
  lv_table_set_cell_value(obj,3,1,"1");
  // lv_table_set_cell_value(obj,3,2,"2");

  // row 4
  lv_table_set_cell_value(obj,4,0,"0");
  lv_table_set_cell_value(obj,4,1,"1");
  // lv_table_set_cell_value(obj,4,2,"2");

  // row 5
  lv_table_set_cell_value(obj,5,0,"0");
  lv_table_set_cell_value(obj,5,1,"1");
  // lv_table_set_cell_value(obj,5,2,"2");
}


static void callback_import_account(lv_event_t* event)
{
  lv_event_code_t code = lv_event_get_code(event);
  if (code == LV_EVENT_CLICKED)
  {
    printf("callback_import_account\r\n");
    lv_obj_clear_flag(guider_ui.screen_msgbox_1, LV_OBJ_FLAG_HIDDEN);
    msc_init(0, USB_OTG_FS_PERIPH_BASE);
  }
}

static void callback_close_msc(lv_event_t* event)
{
  lv_event_code_t code = lv_event_get_code(event);
  if (code == LV_EVENT_CLICKED)
  {
    printf("callback_close_msc\r\n");
    read_and_parse_data("0:account.txt");
    lv_obj_add_flag(guider_ui.screen_msgbox_1, LV_OBJ_FLAG_HIDDEN);
    usbd_deinitialize(0);
  }
}

static void callback_sync_timestamp(lv_event_t* event)
{
  lv_event_code_t code = lv_event_get_code(event);
  if (code == LV_EVENT_CLICKED)
  {
    printf("callback_sync_timestamp\r\n");
    lv_obj_clear_flag(guider_ui.screen_msgbox_2, LV_OBJ_FLAG_HIDDEN);
    extern void cdc_acm_init(uint8_t busid, uintptr_t reg_base);
    cdc_acm_init(0, USB_OTG_FS_PERIPH_BASE);
  }
}

static void callback_close_cdc_acm(lv_event_t* event)
{
  lv_event_code_t code = lv_event_get_code(event);
  if (code == LV_EVENT_CLICKED)
  {
    printf("callback_close_cdc_acm\r\n");
    lv_obj_add_flag(guider_ui.screen_msgbox_2, LV_OBJ_FLAG_HIDDEN);
    usbd_deinitialize(0);
  }
}

uint32_t struct_time_timestamp(Time_s *time)
{
  struct tm t;

  t.tm_year = time->year + 2000 - 1900;
  t.tm_mon = time->month;
  t.tm_mday = time->date;
  t.tm_hour = time->hour;
  t.tm_min = time->min;
  t.tm_sec = time->sec;

  return mktime(&t);
}

/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{

  /* USER CODE BEGIN 1 */

  /* USER CODE END 1 */

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_DMA_Init();
  MX_SPI1_Init();
  MX_RTC_Init();
  MX_I2C3_Init();
  MX_FATFS_Init();
  MX_SPI2_Init();
  /* USER CODE BEGIN 2 */
  SEGGER_RTT_Init();
  SEGGER_RTT_printf(0, "System begin...\r\n");

  ds1302_init();

  TOTP(hmacKey, 10, 30);

  BLK_OFF;
  lv_init();
  lv_port_disp_init();
  lv_port_indev_init();
  setup_ui(&guider_ui);
  BLK_ON;

  W25QXX_Init();

  read_and_parse_data("0:account.txt");

  lv_obj_add_event_cb(guider_ui.screen_list_2_item1, callback_import_account, LV_EVENT_CLICKED, NULL);
  lv_obj_add_event_cb(guider_ui.screen_msgbox_1, callback_close_msc, LV_EVENT_CLICKED, NULL);

  lv_obj_add_event_cb(guider_ui.screen_list_4_item0, callback_sync_timestamp, LV_EVENT_CLICKED, NULL);
  lv_obj_add_event_cb(guider_ui.screen_msgbox_2, callback_close_cdc_acm, LV_EVENT_CLICKED, NULL);
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
    ds1302_get_time(&systemTime);
    if (systemTime.sec >= 30)
    {
      char tmp[16] = {0};
      sprintf(tmp, "%d", 60 - systemTime.sec);
      lv_table_set_cell_value(guider_ui.screen_table_1, 1, 2, tmp);
      lv_table_set_cell_value(guider_ui.screen_table_1, 2, 2, tmp);
      lv_table_set_cell_value(guider_ui.screen_table_1, 3, 2, tmp);
      lv_table_set_cell_value(guider_ui.screen_table_1, 4, 2, tmp);
      lv_table_set_cell_value(guider_ui.screen_table_1, 5, 2, tmp);
    }else
    {
      char tmp[16] = {0};
      sprintf(tmp, "%d",30 - systemTime.sec);
      lv_table_set_cell_value(guider_ui.screen_table_1, 1, 2, tmp);
      lv_table_set_cell_value(guider_ui.screen_table_1, 2, 2, tmp);
      lv_table_set_cell_value(guider_ui.screen_table_1, 3, 2, tmp);
      lv_table_set_cell_value(guider_ui.screen_table_1, 4, 2, tmp);
      lv_table_set_cell_value(guider_ui.screen_table_1, 5, 2, tmp);
    }

    if (sync_state == 1 && err_times == 0)
    {
      err_times = 1;
      extern void usb_transmit_string(uint8_t *data, int32_t length);
      usb_transmit_string("fail\r\n", 6);
    }else if (sync_state == 0 && err_times == 0)
    {
      err_times = 1;
      extern void usb_transmit_string(uint8_t *data, int32_t length);
      usb_transmit_string("ok\r\n", 6);
    }
    current_timestamp = struct_time_timestamp(&systemTime) - (uint32_t) 2620801;
    uint32_t code = getCodeFromSteps(current_timestamp / 30);
    SEGGER_RTT_printf(0, "Current Unix Timestamp: %lu\r\n", current_timestamp);
    SEGGER_RTT_printf(0, "Current Code: %lu\r\n", code);
    // SEGGER_RTT_printf(0, "alive\r\n");
    lv_timer_handler();
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
  }
  /* USER CODE END 3 */
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  /** Configure the main internal regulator output voltage
  */
  __HAL_RCC_PWR_CLK_ENABLE();
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_LSI|RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.LSIState = RCC_LSI_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLM = 4;
  RCC_OscInitStruct.PLL.PLLN = 168;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
  RCC_OscInitStruct.PLL.PLLQ = 7;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV4;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV2;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_5) != HAL_OK)
  {
    Error_Handler();
  }
}

/**
  * @brief I2C3 Initialization Function
  * @param None
  * @retval None
  */
static void MX_I2C3_Init(void)
{

  /* USER CODE BEGIN I2C3_Init 0 */

  /* USER CODE END I2C3_Init 0 */

  /* USER CODE BEGIN I2C3_Init 1 */

  /* USER CODE END I2C3_Init 1 */
  hi2c3.Instance = I2C3;
  hi2c3.Init.ClockSpeed = 100000;
  hi2c3.Init.DutyCycle = I2C_DUTYCYCLE_2;
  hi2c3.Init.OwnAddress1 = 0;
  hi2c3.Init.AddressingMode = I2C_ADDRESSINGMODE_7BIT;
  hi2c3.Init.DualAddressMode = I2C_DUALADDRESS_DISABLE;
  hi2c3.Init.OwnAddress2 = 0;
  hi2c3.Init.GeneralCallMode = I2C_GENERALCALL_DISABLE;
  hi2c3.Init.NoStretchMode = I2C_NOSTRETCH_DISABLE;
  if (HAL_I2C_Init(&hi2c3) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN I2C3_Init 2 */

  /* USER CODE END I2C3_Init 2 */

}

/**
  * @brief RTC Initialization Function
  * @param None
  * @retval None
  */
static void MX_RTC_Init(void)
{

  /* USER CODE BEGIN RTC_Init 0 */

  /* USER CODE END RTC_Init 0 */

  RTC_TimeTypeDef sTime = {0};
  RTC_DateTypeDef sDate = {0};
  RTC_AlarmTypeDef sAlarm = {0};

  /* USER CODE BEGIN RTC_Init 1 */

  /* USER CODE END RTC_Init 1 */

  /** Initialize RTC Only
  */
  hrtc.Instance = RTC;
  hrtc.Init.HourFormat = RTC_HOURFORMAT_24;
  hrtc.Init.AsynchPrediv = 127;
  hrtc.Init.SynchPrediv = 255;
  hrtc.Init.OutPut = RTC_OUTPUT_DISABLE;
  hrtc.Init.OutPutPolarity = RTC_OUTPUT_POLARITY_HIGH;
  hrtc.Init.OutPutType = RTC_OUTPUT_TYPE_OPENDRAIN;
  if (HAL_RTC_Init(&hrtc) != HAL_OK)
  {
    Error_Handler();
  }

  /* USER CODE BEGIN Check_RTC_BKUP */

  /* USER CODE END Check_RTC_BKUP */

  /** Initialize RTC and set the Time and Date
  */
  sTime.Hours = 0x0;
  sTime.Minutes = 0x0;
  sTime.Seconds = 0x0;
  sTime.DayLightSaving = RTC_DAYLIGHTSAVING_NONE;
  sTime.StoreOperation = RTC_STOREOPERATION_RESET;
  if (HAL_RTC_SetTime(&hrtc, &sTime, RTC_FORMAT_BCD) != HAL_OK)
  {
    Error_Handler();
  }
  sDate.WeekDay = RTC_WEEKDAY_MONDAY;
  sDate.Month = RTC_MONTH_JANUARY;
  sDate.Date = 0x1;
  sDate.Year = 0x0;

  if (HAL_RTC_SetDate(&hrtc, &sDate, RTC_FORMAT_BCD) != HAL_OK)
  {
    Error_Handler();
  }

  /** Enable the Alarm A
  */
  sAlarm.AlarmTime.Hours = 0x0;
  sAlarm.AlarmTime.Minutes = 0x0;
  sAlarm.AlarmTime.Seconds = 0x1;
  sAlarm.AlarmTime.SubSeconds = 0x0;
  sAlarm.AlarmTime.DayLightSaving = RTC_DAYLIGHTSAVING_NONE;
  sAlarm.AlarmTime.StoreOperation = RTC_STOREOPERATION_RESET;
  sAlarm.AlarmMask = RTC_ALARMMASK_DATEWEEKDAY|RTC_ALARMMASK_HOURS
                              |RTC_ALARMMASK_MINUTES;
  sAlarm.AlarmSubSecondMask = RTC_ALARMSUBSECONDMASK_ALL;
  sAlarm.AlarmDateWeekDaySel = RTC_ALARMDATEWEEKDAYSEL_DATE;
  sAlarm.AlarmDateWeekDay = 0x1;
  sAlarm.Alarm = RTC_ALARM_A;
  if (HAL_RTC_SetAlarm_IT(&hrtc, &sAlarm, RTC_FORMAT_BCD) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN RTC_Init 2 */

  /* USER CODE END RTC_Init 2 */

}

/**
  * @brief SPI1 Initialization Function
  * @param None
  * @retval None
  */
static void MX_SPI1_Init(void)
{

  /* USER CODE BEGIN SPI1_Init 0 */

  /* USER CODE END SPI1_Init 0 */

  /* USER CODE BEGIN SPI1_Init 1 */

  /* USER CODE END SPI1_Init 1 */
  /* SPI1 parameter configuration*/
  hspi1.Instance = SPI1;
  hspi1.Init.Mode = SPI_MODE_MASTER;
  hspi1.Init.Direction = SPI_DIRECTION_2LINES;
  hspi1.Init.DataSize = SPI_DATASIZE_8BIT;
  hspi1.Init.CLKPolarity = SPI_POLARITY_LOW;
  hspi1.Init.CLKPhase = SPI_PHASE_1EDGE;
  hspi1.Init.NSS = SPI_NSS_SOFT;
  hspi1.Init.BaudRatePrescaler = SPI_BAUDRATEPRESCALER_2;
  hspi1.Init.FirstBit = SPI_FIRSTBIT_MSB;
  hspi1.Init.TIMode = SPI_TIMODE_DISABLE;
  hspi1.Init.CRCCalculation = SPI_CRCCALCULATION_DISABLE;
  hspi1.Init.CRCPolynomial = 10;
  if (HAL_SPI_Init(&hspi1) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN SPI1_Init 2 */

  /* USER CODE END SPI1_Init 2 */

}

/**
  * @brief SPI2 Initialization Function
  * @param None
  * @retval None
  */
static void MX_SPI2_Init(void)
{

  /* USER CODE BEGIN SPI2_Init 0 */

  /* USER CODE END SPI2_Init 0 */

  /* USER CODE BEGIN SPI2_Init 1 */

  /* USER CODE END SPI2_Init 1 */
  /* SPI2 parameter configuration*/
  hspi2.Instance = SPI2;
  hspi2.Init.Mode = SPI_MODE_MASTER;
  hspi2.Init.Direction = SPI_DIRECTION_2LINES;
  hspi2.Init.DataSize = SPI_DATASIZE_8BIT;
  hspi2.Init.CLKPolarity = SPI_POLARITY_LOW;
  hspi2.Init.CLKPhase = SPI_PHASE_1EDGE;
  hspi2.Init.NSS = SPI_NSS_SOFT;
  hspi2.Init.BaudRatePrescaler = SPI_BAUDRATEPRESCALER_8;
  hspi2.Init.FirstBit = SPI_FIRSTBIT_MSB;
  hspi2.Init.TIMode = SPI_TIMODE_DISABLE;
  hspi2.Init.CRCCalculation = SPI_CRCCALCULATION_DISABLE;
  hspi2.Init.CRCPolynomial = 10;
  if (HAL_SPI_Init(&hspi2) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN SPI2_Init 2 */

  /* USER CODE END SPI2_Init 2 */

}

/**
  * @brief USB_OTG_FS Initialization Function
  * @param None
  * @retval None
  */
static void MX_USB_OTG_FS_PCD_Init(void)
{

  /* USER CODE BEGIN USB_OTG_FS_Init 0 */

  /* USER CODE END USB_OTG_FS_Init 0 */

  /* USER CODE BEGIN USB_OTG_FS_Init 1 */

  /* USER CODE END USB_OTG_FS_Init 1 */
  hpcd_USB_OTG_FS.Instance = USB_OTG_FS;
  hpcd_USB_OTG_FS.Init.dev_endpoints = 4;
  hpcd_USB_OTG_FS.Init.speed = PCD_SPEED_FULL;
  hpcd_USB_OTG_FS.Init.dma_enable = DISABLE;
  hpcd_USB_OTG_FS.Init.phy_itface = PCD_PHY_EMBEDDED;
  hpcd_USB_OTG_FS.Init.Sof_enable = DISABLE;
  hpcd_USB_OTG_FS.Init.low_power_enable = DISABLE;
  hpcd_USB_OTG_FS.Init.lpm_enable = DISABLE;
  hpcd_USB_OTG_FS.Init.vbus_sensing_enable = DISABLE;
  hpcd_USB_OTG_FS.Init.use_dedicated_ep1 = DISABLE;
  if (HAL_PCD_Init(&hpcd_USB_OTG_FS) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN USB_OTG_FS_Init 2 */

  /* USER CODE END USB_OTG_FS_Init 2 */

}

/**
  * Enable DMA controller clock
  */
static void MX_DMA_Init(void)
{

  /* DMA controller clock enable */
  __HAL_RCC_DMA2_CLK_ENABLE();

  /* DMA interrupt init */
  /* DMA2_Stream0_IRQn interrupt configuration */
  HAL_NVIC_SetPriority(DMA2_Stream0_IRQn, 0, 0);
  HAL_NVIC_EnableIRQ(DMA2_Stream0_IRQn);
  /* DMA2_Stream3_IRQn interrupt configuration */
  HAL_NVIC_SetPriority(DMA2_Stream3_IRQn, 0, 0);
  HAL_NVIC_EnableIRQ(DMA2_Stream3_IRQn);

}

/**
  * @brief GPIO Initialization Function
  * @param None
  * @retval None
  */
static void MX_GPIO_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};
/* USER CODE BEGIN MX_GPIO_Init_1 */
/* USER CODE END MX_GPIO_Init_1 */

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOE_CLK_ENABLE();
  __HAL_RCC_GPIOC_CLK_ENABLE();
  __HAL_RCC_GPIOH_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOE, DS1302_SCK_Pin|DS1302_IO_Pin|DS1302_CE_Pin|W25Q_CS_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOA, LCD_PWR_Pin|LCD_CS_Pin|LCD_DC_Pin|LCD_RESET_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(LED1_GPIO_Port, LED1_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOC, TP_INT_Pin|TP_RESET_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pins : DS1302_SCK_Pin DS1302_IO_Pin DS1302_CE_Pin */
  GPIO_InitStruct.Pin = DS1302_SCK_Pin|DS1302_IO_Pin|DS1302_CE_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOE, &GPIO_InitStruct);

  /*Configure GPIO pins : LCD_PWR_Pin LCD_CS_Pin LCD_DC_Pin LCD_RESET_Pin */
  GPIO_InitStruct.Pin = LCD_PWR_Pin|LCD_CS_Pin|LCD_DC_Pin|LCD_RESET_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  /*Configure GPIO pin : LED1_Pin */
  GPIO_InitStruct.Pin = LED1_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(LED1_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pin : W25Q_CS_Pin */
  GPIO_InitStruct.Pin = W25Q_CS_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
  HAL_GPIO_Init(W25Q_CS_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pin : TP_INT_Pin */
  GPIO_InitStruct.Pin = TP_INT_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
  HAL_GPIO_Init(TP_INT_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pin : TP_RESET_Pin */
  GPIO_InitStruct.Pin = TP_RESET_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_PULLUP;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
  HAL_GPIO_Init(TP_RESET_GPIO_Port, &GPIO_InitStruct);

/* USER CODE BEGIN MX_GPIO_Init_2 */
/* USER CODE END MX_GPIO_Init_2 */
}

/* USER CODE BEGIN 4 */
void SPI1_SetSpeed(uint8_t SpeedSet)
{

  if(SpeedSet==1)
  {
    hspi1.Init.BaudRatePrescaler = SPI_BAUDRATEPRESCALER_2;
  }
  else
  {
    hspi1.Init.BaudRatePrescaler = SPI_BAUDRATEPRESCALER_8;
  }
  if (HAL_SPI_Init(&hspi1) != HAL_OK)
  {
    Error_Handler();
  }
}
/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  __disable_irq();
  while (1)
  {
  }
  /* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */
