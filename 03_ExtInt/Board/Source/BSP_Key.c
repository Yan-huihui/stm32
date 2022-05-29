/***********************************************************************************
 Key 驱动  huo  2016-12-23  10:00
 Key IO：Key1-PF9 Key2-PG13 按下返回低电平
************************************************************************************/
#include "BSP_Key.h"					//Key驱动头文件

/*
*********************************************************************************************************
*	函 数 名: BSP_Key_Init
*	功能说明: 板载Key初始化函数
*	形    参: 无
*	返 回 值: 无
*********************************************************************************************************
*/
void BSP_Key_Init(void)
{
	BSP_Key_GPIO_Init();
}

/*
*********************************************************************************************************
*	函 数 名: BSP_Key_GPIO_Init
*	功能说明: 板载Key GPIO初始化函数
*	形    参: 无
*	返 回 值: 无
*********************************************************************************************************
*/
static void BSP_Key_GPIO_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	RCC_APB2PeriphClockCmd(RCC_KEYALL, ENABLE);				//使能GPIOF时钟 
	
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;			//推挽输出
	GPIO_InitStructure.GPIO_Pin = GPIO_PIN_KEY1;			//Key1引脚
	GPIO_Init(GPIO_PORT_KEY1, &GPIO_InitStructure);
	GPIO_InitStructure.GPIO_Pin = GPIO_PIN_KEY2;			//Key2引脚
	GPIO_Init(GPIO_PORT_KEY2, &GPIO_InitStructure);
}

/*
*********************************************************************************************************
*	函 数 名: BSP_Key_Scan
*	功能说明: 板载Key扫描功能函数
*	形    参: KeyCount : 按键序号
*	返 回 值: KeyValue : 按键状态
*********************************************************************************************************
*/
uint8_t BSP_Key_Scan(KeyCount_TypeDef KeyCount)
{
	uint8_t KeyState=0x00;
	
	if (KeyCount & Key1)
		KeyState |= GPIO_ReadInputDataBit(GPIO_PORT_KEY1, GPIO_PIN_KEY1)<<(Key1-1);
	if (KeyCount & Key2)
		KeyState |= GPIO_ReadInputDataBit(GPIO_PORT_KEY2, GPIO_PIN_KEY2)<<(Key2-1);
	if (KeyCount & Key3)
		;
	if (KeyCount & Key4)
		;
	
	return KeyState;
}

