/*
 * ADC.c contains routines for initializing and reading values of ADC1
 */

#include "ADC.h"
#include "stm32f4xx_ADC.h"
#include "stm32f4xx_rcc.h"
#include "stm32f4xx_gpio.h"
#include "cortexm4_nvic.h"
#include "servo.h"
#include "stm32f4xx_DMA.h"

int initialized;

#define BUF_SIZE 10
uint16_t buffer[BUF_SIZE];

static void(*callback_fn)(uint16_t * , uint32_t);	// handles read value when conversion completes

void __attribute__ ((interrupt)) ADC_handler(void)
{
	/* Call the user-specified callback function */
	callback_fn( (uint16_t *) buffer, BUF_SIZE );

	/* reading data register clears interrupt */

}

void __attribute__ ((interrupt)) DMA2_stream0_handler(void)
{
	/* clear interrupt */
	// disable stream 0 (wait until confirmed zero)
	DMA2->S0CR &= DMAx_SxCR_DISABLE_MASK;
	while( DMAx_SxCR_ENABLE_MASK & DMA2->S0CR){;}

	//DMA2->S0CR |= DMAx_LIFCR_CTCIFO_MASK;
	DMA2->LIFCR |= DMAx_LIFCR_CLEARALL_MASK;

	/* disable timer */
	TIM2_disable();

	/* Call the user-specified callback function */
	callback_fn( (uint16_t *) buffer, BUF_SIZE );

}

void ADC_init( void(*ADC_callback_fn)(uint16_t * , uint32_t) )
{
	/* Enable Clock in Port A Peripheral */
	RCC->AHB1ENR = RCC_AHB1ENR_GPIOAEN | RCC->AHB1ENR;

	/* Enable clock to ADC Peripheral */
	RCC->APB2ENR = RCC_APB2ENR_ADC1 | RCC->APB2ENR;

	/* Set pin 1 to analog mode -> ADC_w */
	GPIOA->MODER = GPIOx_MODER_PIN1_ANALOG | GPIOA->MODER;

	/* Set the regular sequence to a length of 1 */
	ADC1->SQR1 = ADC1_SQR1_MASK & ADC1->SQR1;

	/* Set ADC1 to sample channel 1 first */
	//ADC1->SQR3 = ADC1_SQR3_MASK & ADC1->SQR3;
	ADC1->SQR3 = ADC1_SQR3_MASK;

	/* Set sample length to 15 clock cycles */
	ADC1->SMPR2 = ADC1_SMPR2_SMP1_MASK | ADC1->SMPR2;

	/* Resolution starts at reset with 12 bits resolution */
	/* Set ADON bit in CR2 to enable reading */
	ADC1->CR2 = ADC1_CR2_ADON_MASK | ADC1->CR2;

	// set interrupt call back function
	callback_fn = ADC_callback_fn;

	// enable interrupts
	//ADC1->CR1 = ADCx_CR1_EOCIE_MASK | ADC1->CR1;

	// enable NVIC interrupt
	NVIC_INTERRUPT_ADC_ENABLE();

	TIM2_init();

	// set conversion to start on external trigger (TIM2_CH3)
	ADC1->CR2 = ADCx_CR2_EXTEN_MASK & ADC1->CR2;
	ADC1->CR2 = ADCx_CR2_EXTEN_SET | ADC1->CR2;

	ADC1->CR2 = ADCx_CR2_EXTSEL_MASK & ADC1->CR2;
	ADC1->CR2 = ADCx_CR2_EXTSEL_SET | ADC1->CR2;

	// disable TIM2
	//TIM2_disable();

	// clear DMA flag in ADC_CR2
	//ADC1->CR2 = ADCx_CR2_CLRDMA_MASK & ADC1->CR2;

	int i;
	for( i = 0; i < BUF_SIZE; i++){
		buffer[i] = 0;
	}

	// enable clock in DMA2
	RCC->AHB1ENR |= RCC_AHB1RSTR_DMA2;

	// disable stream 0 (wait until confirmed zero)
	DMA2->S0CR &= DMAx_SxCR_DISABLE_MASK;
	while( DMAx_SxCR_ENABLE_MASK & DMA2->S0CR){;}

	// enable DMA interrupts when transfer is complete
	DMA2->S0CR |= DMAx_SxCR_TCIE_MASK;

	NVIC_INTERRUPT_DMA2_STREAM0_ENABLE();

	// configure ADC to user DMA controller
	ADC1->CR2 |= ADCx_CR2_DMA_MASK;

	// allow DMA request (?)
	ADC1->CR2 |= ADCx_CR2_DDS_MASK;
}

/*
 * initiates conversion, busy waits until conversion is done, then returns converted value
 */
uint32_t ADC_read( void )
{
	uint32_t temp;
	/* Set SWSTART bit to start regular conversion sequence */
	ADC1->CR2 = ADC1_CR2_SWSTART_MASK | ADC1->CR2;

	/* When SR EOC bit goes high, data is ready to be read */
	while( ! ADC1_SR_EOC_MASK & ADC1->SR );

	temp = ADC1_DR_12BIT_R_MASK & ADC1->DR;
	/* return analog data, data is right aligned with bit 11 as MSB */
	return( temp );
}

/*
 * starts ADC conversion
 */
void ADC_start( void )
{
	/* Set SWSTART bit to start regular conversion sequence */
	//ADC1->CR2 = ADC1_CR2_SWSTART_MASK | ADC1->CR2;

	// disable TIM2
	TIM2_disable();

	// clear DMA flag in ADC_CR2
	ADC1->CR2 &= ADCx_CR2_CLRDMA_MASK & ADC1->CR2;

	// disable stream 0 (wait until confirmed zero)
	DMA2->S0CR &= DMAx_SxCR_DISABLE_MASK;
	while( DMAx_SxCR_ENABLE_MASK & DMA2->S0CR) {;}

	//set peripheral port address where data is collected from
	DMA2->S0PAR = &(ADC1->DR);

	// set memory address where data is stored
	DMA2->S0M0AR = buffer;

	// configure # of items
	DMA2->S0NDTR = BUF_SIZE;

	// set size of data to 16 bits in memory
	DMA2->S0CR &= DMAx_SxCR_MSIZE_16B_MASK;
	DMA2->S0CR |= DMAx_SxCR_MSIZE_16B_SET;

	// set size of peripheral data to
	DMA2->S0CR &= DMAx_SxCR_PSIZE_16B_MASK;
	DMA2->S0CR |= DMAx_SxCR_PSIZE_16B_SET;

	// set to increment memory address
	DMA2->S0CR |= DMAx_SxCR_MINC_MASK;

	// clear all interrupt flags
	DMA2->LIFCR |= DMAx_LIFCR_CLEARALL_MASK;

	// enable DMA
	DMA2->S0CR |= DMAx_SxCR_ENABLE_MASK;

	// clear OVR flag in ADC SR
	ADC1->SR &= ADCx_SR_OVR_CLEAR_MASK;

	// configure ADC to user DMA controller
	ADC1->CR2 |= ADCx_CR2_DMA_MASK;

	TIM2_start();
}
