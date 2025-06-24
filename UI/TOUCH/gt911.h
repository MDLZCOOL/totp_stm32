#pragma once

#include "main.h"

#ifndef INC_GT9XX_H_
#define INC_GT9XX_H_


// ����IC���ź��ж�
#define GTP_RST_GPIO_PORT TP_RESET_GPIO_Port
#define GTP_RST_GPIO_PIN TP_RESET_Pin
#define GTP_INT_GPIO_PORT TP_INT_GPIO_Port
#define GTP_INT_GPIO_PIN TP_INT_Pin
//#define GTP_INT_EXTI_IRQ EXTI4_IRQn //

/*I2C���*/
#define		GT911_I2C			hi2c3

// ����IC�豸��ַ
#define GT911_DIV_W 0x28
#define GT911_DIV_R 0x29

//GT911 ���ּĴ�������
#define GT_CTRL_REG 	0X8040   	//GT911���ƼĴ���
#define GT_CFGS_REG 	0X8047   	//GT911������ʼ��ַ�Ĵ���
#define GT_CHECK_REG 	0X80FF   	//GT911У��ͼĴ���
#define GT_PID_REG 		0X8140   	//GT911��ƷID�Ĵ���

#define GT_GSTID_REG 	0X814E   	//GT911��ǰ��⵽�Ĵ������,��7λ�Ǵ�����־λ����4λ�Ǵ�����������

#define GT_TPD_Sta		0X8150		//��������ʼ���ݵ�ַ
#define GT_TP1_REG 		0X8150  	//��һ�����������ݵ�ַ
#define GT_TP2_REG 		0X8158		//�ڶ������������ݵ�ַ
#define GT_TP3_REG 		0X8160		//���������������ݵ�ַ
#define GT_TP4_REG 		0X8168		//���ĸ����������ݵ�ַ
#define GT_TP5_REG 		0X8170		//��������������ݵ�ַ


#define GT_TOUCH_MAX	5			//����gt911�����ͬʱ��ȡ5�������������

typedef enum {
    X_L = 0,
    X_H = 1,
    Y_L = 2,
    Y_H = 3,
    S_L = 4,
    S_H = 5
} Data_XYS_P; //����X��Y��������С����ƫ����

typedef enum {
    TOUCH__NO = 0x00, //û�д���
    TOUCH_ING = 0x80 //������
} TOUCH_STATE_enum; //����״̬

typedef struct {
    uint16_t X_Point; //X����
    uint16_t Y_Point; //Y����
    uint16_t S_Point; //�������С
} XY_Coordinate; //����������


/*�����ṹ��*/
typedef struct {
    uint8_t Touch_State; //����״̬
    uint8_t Touch_Number; //��������
    XY_Coordinate Touch_XY[GT_TOUCH_MAX]; //������x���꣬����gt911���5���������
} Touch_Struct; //������Ϣ�ṹ��

/*�ⲿ������*/
extern Touch_Struct User_Touch;


/*�ⲿ������*/
void GTP_Init(void);

void GTXXXX_Scanf(void);

void GTP911_Test(void);


#endif /* INC_GT9XX_H_ */
