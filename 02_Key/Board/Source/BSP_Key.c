/***********************************************************************************
 Key ����  huo  2016-12-23  10:00
 Key IO��Key1-PF9 Key2-PG13 ���·��ص͵�ƽ
************************************************************************************/
#include "BSP_Key.h"					//Key����ͷ�ļ�

/*
*********************************************************************************************************
*	�� �� ��: BSP_Key_Init
*	����˵��: ����Key��ʼ������
*	��    ��: ��
*	�� �� ֵ: ��
*********************************************************************************************************
*/
void BSP_Key_Init(void)
{
	BSP_Key_GPIO_Init();
}

/*
*********************************************************************************************************
*	�� �� ��: BSP_Key_GPIO_Init
*	����˵��: ����Key GPIO��ʼ������
*	��    ��: ��
*	�� �� ֵ: ��
*********************************************************************************************************
*/
static void BSP_Key_GPIO_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	RCC_APB2PeriphClockCmd(RCC_KEYALL, ENABLE);				//ʹ��GPIOFʱ�� 
	
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;			//�������
	GPIO_InitStructure.GPIO_Pin = GPIO_PIN_KEY1;			//Key1����
	GPIO_Init(GPIO_PORT_KEY1, &GPIO_InitStructure);
	GPIO_InitStructure.GPIO_Pin = GPIO_PIN_KEY2;			//Key2����
	GPIO_Init(GPIO_PORT_KEY2, &GPIO_InitStructure);
}

/*
*********************************************************************************************************
*	�� �� ��: BSP_Key_Scan
*	����˵��: ����Keyɨ�蹦�ܺ���
*	��    ��: KeyCount : �������
*	�� �� ֵ: KeyValue : ����״̬
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

