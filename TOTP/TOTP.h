#ifndef TOTP_H
#define TOTP_H

#include <stdint.h>
#include <time.h> // For struct tm

// 定义 TOTP_Generator 结构体
typedef struct {
    uint8_t* hmacKey;
    uint8_t keyLength;
    uint32_t timeStep;
    uint8_t timeZoneOffset; // 保持与您原始代码一致的 uint8_t 类型
} TOTP_Generator;

// --- 函数声明 ---

/**
 * @brief 初始化一个 TOTP 生成器实例。
 * @param generator 指向要初始化的 TOTP_Generator 实例的指针。
 * @param hmacKey 指向 HMAC 密钥的指针。
 * @param keyLength 密钥的长度。
 * @param timeStep TOTP 的时间步长（秒），通常为 30 或 60。
 */
void initTOTP(TOTP_Generator* generator, uint8_t* hmacKey, uint8_t keyLength, uint32_t timeStep);

/**
 * @brief 为指定的 TOTP 生成器实例设置时区偏移。
 * @param generator 指向 TOTP_Generator 实例的指针。
 * @param timezone 时区偏移量（小时）。注意：此函数保留了原始代码中 uint8_t 类型，通常表示正偏移。
 */
void setTOTPTimezone(TOTP_Generator* generator, uint8_t timezone);

/**
 * @brief 将 struct tm 转换为 Unix 时间戳（考虑时区和 NTP 纪元偏移）。
 * 此函数逻辑与您原始代码中 TimeStruct2Timestamp 函数的逻辑完全一致。
 * @param generator 指向 TOTP_Generator 实例的指针，用于获取时区信息。
 * @param time 要转换的 struct tm 结构体。
 * @return 对应的 Unix 时间戳（从 1970/01/01 00:00:00 UTC 开始的秒数）。
 */
uint32_t TOTP_TimeStruct2Timestamp(TOTP_Generator* generator, struct tm time);

/**
 * @brief 从 Unix 时间戳为指定的 TOTP 生成器生成 TOTP 代码。
 * @param generator 指向 TOTP_Generator 实例的指针。
 * @param timeStamp Unix 时间戳。
 * @return 生成的 6 位 TOTP 代码。
 */
uint32_t getTOTPCodeFromTimestamp(TOTP_Generator* generator, uint32_t timeStamp);

/**
 * @brief 从 struct tm 为指定的 TOTP 生成器生成 TOTP 代码。
 * @param generator 指向 TOTP_Generator 实例的指针。
 * @param time struct tm 结构体。
 * @return 生成的 6 位 TOTP 代码。
 */
uint32_t getTOTPCodeFromTimeStruct(TOTP_Generator* generator, struct tm time);

/**
 * @brief 从步数（时间戳 / 时间步长）为指定的 TOTP 生成器生成 TOTP 代码。
 * @param generator 指向 TOTP_Generator 实例的指针。
 * @param steps 时间步数。
 * @return 生成的 6 位 TOTP 代码。
 */
uint32_t getTOTPCodeFromSteps(TOTP_Generator* generator, uint32_t steps);

#endif // TOTP_H