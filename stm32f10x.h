#ifndef __STM32F10X_H
#define __STM32F10X_H

// 用来存放STM32寄存器映射的代码

/* 外设  perirhral，计算机的外围设备的意思，这里的地址命名方式都是 基地址+偏移量（base+offset）的形式，便于理解
** 这里的地址参考STM32F10x官方中文手册2.3节
*/
#define PERIPH_BASE            ((unsigned int)0x40000000)
#define APB1PERIPH_BASE        PERIPH_BASE
#define APB2PERIPH_BASE       (PERIPH_BASE + 0x10000)
#define AHBPERIPH_BASE        (PERIPH_BASE + 0x20000)
#define RCC_BASE              (AHBPERIPH_BASE + 0x1000)
#define AFIO_BASE             (APB2PERIPH_BASE + 0x0000)	

#define GPIOA_BASE            (APB2PERIPH_BASE + 0x0800)
#define GPIOB_BASE            (APB2PERIPH_BASE + 0x0C00)
#define GPIOC_BASE            (APB2PERIPH_BASE + 0x1000)
#define GPIOD_BASE            (APB2PERIPH_BASE + 0x1400)
#define GPIOE_BASE            (APB2PERIPH_BASE + 0x1800)
#define GPIOF_BASE            (APB2PERIPH_BASE + 0x1C00)
#define GPIOG_BASE            (APB2PERIPH_BASE + 0x2000)


#define RCC_APB2ENR            *(unsigned int*)(RCC_BASE + 0x18)

	
typedef unsigned int      uint32_t;
typedef unsigned short    uint16_t;

typedef struct
{
	uint32_t CRL;
	uint32_t CRH;
	uint32_t IDR;
	uint32_t ODR;
	uint32_t BSRR;
	uint32_t BRR;
	uint32_t LCKR;
}GPIO_TypeDef;


typedef struct
{
	uint32_t CR;
	uint32_t CFGR;
	uint32_t CIR;
	uint32_t APB2RSTR;
	uint32_t APB1RSTR;
	uint32_t AHBENR;
	uint32_t APB2ENR;
	uint32_t APB1ENR;
	uint32_t BDCR;
	uint32_t CSR;
}RCC_TypeDef;


typedef struct
{
  uint32_t EVCR;
  uint32_t MAPR;
  uint32_t EXTICR[4];
} AFIO_TypeDef;

#define GPIOB   ((GPIO_TypeDef*)GPIOB_BASE)
#define GPIOE   ((GPIO_TypeDef*)GPIOE_BASE)
#define RCC     ((RCC_TypeDef*)RCC_BASE)
#define AFIO                ((AFIO_TypeDef *) AFIO_BASE)

#endif /* __STM32F10X_H */





















