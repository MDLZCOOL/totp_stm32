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

char* fatTest_ReadTXTFile_ret_char(const TCHAR* filename) {
        FATFS fs;
        printf("Mounting filesystem...\r\n");
        FRESULT res = f_mount(&fs, "", 1);  // 挂载文件系统到默认驱动器（""），立即挂载（opt=1）

        if (res != FR_OK) {
            printf("f_mount failed: %d\r\n", res);
            return NULL;
        }

        printf("Reading TXT file: %s\r\n", filename);

        FIL file;
        res = f_open(&file, filename, FA_READ);
        if (res != FR_OK) {
            if (res == FR_NO_FILE)
                printf("%s does not exist\r\n", filename);
            else
                printf("f_open() error: %d\r\n", res);
            return NULL;
        }

        char* result = NULL;
        size_t total_len = 0;

        char line[128];  // 临时缓存一行
        while (f_gets(line, sizeof(line), &file)) {
            size_t line_len = strlen(line);
            char* new_buf = realloc(result, total_len + line_len + 1);  // +1 for null terminator
            if (!new_buf) {
                printf("Memory allocation failed\r\n");
                free(result);
                f_close(&file);
                return NULL;
            }
            result = new_buf;
            memcpy(result + total_len, line, line_len);
            total_len += line_len;
            result[total_len] = '\0';  // null 结尾
        }

        f_close(&file);
        f_mount(0, "0:", 0);
        return result;
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

DWORD fat_GetFatTimeFromRTC() {
        return 0;
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
        while (len > 0 && (lineBuffer[len - 1] == '\n' || lineBuffer[len - 1] == '\r')) {
            lineBuffer[--len] = '\0';
        }

        if (len == 0) {
            continue; // 跳过空行
        }

        token = strtok_r(lineBuffer, ",", &saveptr);
        if (token != NULL) {
            // 先清空 name 和 code
            memset(dataEntries[numEntries].name, 0, MAX_NAME_LEN);
            memset(dataEntries[numEntries].code, 0, MAX_CODE_LEN);

            // 拷贝 name 字段
            snprintf(dataEntries[numEntries].name, MAX_NAME_LEN, "%s", token);

            token = strtok_r(NULL, ",", &saveptr);
            if (token != NULL) {
                // 拷贝 code 字段
                snprintf(dataEntries[numEntries].code, MAX_CODE_LEN, "%s", token);
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