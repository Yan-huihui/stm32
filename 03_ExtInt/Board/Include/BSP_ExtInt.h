#ifndef _BSP_EXTINT_H_
#define _BSP_EXTINT_H_
#include "stm32f10x.h"
#include "BSP_Key.h"					//Key驱动头文件
#include "BSP_Led.h"					//Led头文件

extern int BreathLedstate;

void BSP_ExtInt_Init(void);
static void BSP_ExtInt_EXTI_Init(void);
static void BSP_ExtInt_NVIC_Init(void);
void BSP_ExtInt_ISR1(void);
void BSP_ExtInt_ISR2(void);

#endif
