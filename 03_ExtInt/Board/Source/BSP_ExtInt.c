/***********************************************************************************
 ExtInt ����  huo  2016-12-23  10:15
 KEY IO��KEY1-PF9 KEY2-PG13 ���·��ص͵�ƽ
************************************************************************************/
#include "BSP_ExtInt.h"					//ExtInt����ͷ�ļ�

int BreathLedstate = 0;

/* ����ȷ��ʱ���� */
static void BSP_ExtInt_Delay(uint32_t Count)
{
	while(Count--);
}

/*
*********************************************************************************************************
*	�� �� ��: BSP_ExtInt_Init
*	����˵��: ����ExtInt��ʼ������
*	��    ��: ��
*	�� �� ֵ: ��
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
*	�� �� ��: BSP_ExtInt_EXTI_Init
*	����˵��: ����ExtInt EXTI��ʼ������
*	��    ��: ��
*	�� �� ֵ: ��
*********************************************************************************************************
*/
static void BSP_ExtInt_EXTI_Init(void)
{
 	EXTI_InitTypeDef EXTI_InitStructure;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO,ENABLE);	//ʹ�ܸ��ù���ʱ��

	//GPIOF.9 �ж����Լ��жϳ�ʼ������   �½��ش���
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOF,GPIO_PinSource9);
	EXTI_InitStructure.EXTI_Line=EXTI_Line9;	//KEY1
	EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;	
	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling;
	EXTI_InitStructure.EXTI_LineCmd = ENABLE;
	EXTI_Init(&EXTI_InitStructure);	 	//����EXTI_InitStruct��ָ���Ĳ�����ʼ������EXTI�Ĵ���

	//GPIOG.13	  �ж����Լ��жϳ�ʼ������ �½��ش��� //KEY2
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOG,GPIO_PinSource13);
	EXTI_InitStructure.EXTI_Line=EXTI_Line13;
	EXTI_Init(&EXTI_InitStructure);	  	//����EXTI_InitStruct��ָ���Ĳ�����ʼ������EXTI�Ĵ���
}

/*
*********************************************************************************************************
*	�� �� ��: BSP_ExtInt_NVIC_Init
*	����˵��: ����ExtInt NVIC��ʼ������
*	��    ��: ��
*	�� �� ֵ: ��
*********************************************************************************************************
*/
static void BSP_ExtInt_NVIC_Init(void)
{
 	NVIC_InitTypeDef NVIC_InitStructure;

	NVIC_InitStructure.NVIC_IRQChannel = EXTI9_5_IRQn;			//ʹ�ܰ���KEY1���ڵ��ⲿ�ж�ͨ��
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x02;	//��ռ���ȼ�2�� 
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x03;					//�����ȼ�3
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;								//ʹ���ⲿ�ж�ͨ��
	NVIC_Init(&NVIC_InitStructure); 

	NVIC_InitStructure.NVIC_IRQChannel = EXTI15_10_IRQn;			//ʹ�ܰ���KEY2���ڵ��ⲿ�ж�ͨ��
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x02;	//��ռ���ȼ�2�� 
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x02;					//�����ȼ�2
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;								//ʹ���ⲿ�ж�ͨ��
	NVIC_Init(&NVIC_InitStructure);
}

/*
*********************************************************************************************************
*	�� �� ��: BSP_ExtInt_ISR1
*	����˵��: ����ExtInt �жϷ����ܺ���
*	��    ��: ��
*	�� �� ֵ: ��
*********************************************************************************************************
*/
void BSP_ExtInt_ISR1(void)
{
	BSP_ExtInt_Delay(0x19999);//����
	if(!(BSP_Key_Scan(Key1) & Key1))	 	 //KEY1����
	{	
		BreathLedstate = 1;
//		BSP_Led_On(Led1);	
	}
	EXTI_ClearITPendingBit(EXTI_Line9); //���LINE9�ϵ��жϱ�־λ  
}

/*
*********************************************************************************************************
*	�� �� ��: BSP_ExtInt_ISR2
*	����˵��: ����ExtInt �жϷ����ܺ���
*	��    ��: ��
*	�� �� ֵ: ��
*********************************************************************************************************
*/
void BSP_ExtInt_ISR2(void)
{
	BSP_ExtInt_Delay(0x19999);//����
	if(!(BSP_Key_Scan(Key2) & Key2))	  //����KEY2
	{
		BreathLedstate = 0;
		BSP_Led_Off(Led1);
	}		 
	EXTI_ClearITPendingBit(EXTI_Line13);  //���LINE13�ϵ��жϱ�־λ  
}
