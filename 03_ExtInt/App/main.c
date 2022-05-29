/***********************************************************************************
 ExtInt 驱动  huo  2016-12-23  10:15
 外部引脚中断
 Key IO：Key1-PF9 Key2-PG13 按下返回低电平
 Led IO：Led-PF11 低电平点亮
************************************************************************************/
#include "stm32f10x.h"		//STM32F10x头文件
#include "BSP_Led.h"					//Led头文件
#include "BSP_Key.h"					//Key驱动头文件
#include "BSP_ExtInt.h"				//ExtInt驱动头文件

uint8_t KeyState=0xFF;
/* 不精确延时函数 */
void DelayCount(uint32_t Count)
{
	while(Count--);
}

/* 主函数 */
int main(void)
{
//	uint8_t KeyState=0xFF;
	
	BSP_Led_Init();				//LED灯GPIO初始化
	/* 只要工程用到中断，就需要设置中断分组；不使用默认分组方案  */
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2); //设置NVIC中断分组2:2位抢占优先级，2位响应优先级
	BSP_Key_Init();
	BSP_ExtInt_Init();
	
	while (1)
	{
			if(BreathLedstate == 1)
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
						if(BreathLedstate == 0)
						{
							BSP_Led_Off(Led1);
							break;
						}
					}
					
					if(BreathLedstate == 0)
						{
							BSP_Led_Off(Led1);
							break;
						}
					
					for(i = 0; i < period; ++i)
					{
						BSP_Led_On(Led1);
						DelayCount(period - i);
						BSP_Led_Off(Led1);
						DelayCount(i);
						if(BreathLedstate == 0)
						{
							BSP_Led_Off(Led1);
							break;
						}
					}
					
					if(BreathLedstate == 0)
						{
							BSP_Led_Off(Led1);
							break;
						}
				}
			}
	}
}

