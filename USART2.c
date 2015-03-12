#include <USART2.h>

#include <cortexm4_nvic.h>
#include <stm32f4xx_gpio.h>
#include <stm32f4xx_rcc.h>
#include <stm32f4xx_usart.h>

/* flag to indicate USART2 has been initialized */
/* toggled in init function */
static uint32_t US2initialized = 0;

static uint32_t US3initialized = 0;

/* module-global pointer to the callback function for rx'd bytes */
/* populated in init function. */
static void(*rx_callback_fn)(uint8_t byte);

/* module-global pointer to teh callback function for recieved bytes on USART3 */
static void(*rx_callback_fn_US3)(uint8_t byte);

/* Rudimentary handler assumes the interrupt is due to a byte rx event */
void __attribute__ ((interrupt)) USART2_handler(void)
{
	uint8_t byte;

	/* must read the USART2_DR to clear the interrupt */
	byte = USART2->DR;

	if( rx_callback_fn )
	{
		rx_callback_fn(byte);
	}
}

void __attribute__ ((interrupt)) USART3_handler(void)
{
	uint8_t byte;

	/* must read the USART2_DR to clear the interrupt */
	byte = USART3->DR;

	if( rx_callback_fn_US3 )
	{
		rx_callback_fn_US3(byte);
	}
}

void USART2_init(void(*USART2_rx_callback)(uint8_t byte))
{
	rx_callback_fn = USART2_rx_callback;

	/* Enable GPIOD, as USART2 TX is on PD5, and RX is on PD6 */
	RCC->AHB1ENR |= RCC_AHB1ENR_GPIODEN;

	/* Configure PD5 as AF7 (Output, push-pull) */
	GPIOD->AFRL &= GPIOx_AFRL_AFRL5_MASK;
	GPIOD->AFRL |= GPIOx_AFRL_AFRL5_AF7;
	GPIOD->MODER &= GPIOx_MODER_PIN5_MASK;
	GPIOD->MODER |= GPIOx_MODER_PIN5_AF;

	/* Configure PD6 as AF7 (Input) */
	GPIOD->AFRL &= GPIOx_AFRL_AFRL6_MASK;
	GPIOD->AFRL |= GPIOx_AFRL_AFRL6_AF7;
	GPIOD->MODER &= GPIOx_MODER_PIN6_MASK;
	GPIOD->MODER |= GPIOx_MODER_PIN6_AF;

	/* Reset the USART peripheral and enable its clock */
	RCC->APB1ENR &= ~RCC_APB1ENR_USART2;
	RCC->APB1RSTR |= RCC_APB1RSTR_USART2;
	RCC->APB1RSTR &= ~RCC_APB1RSTR_USART2;
	RCC->APB1ENR |= RCC_APB1ENR_USART2;

	/* Enable the USART peripheral */
	USART2->CR1 |= USARTx_CR1_UE;  /* Enable */

	/* Configure for 8N1, 9600 baud (assuming 16MHz clock) */
	USART2->BRR = 1667;             /* 16MHz/1667 ~= 9600 */

	/* Enable transmit */
	USART2->CR1 |= (USARTx_CR1_TE);

	/*
	 *  If a callback function was registered, enable receive and the
	 *  receive interrupt.
	 */
	if( USART2_rx_callback )
	{
		/* Configure Receive Interrupt */
		NVIC_INTERRUPT_USART_2_ENABLE();
		USART2->CR1 |= USARTx_CR1_RXNEIE;
		USART2->CR1 |= (USARTx_CR1_RE);
	}

	US2initialized = 1;
}

void USART3_init(void(*USART3_rx_callback)(uint8_t byte))
{
	rx_callback_fn_US3 = USART3_rx_callback;

	/* Enable GPIOD, as USART2 TX is on PD5, and RX is on PD6 */
	RCC->AHB1ENR |= RCC_AHB1ENR_GPIODEN;

	/* Configure PD8 as AF7 (Output, push-pull) */
	GPIOD->AFRH &= GPIOx_AFRH_AFRH8_MASK;
	GPIOD->AFRH |= GPIOx_AFRH_AFRH8_AF7;
	GPIOD->MODER &= GPIOx_MODER_PIN8_MASK;
	GPIOD->MODER |= GPIOx_MODER_PIN8_AF;

	/* Configure PD9 as AF7 (Input) */
	GPIOD->AFRH &= GPIOx_AFRH_AFRH9_MASK;
	GPIOD->AFRH |= GPIOx_AFRH_AFRH9_AF7;
	GPIOD->MODER &= GPIOx_MODER_PIN9_MASK;
	GPIOD->MODER |= GPIOx_MODER_PIN9_AF;

	/* Reset the USART peripheral and enable its clock */
	RCC->APB1ENR &= ~RCC_APB1ENR_USART3;
	RCC->APB1RSTR |= RCC_APB1RSTR_USART3;
	RCC->APB1RSTR &= ~RCC_APB1RSTR_USART3;
	RCC->APB1ENR |= RCC_APB1ENR_USART3;

	/* Enable the USART peripheral */
	USART3->CR1 |= USARTx_CR1_UE;  /* Enable */

	/* Configure for 8N1, 9600 baud (assuming 16MHz clock) */
	USART3->BRR = 1667;             /* 16MHz/1667 ~= 9600 */

	/* Enable transmit */
	USART3->CR1 |= (USARTx_CR1_TE);

	/*
	 *  If a callback function was registered, enable receive and the
	 *  receive interrupt.
	 */
	if( USART3_rx_callback )
	{
		/* Configure Receive Interrupt */
		NVIC_INTERRUPT_USART_3_ENABLE();
		USART3->CR1 |= USARTx_CR1_RXNEIE;
		USART3->CR1 |= (USARTx_CR1_RE);
	}

	US3initialized = 1;
}

/* Send a single character out USART2 */
void USART2_putchar(uint8_t byte)
{
	if( US2initialized )
	{
		/* Wait for the transmit shift register to be free... */
		while( !(USART2->SR & USARTx_SR_TXE) );
		USART2->DR = byte;
	}
}

/* Send a single character out USART3 */
void USART3_putchar(uint8_t byte)
{
	if( US3initialized )
	{
		/* Wait for the transmit shift register to be free... */
		while( !(USART3->SR & USARTx_SR_TXE) );
		USART3->DR = byte;
	}
}

/* Send a null-terminated string out USART2 */
void USART2_putstr(uint8_t *buffer)
{
	if( US2initialized )
	{
		while( *buffer != '\0')
		{
			USART2_putchar(*buffer);
			buffer++;
		}
	}
}

/* Send a null-terminated string out USART3 */
void USART3_putstr(uint8_t *buffer)
{
	if( US3initialized )
	{
		while( *buffer != '\0')
		{
			USART3_putchar(*buffer);
			buffer++;
		}
	}
}
