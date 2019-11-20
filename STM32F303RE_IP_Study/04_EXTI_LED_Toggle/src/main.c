#include "stm32f3xx.h"

void EXTI_INT_Enable();

int main(void)
{
	RCC->AHBENR |= RCC_AHBENR_GPIOAEN;
	GPIOA->MODER &= ~GPIO_MODER_MODER5;
	GPIOA->MODER |= GPIO_MODER_MODER5_0;

	RCC->AHBENR |= RCC_AHBENR_GPIOCEN;
	GPIOC->MODER &= ~GPIO_MODER_MODER13;

	RCC->APB2ENR |= RCC_APB2ENR_SYSCFGEN;
	SYSCFG->EXTICR[3] &= ~SYSCFG_EXTICR4_EXTI13;
	SYSCFG->EXTICR[3] |= SYSCFG_EXTICR4_EXTI13_PC;

	EXTI->RTSR |= EXTI_RTSR_TR13;
	EXTI->IMR |= EXTI_IMR_MR13;

	EXTI_INT_Enable();

	while(1)
	{

	}

	return 0;
}


void EXTI_INT_Enable()
{
	uint32_t priorityGroup;
	uint32_t PreemptPriority = 0;
	uint32_t SubPriority = 0;
	uint32_t priority;

	priorityGroup = NVIC_GetPriorityGrouping();
	priority =  NVIC_EncodePriority(priorityGroup, PreemptPriority, SubPriority);

	NVIC_SetPriority(EXTI15_10_IRQn, priority);

	NVIC_EnableIRQ(EXTI15_10_IRQn);
}

void EXTI15_10_IRQHandler()
{
	static int flag = 0;
	if(flag)
	{
		GPIOA->ODR |= GPIO_ODR_5;
		flag = 0;
	}
	else
	{
		GPIOA->BRR |= GPIO_BRR_BR_5;
		flag = 1;
	}

	/* Clear Pending Bit */
	EXTI->PR |= EXTI_PR_PR13;
}