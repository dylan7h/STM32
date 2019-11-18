#include "stm32f3xx.h"
#include "uart.h"

uint8_t flag = 0;

void BasicTimerInit();

int main(void)
{
	uint8_t buf = 'A';

	GPIO_Init();
	UART_Init(115200U);

	BasicTimerInit();

	while (1)
	{
		if(TIM7->SR & TIM_SR_UIF)
		{
			/* Clear Flag Bit */
			TIM7->SR &= ~TIM_SR_UIF;

			WriteByte(buf);
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

	/* Set prescaler */
	TIM7->PSC = 8000 - 1;

	/* Set Auto-Reload Register */
	TIM7->ARR = 1000 - 1;

	/* TIM6 Counter Enable */
	TIM7->CR1 |= TIM_CR1_CEN;
}

