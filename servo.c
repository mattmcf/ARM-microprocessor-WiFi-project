/*
 * servo.c contains routines for initializing and changing timer
 */

#include "stm32f4xx_TIM.h"
#include "stm32f4xx_rcc.h"
#include "stm32f4xx_gpio.h"
#include "stdint.h"
#include "servo.h"

#define TIM4_PSC_SET	16		/* User System CLK (16MHz) / 16 = 1MHz timer */
#define TIM4_ARR_SET	19999	/* 20,000 milliseconds */
#define TIM4_CCR1_MIDDLE	1200	/* 1.5 ms should be 7.5% duty cycle */

#define TIM2_PSC_SET 	16000
#define TIM2_ARR_SET 	99


#define OPEN 1600
#define CLOSED 800

/*
 * Initializes TIM4 for PWM mode output on GPIOB Pin 6
 */
void servo_init( void )
{
	/* Enable clock to GPIO port B */
	RCC->AHB1ENR = RCC_AHB1ENR_GPIOBEN | RCC->AHB1ENR;

	/* Enable clock to TIM 4 Peripheral */
	RCC->APB1ENR = RCC_APB1ENR_TIM4 | RCC->APB1ENR;

	/* Set GPIOB Pin 6 as Alternate Function */
	//GPIOB->MODER = GPIOx_MODER_PIN6_MASK | GPIOB->MODER;
	GPIOB->MODER &= 0xFFFFCFFF;
	GPIOB->MODER |= 0x00002000;

	/* Specify GPIOB Pin 6 to map Alternate Function 2 -> TIM4_CH1 */
	//GPIOB->AFRL = GPIOx_AFRL_PIN6_MASK | GPIOB->AFRL;
	GPIOB->AFRL &= 0xFCFFFFFF;
	GPIOB->AFRL |= 0x02000000;

	/* TIM4 uses system clock on reset */
	/* TIM4 resets to upcounting mode */

	/* Set Capture and Compare Mode to PMW mode 1 */
	TIM4->CCMR1 = TIMx_CCMR1_OCM1_MASK | TIM4->CCMR1;

	/* Enable Capture and Compare Output */
	TIM4->CCER = TIMx_CCER_CC1E_MASK | TIM4->CCER;

	/* Set Prescalar to 16 -> 1 MHz clock on timer */
	TIM4->PSC = TIM4_PSC_SET;

	/* Set Reload Value to 19,999 -> 50 Hz fundamental frequency */
	TIM4->ARR = TIM4_ARR_SET;

	TIM4->CCR1 = TIM4_CCR1_MIDDLE;

	/* Enable Timer */
	TIM4->CR1 = TIMx_CR1_CEN_MASK | TIM4->CR1;
}

/*
 * initializes TIM2_CH3 to a PWM mode output of 50% duty cycle at 10 Hz
 */
void TIM2_init( void )
{
	/* enable clock to TIM2 */
	RCC->APB1ENR = RCC_APB1ENR_TIM2 | RCC->APB1ENR;

	/* Set Capture and Compare Mode of channel 3 to PMW mode 1 */
	TIM2->CCMR2 = TIMx_CCMR2_OCM3_MASK | TIM2->CCMR2;

	/* Enable Capture and Compare output on CH 3 */
	TIM2->CCER = TIMx_CCER_CC3E_MASK | TIM2->CCER;

	/* Set prescalar */
	TIM2->PSC = TIM2_PSC_SET;

	/* Set ARR: 10 Hz */
	TIM2->ARR = TIM2_ARR_SET;

	/* Set 50% duty cycle */
	TIM2->CCR3 = TIM2_ARR_SET/2;

}

/*
 * starts Timer 2
 */
void TIM2_start( void )
{
	TIM2->CR1 = TIMx_CR1_CEN_MASK | TIM2->CR1;
}

/*
 * disables timer 2
 */
void TIM2_disable( void )
{
	TIM2->CR2 = TIMx_CR1_DES_MASK & TIM2->CR2;
}

/*
 * Moves servo to corresponding angle to argument
 */
void servo_change( uint32_t read)
{
	TIM4->CCR1 = read;
}

/*
 * closes gate
 */
void servo_closegate( void )
{
	TIM4->CCR1 = CLOSED;
}

/*
 * opens gate
 */
void servo_opengate( void )
{
	TIM4->CCR1 = OPEN;
}

/*
 * maps ADC argument (0x000 - 0xFFF) to servo
 */
void servo_mapADC( uint32_t val )
{
	int tmp;
	if( val > 0xFFF){
		tmp = OPEN;
	} else if( val < 0x000 ){
		tmp = CLOSED;
	} else{
		tmp = val;
	}

	TIM4->CCR1 = (tmp >> 2) + 800;
}
