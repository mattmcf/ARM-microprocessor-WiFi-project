#pragma once

#include <stdint.h>

/* USART Registers, see the reference manual sections 26.6.X */
volatile typedef struct
{
	uint32_t SR;                /* Status Register */
	uint32_t DR;                /* Data Register */
	uint32_t BRR;               /* Baud Rate Register */
	uint32_t CR1;               /* Config Register 1 */
	uint32_t CR2;               /* Config Register 2 */
	uint32_t CR3;               /* Config Register 3 */
	uint32_t GTPR;              /* Guard Time and Prescale Register */
} USART_TypeDef;

/*
 * USARTs
 */
#define USART1_BASE   (0x40011000)
#define USART1        ((USART_TypeDef*)USART1_BASE)

#define USART2_BASE   (0x40004400)  /* Base address of USART2 peripheral */
#define USART2        ((USART_TypeDef*)USART2_BASE)

#define USART3_BASE		(0x40004800)
#define USART3			((USART_TypeDef*)USART3_BASE)

#define USARTx_SR_TC          (0x40)     /* Transmission Complete */
#define USARTx_SR_TXE         (0x80)     /* Transmit Shift Register Empty */
#define USARTx_SR_RXNE        (0x20)     /* Receive Shift Register Not Empty */
#define USARTx_SR_ORE         (0x08)     /* Overrun occurred */
#define USARTx_SR_NF          (0x04)     /* Noise Flag */
#define USARTx_SR_FE          (0x02)     /* Framing Error */

#define USARTx_CR1_RE   (0x00000004)     /* Receiver Enable */
#define USARTx_CR1_TE   (0x00000008)     /* Transmitter Enable */
#define USARTx_CR1_RXNEIE (0x00000020)   /* Receive interrupt enable */
#define USARTx_CR1_UE   (0x00002000)     /* USART enable */

