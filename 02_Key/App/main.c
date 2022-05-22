/***********************************************************************************
 Key ����  huo  2016-12-23  10:00
 Key IO��Key1-PF9 Key2-PG13 ���·��ص͵�ƽ
 Led IO��Led-PF11 �͵�ƽ����
************************************************************************************/
#include "stm32f10x.h"		//STM32F10xͷ�ļ�
#include "BSP_Led.h"			//Ledͷ�ļ�
#include "BSP_Key.h"			//Key����ͷ�ļ�

uint8_t KeyState=0xFF;

/* ����ȷ��ʱ���� */
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
			
			KeyState = BSP_Key_Scan(KeyAll);	//����ɨ��
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
			
			KeyState = BSP_Key_Scan(KeyAll);	//����ɨ��
			if(!(KeyState & Key2))
			{
				BSP_Led_Off(Led1);
				return 0;
			}
		}
	}
}

/* ������ */
int main(void)
{
	BSP_Led_Init();				//Led��GPIO��ʼ��
	BSP_Key_Init();				//Key��ʼ��
	
	while (1)
	{
//		BSP_Led_On(Led1);
//		DelayCount(0x4FFFFF);
//		BSP_Led_Off(Led1);
//		DelayCount(0x4FFFFF);
		
//		BSP_Led_Toggle(Led1);
//		DelayCount(0x4FFFFF);
		
		KeyState = BSP_Key_Scan(KeyAll);	//����ɨ��

//		if(!(KeyState & Key1))						//�����ȼ�
//			BSP_Led_On(Led1);
//		if(!(KeyState & Key2))
//			BSP_Led_Off(Led1);

		if(!(KeyState & Key1))						//Key1 ���ȼ����� Key2
			BreathLed();
		else if(!(KeyState & Key2))
			BSP_Led_Off(Led1);
	}
}

