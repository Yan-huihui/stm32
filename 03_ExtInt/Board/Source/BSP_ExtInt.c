/***********************************************************************************
 ExtInt 驱动  huo  2016-12-23  10:15
 KEY IO：KEY1-PF9 KEY2-PG13 按下返回低电平
************************************************************************************/
#include "BSP_ExtInt.h"					//ExtInt驱动头文件

int BreathLedstate = 0;

/* 不精确延时函数 */
static void BSP_ExtInt_Delay(uint32_t Count)
{
	while(Count--);
}

/*
*********************************************************************************************************
*	函 数 名: BSP_ExtInt_Init
*	功能说明: 板载ExtInt初始化函数
*	形    参: 无
*	返 回 值: 无
*********************************************************************************************************
*/
void BSP_ExtInt_Init(void)
{
//	BSP_Key_GPIO_Init();
	BSP_ExtInt_EXTI_Init();
	BSP_ExtInt_NVIC_Init();
}

/*
*********************************************************************************************************
*	函 数 名: BSP_ExtInt_EXTI_Init
*	功能说明: 板载ExtInt EXTI初始化函数
*	形    参: 无
*	返 回 值: 无
*********************************************************************************************************
*/
static void BSP_ExtInt_EXTI_Init(void)
{
 	EXTI_InitTypeDef EXTI_InitStructure;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO,ENABLE);	//使能复用功能时钟

	//GPIOF.9 中断线以及中断初始化配置   下降沿触发
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOF,GPIO_PinSource9);
	EXTI_InitStructure.EXTI_Line=EXTI_Line9;	//KEY1
	EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;	
	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling;
	EXTI_InitStructure.EXTI_LineCmd = ENABLE;
	EXTI_Init(&EXTI_InitStructure);	 	//根据EXTI_InitStruct中指定的参数初始化外设EXTI寄存器

	//GPIOG.13	  中断线以及中断初始化配置 下降沿触发 //KEY2
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOG,GPIO_PinSource13);
	EXTI_InitStructure.EXTI_Line=EXTI_Line13;
	EXTI_Init(&EXTI_InitStructure);	  	//根据EXTI_InitStruct中指定的参数初始化外设EXTI寄存器
}

/*
*********************************************************************************************************
*	函 数 名: BSP_ExtInt_NVIC_Init
*	功能说明: 板载ExtInt NVIC初始化函数
*	形    参: 无
*	返 回 值: 无
*********************************************************************************************************
*/
static void BSP_ExtInt_NVIC_Init(void)
{
 	NVIC_InitTypeDef NVIC_InitStructure;

	NVIC_InitStructure.NVIC_IRQChannel = EXTI9_5_IRQn;			//使能按键KEY1所在的外部中断通道
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x02;	//抢占优先级2， 
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x03;					//子优先级3
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;								//使能外部中断通道
	NVIC_Init(&NVIC_InitStructure); 

	NVIC_InitStructure.NVIC_IRQChannel = EXTI15_10_IRQn;			//使能按键KEY2所在的外部中断通道
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x02;	//抢占优先级2， 
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x02;					//子优先级2
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;								//使能外部中断通道
	NVIC_Init(&NVIC_InitStructure);
}

/*
*********************************************************************************************************
*	函 数 名: BSP_ExtInt_ISR1
*	功能说明: 板载ExtInt 中断服务功能函数
*	形    参: 无
*	返 回 值: 无
*********************************************************************************************************
*/
void BSP_ExtInt_ISR1(void)
{
	BSP_ExtInt_Delay(0x19999);//消抖
	if(!(BSP_Key_Scan(Key1) & Key1))	 	 //KEY1按键
	{	
		BreathLedstate = 1;
//		BSP_Led_On(Led1);	
	}
	EXTI_ClearITPendingBit(EXTI_Line9); //清除LINE9上的中断标志位  
}

/*
*********************************************************************************************************
*	函 数 名: BSP_ExtInt_ISR2
*	功能说明: 板载ExtInt 中断服务功能函数
*	形    参: 无
*	返 回 值: 无
*********************************************************************************************************
*/
void BSP_ExtInt_ISR2(void)
{
	BSP_ExtInt_Delay(0x19999);//消抖
	if(!(BSP_Key_Scan(Key2) & Key2))	  //按键KEY2
	{
		BreathLedstate = 0;
		BSP_Led_Off(Led1);
	}		 
	EXTI_ClearITPendingBit(EXTI_Line13);  //清除LINE13上的中断标志位  
}
