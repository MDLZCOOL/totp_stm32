/**
  ******************************************************************************
  * @file           : file_opera.c
  * @author         : Kevin_WWW
  * @brief          : None
  * @attention      : None
  * @date           : 2024/4/25
  ******************************************************************************
  */
#include "file_opera.h"

#include "gui_guider.h"

void fatTest_GetDiskInfo() {
    FATFS *fs;
    DWORD free_clust;
    FRESULT res = f_getfree("0:", &free_clust, &fs);
    if (res != FR_OK) {
        printf("f_getfree() error\r\n");
        return;
    }
    printf("*** FAT disk info ***\r\n");
    DWORD total_sector = (fs->n_fatent - 2) * fs->csize;
    DWORD free_sector = free_clust * fs->csize;

#if _MAX_SS == _MIN_SS
    DWORD free_space = free_sector >> 11;
    DWORD total_space = total_sector >> 11;
#else
    DWORD free_space = (free_sector * fs->ssize) >> 10;
    DWORD total_space = (total_sector * fs->ssize) >> 10;
#endif

    printf("FAT type = %d\r\n", (int)fs->fs_type);
    printf("[1=FAT12,2=FAT16,3=FAT32,4=EXFAT]\r\n");

    printf("Sector size(bytes) = %d\r\n", fs->ssize);

    printf("Cluster size(sectors) = %d\r\n", fs->csize);

    printf("Total cluster count = %d\r\n", fs->n_fatent - 2);

    printf("Total sector count = %d\r\n", total_sector);

    printf("Total space(KB) = %d\r\n", total_space);

    printf("Free cluster count = %d\r\n", free_clust);

    printf("Free sector count = %d\r\n", free_sector);

    printf("Free space(KB) = %d\r\n", free_space);

    printf("Get FAT disk info OK\r\n");
}

void fatTest_ScanDir(const TCHAR* PathName) {
    DIR dir;
    FILINFO dir_info;
    FRESULT res = f_opendir(&dir, PathName);
    if (res != FR_OK) {
        f_closedir(&dir);
        return;
    }

    printf("All entries in dir %s\r\n", PathName);
    while (1) {
        res = f_readdir(&dir, &dir_info);
        if (res != FR_OK || dir_info.fname[0] == 0) {
            break;
        }
        if (dir_info.fattrib & AM_DIR) {
            printf("DIR   %s\r\n", dir_info.fname);
        } else {
            printf("FILE  %s\r\n", dir_info.fname);
        }
    }
    printf("Scan dir OK\r\n");
    f_closedir(&dir);
}

void fatTest_WriteTXTFile(TCHAR* filename, uint16_t year, uint8_t month, uint8_t day) {
    FIL file;
    FRESULT res = f_open(&file, filename, FA_CREATE_ALWAYS | FA_WRITE);
    if (res == FR_OK) {
        f_puts("Line1: Hello FatFS\n", &file);
        f_puts("Line2: UPC, Qingdao\n", &file);
        f_printf(&file, "Line3: Date=%04d-%02d-%02d\n", year, month, day);
    } else {
        printf("Write file error\r\n");
    }
    f_close(&file);
}

void fatTest_WriteBinFile(TCHAR* filename, uint32_t pointCount, uint32_t sampFreq) {
    FIL file;
    FRESULT res = f_open(&file, filename, FA_CREATE_ALWAYS | FA_WRITE);
    if (res == FR_OK) {
        f_puts("ADC1-IN5\n", &file);

        UINT bw = 0;
        f_write(&file, &pointCount, sizeof (uint32_t), &bw);
        f_write(&file, &sampFreq, sizeof (uint32_t), &bw);

        uint32_t value = 1000;
        for (uint16_t i = 0; i < pointCount; i++, value++) {
            f_write(&file, &value, sizeof (uint32_t), &bw);
        }
    }
    f_close(&file);
}

void fatTest_ReadTXTFile(TCHAR* filename) {
    printf("Reading TXT file: %s\r\n", filename);

    FIL file;
    FRESULT res = f_open(&file, filename, FA_READ);
    if (res == FR_OK) {
        uint8_t show_str[40];
        while (!f_eof(&file)) {
            f_gets(show_str, 40, &file);
            printf("%s\r\n", show_str);
        }
    } else if (res == FR_NO_FILE) {
        printf("%s does not exist\r\n", filename);
    } else {
        printf("f_open() error\r\n");
    }
    f_close(&file);
}

void fatTest_ReadBinFile(TCHAR* filename) {
    printf("Reading BIN file: %s\r\n", filename);
    FIL file;
    FRESULT res = f_open(&file, filename, FA_READ);
    if (res == FR_OK) {
        uint8_t show_str[40];
        f_gets(show_str, 40, &file);

        UINT bw = 0;
        uint32_t pointCount;
        uint32_t sampFreq;
        f_read(&file, &pointCount, sizeof (uint32_t), &bw);
        f_read(&file, &sampFreq, sizeof (uint32_t), &bw);
        uint32_t value[pointCount];
        for (uint16_t i = 0; i < pointCount; ++i) {
            f_read(&file, &value[i], sizeof (uint32_t), &bw);
        }

        printf("%s\r\n", show_str);

        printf("Point count: %d\r\n", pointCount);

        printf("Sampling frequency: %d\r\n", sampFreq);

        printf("value[5] = %d\r\n", value[5]);

        printf("value[16] = %d\r\n", value[16]);
    } else if (res == FR_NO_FILE) {
        printf("%s does not exist\r\n", filename);
    } else {
        printf("f_open() error\r\n");
    }
    f_close(&file);
}

void fatTest_GetFileInfo(TCHAR* filename) {
    printf("File info of: %s\r\n", filename);

    FILINFO file_info;
    FRESULT res = f_stat(filename, &file_info);
    if (res == FR_OK) {
        printf("File size(bytes)= %d\r\n", file_info.fsize);

        printf("File attribute = 0x%X\r\n", file_info.fattrib);

        printf("File name = %s\r\n", file_info.fname);

        RTC_DateTypeDef sDate;
        RTC_TimeTypeDef sTime;

        sDate.Date = file_info.fdate & 0x001F;
        sDate.Month = (file_info.fdate & 0x01E0) >> 5;
        sDate.Year = 1980 + ((file_info.fdate & 0xFE00) >> 9) - 2000;

        sTime.Hours = (file_info.ftime & 0xF800) >> 11;
        sTime.Minutes = (file_info.ftime & 0x07E0) >> 5;
        sTime.Seconds = (file_info.ftime & 0x001F) << 1;


        printf("File Date = 20%02d-%02d-%02d\r\n", sDate.Year, sDate.Month, sDate.Date);

        printf("File Time = %02d:%02d:%02d\r\n", sTime.Hours, sTime.Minutes, sTime.Seconds);
    } else if (res == FR_NO_FILE) {
        printf("%s does not exist\r\n", filename);
    } else {
        printf("f_stat() error\r\n");
    }
}

DWORD fat_GetFatTimeFromRTC() {
    RTC_TimeTypeDef sTime;
    RTC_DateTypeDef sDate;
    if (HAL_RTC_GetTime(&hrtc, &sTime, RTC_FORMAT_BIN) == HAL_OK) {
        HAL_RTC_GetDate(&hrtc, &sDate, RTC_FORMAT_BIN);
        WORD date = ((2000 + sDate.Year - 1980) << 9) | (sDate.Month << 5) | sDate.Date;
        WORD time = (sTime.Hours << 11) | (sTime.Minutes << 5) | (sTime.Seconds >> 1);

        DWORD fatTime = ((DWORD)date << 16) | time;
        return fatTime;
    } else {
        return 0;
    }
}

EntryData_t dataEntries[MAX_ENTRIES];
int numEntries = 0;

void read_and_parse_data(const char* filename) {
    FATFS fs;
    FIL fil;
    FRESULT fr;
    char lineBuffer[MAX_LINE_LEN];
    char *token;
    char *saveptr;

    numEntries = 0;
    fr = f_mount(&fs, "0:", 1);
    if (fr != FR_OK) {
        printf("文件系统挂载失败 (%d)\r\n", fr);
        return;
    }
    fr = f_open(&fil, filename, FA_READ);
    if (fr != FR_OK) {
        printf("文件打开失败 (%d)\r\n", fr);
        f_mount(0, "0:", 0);
        return;
    }
    while (f_gets(lineBuffer, sizeof(lineBuffer), &fil) && numEntries < MAX_ENTRIES) {
        size_t len = strlen(lineBuffer);
        if (len > 0 && (lineBuffer[len-1] == '\n' || lineBuffer[len-1] == '\r')) {
            lineBuffer[len-1] = '\0';
            if (len > 1 && (lineBuffer[len-2] == '\n' || lineBuffer[len-2] == '\r')) {
                lineBuffer[len-2] = '\0';
            }
        }
        if (strlen(lineBuffer) == 0) {
            continue;
        }
        token = strtok_r(lineBuffer, ",", &saveptr);
        if (token != NULL) {
            strncpy(dataEntries[numEntries].name, token, MAX_NAME_LEN - 1);
            dataEntries[numEntries].name[MAX_NAME_LEN - 1] = '\0';
            token = strtok_r(NULL, ",", &saveptr);
            if (token != NULL) {
                strncpy(dataEntries[numEntries].code, token, MAX_CODE_LEN - 1);
                dataEntries[numEntries].code[MAX_CODE_LEN - 1] = '\0';
            } else {
                dataEntries[numEntries].code[0] = '\0';
            }
            numEntries++;
        }
    }

    f_close(&fil);

    f_mount(0, "0:", 0);

    printf("成功读取并解析了 %d 条数据:\r\n", numEntries);
    for (int i = 0; i < numEntries; i++) {
        printf("Entry %d: Name=%s, Code=%s\r\n", i, dataEntries[i].name, dataEntries[i].code);
    }

    // Update LVGL table with read data
    // Assuming row 0 is for headers, so data starts from row 1
    for (int i = 0; i < numEntries; i++) {
        // Ensure we don't go beyond the table's capacity or MAX_ENTRIES
        if (i + 1 < lv_table_get_row_cnt(guider_ui.screen_table_1)) {
            lv_table_set_cell_value(guider_ui.screen_table_1, i + 1, 0, dataEntries[i].name);
            // lv_table_set_cell_value(guider_ui.screen_table_1, i + 1, 1, dataEntries[i].code);
        } else {
            printf("Warning: Not enough rows in LVGL table to display all data entries.\r\n");
            break; // Stop if no more rows are available in the table
        }
    }
}