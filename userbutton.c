#include <userbutton.h>

#include <cortexm4_nvic.h>
#include <stm32f4xx_exti.h>
#include <stm32f4xx_rcc.h>
#include "stm32f4xx_gpio.h"

static void(*callback_fn)(void);

void __attribute__ ((interrupt)) EXTI0_handler(void)
{
	/* Call the user-specified callback function */
	callback_fn();

	/* Clear the interrupt pending flag */
	EXTI->PR |= EXTI_PR_PR0;
}

void userbutton_init(void(*button_callback_fn)(void))
{
	callback_fn = button_callback_fn;

	/* Pushbutton is on GPIOA pin 0 - by default EXTI0 mapped to port A */
	/* Just need to enable GPIOA - by default configured as input */
	RCC->AHB1ENR |= RCC_AHB1ENR_GPIOAEN;

	/* Configure for falling-edge interrupts */
	//EXTI->FTSR |= EXTI_FTSR_TR0;

	/* Configure for rising-edge interrupts */
	EXTI->RTSR |= EXTI_RTSR_TR0;

	/* Enable interrupts on EXTI0 */
	NVIC_INTERRUPT_EXTI_0_ENABLE();
	EXTI->IMR |= EXTI_IMR_MR0;
}

uint32_t userbutton_read( void )
{
	uint32_t val = GPIOx_IDR_PIN1_MASK & GPIOA->IDR;
	return( val );
}
