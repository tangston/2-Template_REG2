#ifndef __STM32F10X_GPIO_H
#define __STM32F10X_GPIO_H

#include "stm32f10x.h"

/*  Ŀǰǳ�Ե�����Ǵ�����ƺͻ���ϻ������ģ������Ϲ۲�ע�͵Ĺ��ɣ�0����TTL�͵�ƽ��1����TTL�ߵ�ƽ
**  resoning: ��Ϊÿ��GPIO�Ĵӵ������Է�װ������������޹أ����������ó������ǹ�ͨ�ĵط�
**  ��Ҫ˼�룺���븴��˼��
*/
#define GPIO_Pin_0    ((uint16_t)0x0001)  /*!< ѡ��Pin0 */    //(00000000 00000001)binary
#define GPIO_Pin_1    ((uint16_t)0x0002)  /*!< ѡ��Pin1 */    //(00000000 00000010)binary
#define GPIO_Pin_2    ((uint16_t)0x0004)  /*!< ѡ��Pin2 */    //(00000000 00000100)binary
#define GPIO_Pin_3    ((uint16_t)0x0008)  /*!< ѡ��Pin3 */    //(00000000 00001000)binary
#define GPIO_Pin_4    ((uint16_t)0x0010)  /*!< ѡ��Pin4 */    //(00000000 00010000)binary
#define GPIO_Pin_5    ((uint16_t)0x0020)  /*!< ѡ��Pin5 */    //(00000000 00100000)binary
#define GPIO_Pin_6    ((uint16_t)0x0040)  /*!< ѡ��Pin6 */    //(00000000 01000000)binary
#define GPIO_Pin_7    ((uint16_t)0x0080)  /*!< ѡ��Pin7 */    //(00000000 10000000)binary
#define GPIO_Pin_8    ((uint16_t)0x0100)  /*!< ѡ��Pin8 */    //(00000001 00000000)binary
#define GPIO_Pin_9    ((uint16_t)0x0200)  /*!< ѡ��Pin9 */    //(00000010 00000000)binary
#define GPIO_Pin_10   ((uint16_t)0x0400)  /*!< ѡ��Pin10 */   //(00000100 00000000)binary
#define GPIO_Pin_11   ((uint16_t)0x0800)  /*!< ѡ��Pin11 */   //(00001000 00000000)binary
#define GPIO_Pin_12   ((uint16_t)0x1000)  /*!< ѡ��Pin12 */   //(00010000 00000000)binary
#define GPIO_Pin_13   ((uint16_t)0x2000)  /*!< ѡ��Pin13 */   //(00100000 00000000)binary
#define GPIO_Pin_14   ((uint16_t)0x4000)  /*!< ѡ��Pin14 */   //(01000000 00000000)binary
#define GPIO_Pin_15   ((uint16_t)0x8000)  /*!< ѡ��Pin15 */   //(10000000 00000000)binary
#define GPIO_Pin_All  ((uint16_t)0xFFFF)  /*!< ѡ��ȫ������*/ //(11111111 11111111)binary


/*ע�͵ĸ߼�װ�ư汾*/
#if 0
typedef enum
{ 
  Pin_0=GPIO_Pin_8, Pin_1=GPIO_Pin_1, Pin_2=GPIO_Pin_2,  Pin_3=GPIO_Pin_3,  Pin_4=GPIO_Pin_4,  Pin_5=GPIO_Pin_6,  Pin_6=GPIO_Pin_6,Pin_7=GPIO_Pin_7,
  Pin_8=GPIO_Pin_8, Pin_9=GPIO_Pin_9, Pin_10=GPIO_Pin_10, Pin_11=GPIO_Pin_11, Pin_12=GPIO_Pin_12, Pin_13=GPIO_Pin_13, Pin_14=GPIO_Pin_14, Pin_15=GPIO_Pin_15     
    
}GPIO_Pin_x;
#endif


/*  ���²��ֲο�STM32�ٷ��ֲ� 8.1+8.2��
**  ͬѧ�������Ƕ��ʽ�����Ͷ࿴�ٷ��ĵ���������ʧ��Ѽ������
*/
typedef enum
{ 
  GPIO_Speed_10MHz = 1,                             // 10MHZ        (01)b
  GPIO_Speed_2MHz,                                  // 2MHZ         (10)b
  GPIO_Speed_50MHz                                  // 50MHZ        (11)b
}GPIO_Mode_TypeDef;

typedef enum
{ GPIO_IOtype_Input = 0x0,                            // ģ������     (0000 0000)b
  GPIO_IOtype_Input_Floating = 0x04,                  // ��������     (0000 0100)b
  GPIO_IOtype_Input_Pulldown = 0x28,                  // ��������     (0010 1000)b
  GPIO_IOtype_Input_Pullup = 0x48,                    // ��������     (0100 1000)b
  
  GPIO_IOtype_Output_OpenDrain = 0x14,                // ��©���     (0001 0100)b
  GPIO_IOtype_Output_PushPull = 0x10,                 // �������     (0001 0000)b
  GPIO_IOtype_AlternateFunction_OpenDrain = 0x1C,     // ���ÿ�©��� (0001 1100)b
  GPIO_IOtype_AlternateFunction_PushPull = 0x18       // ����������� (0001 1000)b
}GPIO_Configuration_TypeDef;

typedef struct
{
	uint16_t GPIO_Pin;        //ָ���ĸ�����
	uint16_t GPIO_IOtype;     //ָ�����������������
	uint16_t GPIO_Speed;      //ָ������Ƶ��
}GPIO_InitTypeDef;




void GPIO_SetBits(GPIO_TypeDef *  GPIOx,uint16_t  GPIO_Pin);
void GPIO_ResetBits(GPIO_TypeDef *  GPIOx,uint16_t  GPIO_Pin);
void GPIO_Init(GPIO_TypeDef* GPIOx, GPIO_InitTypeDef* GPIO_InitStruct);
#endif  /*__STM32F10X_GPIO_H*/

