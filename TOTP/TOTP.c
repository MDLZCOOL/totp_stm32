#include "TOTP.h"
#include "sha1.h" // 假设你的 SHA1 库头文件为 sha1.h

// HMAC-SHA1 库的外部函数声明
// 这些声明必须与你的 sha1.c 文件中的实际定义匹配。
// 特别注意 writeArray 的第二个参数类型，原始代码中是 uint8_t，这里保持一致。
extern void initHmac(const uint8_t* key, uint8_t keyLength);
extern void writeArray(uint8_t *buffer, uint8_t size);
extern uint8_t* resultHmac(void);

// --- 函数实现 ---

void initTOTP(TOTP_Generator* generator, uint8_t* hmacKey, uint8_t keyLength, uint32_t timeStep) {
    if (generator == NULL) {
        // 错误处理：生成器指针为空
        return;
    }
    generator->hmacKey = hmacKey;
    generator->keyLength = keyLength;
    generator->timeStep = timeStep;
    generator->timeZoneOffset = 0; // 默认时区为 0
}

void setTOTPTimezone(TOTP_Generator* generator, uint8_t timezone) {
    if (generator == NULL) {
        return;
    }
    generator->timeZoneOffset = timezone;
}

uint32_t TOTP_TimeStruct2Timestamp(TOTP_Generator* generator, struct tm time) {
    if (generator == NULL) {
        return 0; // 如果生成器为空，返回0或进行错误处理
    }
    // 完全保留您原始 TimeStruct2Timestamp 函数的逻辑。
    // mktime(&(time)) - (_timeZoneOffset * 3600) - 2208988800;
    // 这里的 mktime 通常会假设输入的 struct tm 是本地时间，并返回一个 Unix 时间戳（从 1970 UTC 开始）。
    // 然后再减去时区偏移量，以及从 1900年1月1日 到 1970年1月1日 的秒数 (2208988800)。
    // 这意味着最终得到的时间戳是基于 NTP 纪元 (1900-01-01 00:00:00 UTC) 且考虑了时区偏移的。
    return (uint32_t)mktime(&(time)) - (generator->timeZoneOffset * 3600) - 2208988800;
}

uint32_t getTOTPCodeFromTimestamp(TOTP_Generator* generator, uint32_t timeStamp) {
    if (generator == NULL) {
        return 0;
    }
    uint32_t steps = timeStamp / generator->timeStep;
    return getTOTPCodeFromSteps(generator, steps);
}

uint32_t getTOTPCodeFromTimeStruct(TOTP_Generator* generator, struct tm time) {
    if (generator == NULL) {
        return 0;
    }
    return getTOTPCodeFromTimestamp(generator, TOTP_TimeStruct2Timestamp(generator, time));
}

uint32_t getTOTPCodeFromSteps(TOTP_Generator* generator, uint32_t steps) {
    if (generator == NULL) {
        return 0;
    }

    // STEP 0: 将步数映射到 8 字节数组（计数器值）
    uint8_t _byteArray[8];
    _byteArray[0] = 0x00;
    _byteArray[1] = 0x00;
    _byteArray[2] = 0x00;
    _byteArray[3] = 0x00;
    _byteArray[4] = (uint8_t)((steps >> 24) & 0xFF);
    _byteArray[5] = (uint8_t)((steps >> 16) & 0xFF);
    _byteArray[6] = (uint8_t)((steps >> 8) & 0XFF);
    _byteArray[7] = (uint8_t)((steps & 0XFF));

    // STEP 1: 使用计数器和密钥获取 HMAC-SHA1 哈希
    initHmac(generator->hmacKey, generator->keyLength);
    writeArray(_byteArray, 8); // 这里的 8 保持 uint8_t 兼容
    uint8_t* _hash = resultHmac(); // 获取 20 字节的 SHA1 哈希值

    // STEP 2: 应用动态截断以获取 4 字节字符串
    uint32_t _truncatedHash = 0;
    // OTP 算法规范中偏移量是从哈希的最后一个字节的低 4 位获取
    uint8_t _offset = _hash[20 - 1] & 0xF;
    uint8_t j;
    for (j = 0; j < 4; ++j) {
        _truncatedHash <<= 8;
        _truncatedHash |= _hash[_offset + j];
    }

    // STEP 3: 计算 OTP 值
    // 移除最高位（MSB），因为 HOTP/TOTP 规范要求结果是非负数
    _truncatedHash &= 0x7FFFFFFF;
    // 取模 1,000,000 得到 6 位数字
    _truncatedHash %= 1000000;

    return _truncatedHash;
}