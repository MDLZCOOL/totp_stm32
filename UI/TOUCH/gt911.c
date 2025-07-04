/*
 * gt9xx.c
 *
 *  Created on: Mar 20, 2024
 *      Author: ZuoenDeng
 */
#include "gt911.h"
#include <stdio.h>

#include "SEGGER_RTT.h"

/*创建触摸结构体*/
Touch_Struct User_Touch;

// GT911驱动配置，默认使用第一份配置文件，如果屏幕异常，可尝试使用第二份
#if  0
const uint8_t CTP_CFG_GT911[] = {
    0x41, 0x20, 0x03, 0xE0, 0x01, 0x05, 0x3D, 0x00, 0x01, 0x08,
    0x1E, 0x05, 0x3C, 0x3C, 0x03, 0x05, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x1A, 0x1C, 0x1E, 0x14, 0x8A, 0x2A, 0x0C,
    0x2A, 0x28, 0xEB, 0x04, 0x00, 0x00, 0x01, 0x61, 0x03, 0x2C,
    0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x14, 0x3C, 0x94, 0xC5, 0x02, 0x08, 0x00, 0x00, 0x04,
    0xB7, 0x16, 0x00, 0x9F, 0x1B, 0x00, 0x8B, 0x22, 0x00, 0x7B,
    0x2B, 0x00, 0x70, 0x36, 0x00, 0x70, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x18, 0x16, 0x14, 0x12, 0x10, 0x0E, 0x0C, 0x0A,
    0x08, 0x06, 0x04, 0x02, 0xFF, 0xFF, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x24, 0x22, 0x21, 0x20, 0x1F, 0x1E, 0x1D, 0x1C,
    0x18, 0x16, 0x13, 0x12, 0x10, 0x0F, 0x0A, 0x08, 0x06, 0x04,
    0x02, 0x00, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x0A, 0x00
};
#else
const uint8_t CTP_CFG_GT911[] =  {
  0x00,0x20,0x03,0xE0,0x01,0x05,0x0D,0x00,0x01,0x08,
  0x28,0x0F,0x50,0x32,0x03,0x05,0x00,0x00,0x00,0x00,
  0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x8A,0x2A,0x0C,
  0x45,0x47,0x0C,0x08,0x00,0x00,0x00,0x02,0x02,0x2D,
  0x00,0x00,0x00,0x00,0x00,0x03,0x64,0x32,0x00,0x00,
  0x00,0x28,0x64,0x94,0xC5,0x02,0x07,0x00,0x00,0x04,
  0x9C,0x2C,0x00,0x8F,0x34,0x00,0x84,0x3F,0x00,0x7C,
  0x4C,0x00,0x77,0x5B,0x00,0x77,0x00,0x00,0x00,0x00,
  0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
  0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
  0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
  0x00,0x00,0x18,0x16,0x14,0x12,0x10,0x0E,0x0C,0x0A,
  0x08,0x06,0x04,0x02,0xFF,0xFF,0x00,0x00,0x00,0x00,
  0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
  0x00,0x00,0x16,0x18,0x1C,0x1D,0x1E,0x1F,0x20,0x21,
  0x22,0x24,0x13,0x12,0x10,0x0F,0x0A,0x08,0x06,0x04,
  0x02,0x00,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0x00,0x00,
  0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
  0x00,0x00,0x00,0x00,0x24,0x01
};
#endif

void GTXXXX_WriteReg(uint16_t _usRegAddr, uint8_t *_pRegBuf, uint8_t _ucLen) {
    HAL_I2C_Mem_Write(&GT911_I2C, GT911_DIV_W, _usRegAddr, I2C_MEMADD_SIZE_16BIT, _pRegBuf, _ucLen, 0xff);
}

void GTXXXX_ReadReg(uint16_t _usRegAddr, uint8_t *_pRegBuf, uint8_t _ucLen) {
    HAL_I2C_Mem_Read(&GT911_I2C, GT911_DIV_R, _usRegAddr, I2C_MEMADD_SIZE_16BIT, _pRegBuf, _ucLen, 0xff);
}

void GTP_Init(void) {
    /*初始化gt9157的设备地址为0x28/0x29*/

    HAL_GPIO_WritePin(GTP_INT_GPIO_PORT,GTP_INT_GPIO_PIN, GPIO_PIN_RESET);
    HAL_GPIO_WritePin(GTP_RST_GPIO_PORT,GTP_RST_GPIO_PIN, GPIO_PIN_RESET);
    HAL_Delay(100);
    /*复位为低电平，为初始化做准备*/
    HAL_GPIO_WritePin(GTP_INT_GPIO_PORT,GTP_INT_GPIO_PIN, GPIO_PIN_SET);
    HAL_Delay(10);

    /*拉高一段时间，进行初始化*/
    HAL_GPIO_WritePin(GTP_RST_GPIO_PORT,GTP_RST_GPIO_PIN, GPIO_PIN_SET);
    HAL_Delay(10);

    /*把INT引脚设置为浮空输入模式，以便接收触摸中断信号*/
    GPIO_InitTypeDef GPIO_InitStructure;
    GPIO_InitStructure.Pin = GTP_INT_GPIO_PIN;
    GPIO_InitStructure.Mode = GPIO_MODE_INPUT;
    GPIO_InitStructure.Speed = GPIO_SPEED_HIGH;
    GPIO_InitStructure.Pull = GPIO_NOPULL;
    HAL_GPIO_Init(GTP_INT_GPIO_PORT, &GPIO_InitStructure);
    //   HAL_NVIC_SetPriority(GTP_INT_EXTI_IRQ, 1, 1);/* 配置中断优先级 */
    //   HAL_NVIC_EnableIRQ(GTP_INT_EXTI_IRQ);/* 使能中断 */

    // 读取ID
    HAL_Delay(100);
    uint8_t GTP_ID[4];
    GTXXXX_ReadReg(GT_PID_REG, GTP_ID, 4);
    SEGGER_RTT_printf("GTP_ID:%s\n", GTP_ID);

    // 写入配置表
    GTXXXX_WriteReg(GT_CFGS_REG, (uint8_t *) CTP_CFG_GT911, sizeof(CTP_CFG_GT911));
    HAL_Delay(100);

    // 转换为软复位模式
    uint8_t _temp = 2; //中间变量
    GTXXXX_WriteReg(GT_CTRL_REG, &_temp, 1);
    HAL_Delay(100);

    // 转换为读取坐标模式
    _temp = 0; //中间变量
    GTXXXX_WriteReg(GT_CTRL_REG, &_temp, 1);
}

/*
	功能：gt911触摸扫描，判断当前是否被触摸
	参数1：
*/
void GTXXXX_Scanf(void) {
    uint8_t _temp; //中间变量

    GTXXXX_ReadReg(GT_GSTID_REG, &_temp, 1); //读取状态寄存器

    // 记录触摸状态
    User_Touch.Touch_State = _temp;
    User_Touch.Touch_Number = (User_Touch.Touch_State & 0x0f); //获取触摸点数
    User_Touch.Touch_State = (User_Touch.Touch_State & 0x80); //触摸状态

    //判断是否有触摸数据
    switch (User_Touch.Touch_State) {
        case TOUCH__NO: //没有数据
            break;
        case TOUCH_ING: //触摸中~后，有数据，并读出数据
            for (uint8_t i = 0; i < User_Touch.Touch_Number; i++) {
                GTXXXX_ReadReg((GT_TPD_Sta + i * 8 + X_L), &_temp, 1); //读出触摸x坐标的低8位
                User_Touch.Touch_XY[i].X_Point = _temp;
                GTXXXX_ReadReg((GT_TPD_Sta + i * 8 + X_H), &_temp, 1); //读出触摸x坐标的高8位
                User_Touch.Touch_XY[i].X_Point |= (_temp << 8);

                GTXXXX_ReadReg((GT_TPD_Sta + i * 8 + Y_L), &_temp, 1); //读出触摸y坐标的低8位
                User_Touch.Touch_XY[i].Y_Point = _temp;
                GTXXXX_ReadReg((GT_TPD_Sta + i * 8 + Y_H), &_temp, 1); //读出触摸y坐标的高8位
                User_Touch.Touch_XY[i].Y_Point |= (_temp << 8);

                GTXXXX_ReadReg((GT_TPD_Sta + i * 8 + S_L), &_temp, 1); //读出触摸大小数据的低8位
                User_Touch.Touch_XY[i].S_Point = _temp;
                GTXXXX_ReadReg((GT_TPD_Sta + i * 8 + S_H), &_temp, 1); //读出触摸大小数据的高8位
                User_Touch.Touch_XY[i].S_Point |= (_temp << 8);
            }

            _temp = 0;
            GTXXXX_WriteReg(GT_GSTID_REG, &_temp, 1); //清除数据标志位
            break;
    }
}

void GTP911_Test(void) {
    GTXXXX_Scanf(); //不断扫描
    if (User_Touch.Touch_State == 0x80) {
        for (uint8_t i = 0; i < User_Touch.Touch_Number; i++) {
            SEGGER_RTT_printf(0, "X : %d  ", User_Touch.Touch_XY[i].X_Point);
            SEGGER_RTT_printf(0, "Y : %d  ", User_Touch.Touch_XY[i].Y_Point);
            SEGGER_RTT_printf(0, "S : %d\r\n\r\n", User_Touch.Touch_XY[i].S_Point);
        }
        User_Touch.Touch_State = 0;
        User_Touch.Touch_Number = 0;
    }
}
