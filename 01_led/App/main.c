/***********************************************************************************
 Led ����  huo  2016-12-23  09:45
 Led IO��Led-PF11 �͵�ƽ����
************************************************************************************/
#include "stm32f10x.h"				//STM32F10xͷ�ļ�
#include "BSP_Led.h"							//LED����ͷ�ļ�

/* ����ȷ��ʱ���� */                                                                                                                                
void DelayCount(uint32_t Count)
{
	while(Count--);
}                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                 
                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                        
/* ������ */
int main(void)
{
	int i;
	int period = 2000;
	BSP_Led_Init();				//LED��GPIO��ʼ��
		
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

