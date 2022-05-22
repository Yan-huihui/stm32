/***********************************************************************************
 Key 驱动  huo  2016-12-23  10:00
 Key IO：Key1-PF9 Key2-PG13 按下返回低电平
 Led IO：Led-PF11 低电平点亮
************************************************************************************/
#include "stm32f10x.h"		//STM32F10x头文件
#include "BSP_Led.h"			//Led头文件
#include "BSP_Key.h"			//Key驱动头文件

uint8_t KeyState=0xFF;

/* 不精确延时函数 */
void DelayCount(uint32_t Count)
{
	while(Count--);
}

int BreathLed(void)
{
	int i = 0;
	int period = 2000;
	
	while(1)
	{
		for(i = 0; i < period; ++i)
		{
			BSP_Led_On(Led1);
			DelayCount(i);
			BSP_Led_Off(Led1);
			DelayCount(period - i);
			
			KeyState = BSP_Key_Scan(KeyAll);	//按键扫描
			if(!(KeyState & Key2))
			{
				BSP_Led_Off(Led1);
				return 0;
			}
		}
		
		for(i = 0; i < period; ++i)
		{
			BSP_Led_On(Led1);
			DelayCount(period - i);
			BSP_Led_Off(Led1);
			DelayCount(i);
			
			KeyState = BSP_Key_Scan(KeyAll);	//按键扫描
			if(!(KeyState & Key2))
			{
				BSP_Led_Off(Led1);
				return 0;
			}
		}
	}
}

/* 主函数 */
int main(void)
{
	BSP_Led_Init();				//Led灯GPIO初始化
	BSP_Key_Init();				//Key初始化
	
	while (1)
	{
//		BSP_Led_On(Led1);
//		DelayCount(0x4FFFFF);
//		BSP_Led_Off(Led1);
//		DelayCount(0x4FFFFF);
		
//		BSP_Led_Toggle(Led1);
//		DelayCount(0x4FFFFF);
		
		KeyState = BSP_Key_Scan(KeyAll);	//案件扫描

//		if(!(KeyState & Key1))						//无优先级
//			BSP_Led_On(Led1);
//		if(!(KeyState & Key2))
//			BSP_Led_Off(Led1);

		if(!(KeyState & Key1))						//Key1 优先级高于 Key2
			BreathLed();
		else if(!(KeyState & Key2))
			BSP_Led_Off(Led1);
	}
}

