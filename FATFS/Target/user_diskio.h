/* USER CODE BEGIN Header */
/**
 ******************************************************************************
  * @file    user_diskio.h
  * @brief   This file contains the common defines and functions prototypes for
  *          the user_diskio driver.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2024 STMicroelectronics.
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
#ifndef __USER_DISKIO_H
#define __USER_DISKIO_H

#ifdef __cplusplus
 extern "C" {
#endif

/* USER CODE BEGIN 0 */

/* Includes ------------------------------------------------------------------*/
#include "diskio.h"
#include "integer.h"
#include "ff_gen_drv.h"
/* Exported types ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/
/* Exported functions ------------------------------------------------------- */
DRESULT USER_read(
    BYTE pdrv, /* Physical drive nmuber to identify the drive */
    BYTE* buff, /* Data buffer to store read data */
    DWORD sector, /* Sector address in LBA */
    UINT count /* Number of sectors to read */
);
DRESULT USER_write(
    BYTE pdrv, /* Physical drive nmuber to identify the drive */
    const BYTE* buff, /* Data to be written */
    DWORD sector, /* Sector address in LBA */
    UINT count /* Number of sectors to write */
);

extern Diskio_drvTypeDef USER_Driver;

/* USER CODE END 0 */

#ifdef __cplusplus
}
#endif

#endif /* __USER_DISKIO_H */
