#include <ch32v00x.h>
#include <debug.h>

void NMI_Handler(void) __attribute__((interrupt("WCH-Interrupt-fast")));
void HardFault_Handler(void) __attribute__((interrupt("WCH-Interrupt-fast")));
void EXTI7_0_IRQHandler(void) __attribute__((interrupt("WCH-Interrupt-fast")));
void Delay_Init(void);
void Delay_Ms(uint32_t n);


#define COUNTDOWN_TIME 300
int countdown = COUNTDOWN_TIME;

int main(void)
{
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
	SystemCoreClockUpdate();
	Delay_Init();

	GPIO_InitTypeDef GPIO_InitStructure = {0};

	// LED
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOD, ENABLE);
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOD, &GPIO_InitStructure);
	GPIO_WriteBit(GPIOD, GPIO_Pin_6, 1);

	// Button
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOC, &GPIO_InitStructure);


	while (1)
	{
		if (countdown > 0)
		{
			for(int i = 0; i < 100; i++) {
				Delay_Ms(10);
				if(GPIO_ReadInputDataBit(GPIOC, GPIO_Pin_4)) {
					countdown = COUNTDOWN_TIME;
				}
			}
			countdown--;
		}
		else
		{
		    GPIO_WriteBit(GPIOD, GPIO_Pin_6, 0);
		}
	}
}

void NMI_Handler(void) {}
void HardFault_Handler(void)
{
        while (1)
        {
        }
}
