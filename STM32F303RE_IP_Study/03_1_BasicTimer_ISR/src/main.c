#include "stm32f3xx.h"
#include "uart.h"

uint8_t flag = 0;

void BasicTimerInit();
void BasicTimerINT_Enable();

int main(void)
{
	uint8_t buf = 'A';

	GPIO_Init();
	UART_Init(115200U);

	BasicTimerInit();

	while (1)
	{
		if(flag)
		{
			WriteByte(buf);
			flag = 0;
		}
	}

	return 0;
}

void BasicTimerInit()
{
	/* TIM6 Clock Enable. */
	RCC->APB1ENR |= RCC_APB1ENR_TIM7EN;

	/* TIM6 Counter Disable */
	TIM7->CR1 &= ~TIM_CR1_CEN;

	/*
	 * Target Period
	 * 1 Second.
	 * Clock: 8,000,000[Hz]
	 * PSC: 8000 - 1
	 * ARR: 1000 - 1
	 */

	TIM7->SR &= ~TIM_SR_UIF;

	/* Set prescaler */
	TIM7->PSC = 8000 - 1;

	/* Set Auto-Reload Register */
	TIM7->ARR = 1000 - 1;

	TIM7->DIER |= TIM_DIER_UIE;
	//TIM7->CR1 |= TIM_CR1_ARPE;
	BasicTimerINT_Enable();

	/* TIM7 Counter Enable */
	TIM7->CR1 |= TIM_CR1_CEN;
}

void BasicTimerINT_Enable()
{
	uint32_t priorityGroup;
	uint32_t PreemptPriority = 0;
	uint32_t SubPriority = 0;
	uint32_t priority;

	priorityGroup = NVIC_GetPriorityGrouping();
	priority =  NVIC_EncodePriority(priorityGroup, PreemptPriority, SubPriority);

	NVIC_SetPriority(TIM7_IRQn, priority);

	NVIC_EnableIRQ(TIM7_IRQn);
}

void TIM7_IRQHandler()
{
	TIM7->SR &= ~TIM_SR_UIF;

	flag = 1;
}