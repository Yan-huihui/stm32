/***********************************************************************************
 Led 驱动  huo  2016-12-23  09:45
 Led IO：Led-PF11 低电平点亮
************************************************************************************/
#include "stm32f10x.h"				//STM32F10x头文件
#include "BSP_Led.h"							//LED驱动头文件

/* 不精确延时函数 */                                                                                                                                
void DelayCount(uint32_t Count)
{
	while(Count--);
}                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                 
                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                        
/* 主函数 */
int main(void)
{
	int i;
	int period = 2000;
	BSP_Led_Init();				//LED灯GPIO初始化
		
	while (1)
	{
		for(i = 0; i < period; ++i)
		{
			BSP_Led_On(Led1);
			DelayCount(i);
			BSP_Led_Off(Led1);
			DelayCount(period - i);
		}
		
		for(i = 0; i < period; ++i)
		{
			BSP_Led_On(Led1);
			DelayCount(period - i);
			BSP_Led_Off(Led1);
			DelayCount(i);
		}
//		BSP_Led_Toggle(Led1);
//		DelayCount(0x4FFFFF);
	}
}

