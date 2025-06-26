/**
  ******************************************************************************
  * @file           : file_opera.h
  * @author         : Kevin_WWW
  * @brief          : None
  * @attention      : None
  * @date           : 2024/4/25
  ******************************************************************************
  */
#ifndef DEMO12_1FLASHFAT_FILE_OPERA_H
#define DEMO12_1FLASHFAT_FILE_OPERA_H

#include "ff.h"
#include "lcd.h"
#include <stdio.h>
#include "main.h"

#define MAX_LINE_LEN 128
#define MAX_NAME_LEN 64
#define MAX_CODE_LEN 64
#define MAX_ENTRIES  10

typedef struct {
  char name[MAX_NAME_LEN];
  char code[MAX_CODE_LEN];
} EntryData_t;

extern EntryData_t dataEntries[MAX_ENTRIES];
extern int numEntries;

void fatTest_GetDiskInfo();
void fatTest_ScanDir(const TCHAR* PathName);
void fatTest_WriteTXTFile(TCHAR* filename, uint16_t year, uint8_t month, uint8_t day);
void fatTest_WriteBinFile(TCHAR* filename, uint32_t pointCount, uint32_t sampFreq);
void fatTest_ReadTXTFile(TCHAR* filename);
void fatTest_ReadBinFile(TCHAR* filename);
void fatTest_GetFileInfo(TCHAR* filename);
void read_and_parse_data(const char* filename);
char* fatTest_ReadTXTFile_ret_char(const TCHAR* filename);

DWORD fat_GetFatTimeFromRTC();

#endif //DEMO12_1FLASHFAT_FILE_OPERA_H
