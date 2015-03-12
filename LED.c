/*
 * LED.c - routines for initializing and manipulating LEDs on the STM32f4-discovery board
 */

#include "LED.h"

#include "stm32f4xx_gpio.h"
#include "stm32f4xx_rcc.h"

void LED_init(void)
{
	/* Turn on GPIOD's clock */
	RCC->AHB1ENR |= RCC_AHB1ENR_GPIODEN;

	/* Clear any existing GPIOD pin 15:12 mode settings */
	GPIOD->MODER &= GPIOx_MODER_PIN12_MASK &
					GPIOx_MODER_PIN13_MASK &
					GPIOx_MODER_PIN14_MASK &
					GPIOx_MODER_PIN15_MASK;

	/* Configure GPIOD pins 15:12 as output, push-pull  */
	GPIOD->MODER |= GPIOx_MODER_PIN12_GPOUT |
					GPIOx_MODER_PIN13_GPOUT |
					GPIOx_MODER_PIN14_GPOUT |
					GPIOx_MODER_PIN15_GPOUT;

	/* Clear all of the LEDs */
	LED_update( LED_GREEN_OFF );
	LED_update( LED_RED_OFF );
	LED_update( LED_BLUE_OFF );
	LED_update( LED_ORANGE_OFF );
}

void LED_update(uint32_t new_state)
{
	GPIOD->BSRR = new_state;
}
