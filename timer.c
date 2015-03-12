/*
 * timer.c includes code for routines that initialize and start timer
 */

#include "timer.h"
#include "stm32f4xx_TIM.h"
#include "stm32f4xx_rcc.h"
#include "cortexm4_nvic.h"

#define PSC_VAL	16000	// set timer to use 1 kHz clock

static uint32_t initialized = 0;

static void(*callback_fn)(void);

void __attribute__ ((interrupt)) TIM3_handler(void)
{
	/* Clear the interrupt pending flag */
	TIM3->SR &= TIMx_SR_UID_MASK;

	/* Call the user-specified callback function */
	callback_fn();
}

/*
 * Initializes timer with callback function and time (in milliseconds)
 *
 * time input should to be less then or equal to 0xffff
 */
void timer3_init(void(*timer3_callback)( void ), uint32_t time){

	// set callback function for interrupts
	callback_fn = timer3_callback;

	// enable clock
	RCC->APB1ENR = RCC_APB1ENR_TIM3 | RCC->APB1ENR;

	// disable timer
	TIM3->CR1 = TIMx_CR1_CDES_MASK & TIM3->CR1;

	// enable interrupt
	TIM3->DIER = TIMx_DIER_UIE_MASK | TIM3->DIER;

	// set PSC
	TIM3->PSC = 0xffff0000 & TIM3->PSC;
	TIM3->PSC = PSC_VAL | TIM3->PSC;

	// set ARR
	TIM3->ARR = 0xffff0000 & TIM3->ARR;
	if( time > 65535 ){
		TIM3->ARR = 0x0000ffff | TIM3->ARR;
	}
	else{
		TIM3->ARR = time | TIM3->ARR;
	}

	// set count to zero
	TIM3->CNT = 0xffff0000 & TIM3->CNT;

	// enable NVIC interrupts
	NVIC_INTERRUPT_TIM_3_ENABLE();

	initialized = 1;
}

/*
 * Start timer
 */
void timer3_start( void ){

	if( initialized ){

		// set count to zero
		TIM3->CNT = 0xffff0000 & TIM3->CNT;

		// enable timer
		TIM3->CR1 |= TIMx_CR1_CEN_MASK;
	}
}

/*
 * Stop timer
 */
void timer3_disable( void ){
	if( initialized ){

		// disable timer
		TIM3->CR1 = TIMx_CR1_CDES_MASK & TIM3->CR1;

		// set count to zero
		TIM3->CNT = 0xffff0000 & TIM3->CNT;

	}
}
