/***********************************************************************************
 ExtInt ����  huo  2016-12-23  10:15
 �ⲿ�����ж�
 Key IO��Key1-PF9 Key2-PG13 ���·��ص͵�ƽ
 Led IO��Led-PF11 �͵�ƽ����
************************************************************************************/
#include "stm32f10x.h"		//STM32F10xͷ�ļ�
#include "BSP_Led.h"					//Ledͷ�ļ�
#include "BSP_Key.h"					//Key����ͷ�ļ�
#include "BSP_ExtInt.h"				//ExtInt����ͷ�ļ�

uint8_t KeyState=0xFF;
/* ����ȷ��ʱ���� */
void DelayCount(uint32_t Count)
{
	while(Count--);
}

/* ������ */
int main(void)
{
//	uint8_t KeyState=0xFF;
	
	BSP_Led_Init();				//LED��GPIO��ʼ��
	/* ֻҪ�����õ��жϣ�����Ҫ�����жϷ��飻��ʹ��Ĭ�Ϸ��鷽��  */
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2); //����NVIC�жϷ���2:2λ��ռ���ȼ���2λ��Ӧ���ȼ�
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

