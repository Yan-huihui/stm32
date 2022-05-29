#ifndef _BSP_KEY_H_
#define _BSP_KEY_H_
#include "stm32f10x.h"

/*! 枚举Key编号 */
typedef enum
{
  KeyAll = 0x0F,
  Key1   = 0x01,
  Key2   = 0x02,
  Key3   = 0x04,
  Key4   = 0x08,
}KeyCount_TypeDef;

/* Key口 */
#define RCC_KEYALL      (RCC_APB2Periph_GPIOF | RCC_APB2Periph_GPIOG)
#define GPIO_PORT_KEY1  GPIOF
#define GPIO_PIN_KEY1   GPIO_Pin_9
#define GPIO_PORT_KEY2  GPIOG
#define GPIO_PIN_KEY2   GPIO_Pin_13

void BSP_Key_Init(void);
static void BSP_Key_GPIO_Init(void);
uint8_t BSP_Key_Scan(KeyCount_TypeDef KeyCount);

#endif
