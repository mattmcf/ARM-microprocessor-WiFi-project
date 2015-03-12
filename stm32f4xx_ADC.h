#pragma once

#include "stdint.h"

volatile typedef struct
{
	uint32_t SR;						/* Status Register				- offset 0x00 */
	uint32_t CR1;						/* Control Register 1			- offset 0x04 */
	uint32_t CR2;						/* Control Register 2			- offset 0x08 */
	uint32_t SMPR1;						/* Sample Time Register 1		- offset 0x0C */
	uint32_t SMPR2;						/* Sample Time Register 2		- offset 0x10 */
	uint32_t JOFR[6];					/* Injected Data Registers		- offset 0x14 - 0x28 */
	uint32_t SQR1;						/* Regular Sequence Register 1	- offset 0x2C */
	uint32_t SQR2;						/* Regular Sequence Register 2	- offset 0x30 */
	uint32_t SQR3;						/* Regular Sequence Register 3	- offset 0x34 */
	uint32_t JSQR;						/* Injected Sequence Register	- offset 0x38 */
	uint32_t JDR[4];					/* ADC Injected Sequence Register	- offset 0x3C - 0x48 */
	uint32_t DR;						/* Data Register				- offset 0x4C */
} ADC_TypeDef;

/* See datasheet for memory map / base addresses */

/*
 * ADC1
 */
#define ADC1_base		(0x40012000)
#define ADC1			((ADC_TypeDef*)ADC1_base)

#define ADCx_CR1_EOCIE_MASK		(0x00000020)	/* enable EOC interrupt */
#define ADC1_CR2_ADON_MASK		(0x00000001)	/* ADON bit is bit 0 of CR 2*/
#define ADC1_SQR1_MASK			(0xFF0FFFFF)	/* only do one conversion */
//#define ADC1_SQR3_MASK			(0xFFFFFFE1)	/* First conversion = ADC_1 - channel 1 */
#define ADC1_SQR3_MASK			(0x00000001)
#define ADC1_SMPR2_SMP1_MASK	(0x00000008)	/* SMPR2[5:2] = SMP1 - set to 1 for 15 clock cycle sample time */
#define ADC1_SR_EOC_MASK		(0x00000002)	/* EOC bit is bit 1 of SR */
#define ADC1_CR2_SWSTART_MASK	(0x40000000)	/* SWSTART bit is bit 30 of CR 2 */
#define ADC1_DR_12BIT_R_MASK	(0x00000FFF)	/* right twelve bits contain data. MSB is bit 11 */

#define ADCx_CR2_EXTEN_MASK		(0xcfffffff)
#define ADCx_CR2_EXTEN_SET		(0x10000000)	/* set for conversion on rising edge */

#define ADCx_CR2_EXTSEL_MASK	(0xf0ffffff)
#define ADCx_CR2_EXTSEL_SET		(0x04000000)	/* select TIM2_CH3 */

#define ADCx_CR2_DMA_MASK			(0x00000100)	/* turn on DMA mode */
#define ADCx_CR2_CLRDMA_MASK		(0xfffffeff)	/* turn off DMA mode */

#define ADCx_CR2_DDS_MASK			(0x00000200)	/* allow DMA requests to be made as long as data is converted and DMA is one */
#define ADCx_SR_OVR_CLEAR_MASK		(0xffffffdf)	/* clear OVR bit in SR */
