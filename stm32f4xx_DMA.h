#pragma once

#include "stdint.h"

volatile typedef struct
{
	uint32_t LISR;
	uint32_t HISR;
	uint32_t LIFCR;
	uint32_t HIFCR;
	uint32_t S0CR;
	uint32_t S0NDTR;
	uint32_t S0PAR;
	uint32_t S0M0AR;
	uint32_t S0M1AR;
	uint32_t S0FCR;
	/* don't use any other streams in lab 6 */
} DMA_Typedef;

#define	DMA2_base		(0x40026400)
#define DMA2			((DMA_Typedef*)DMA2_base)

#define DMAx_SxCR_DISABLE_MASK	(0xfffffffe)	/* must read and confirm that stream is disabled before configuring */
#define DMAx_SxCR_ENABLE_MASK	(0x00000001)

#define DMAx_SxCR_CHSEL_CH0_MASK	(0xf1ffffff)	/* select channel 0 */

#define DMAx_SxCR_MSIZE_16B_MASK	(0xffff9fff)
#define DMAx_SxCR_MSIZE_16B_SET		(0x00002000)	/* set memory size to half-word, 16Bits */

#define DMAx_SxCR_PSIZE_16B_MASK	(0xffffe7ff)
#define DMAx_SxCR_PSIZE_16B_SET		(0x00000800)	/* set peripheral memory size to 32 bits */

#define DMAx_SxCR_MINC_MASK			(0x00000400)	/* turn on memory address increments  */

#define DMAx_SxCR_TCIE_MASK			(0x00000010)	/* enable transfer complete interrupts */
#define DMAx_LIFCR_CTCIFO_MASK		(0x00000020)	/* clear transfer complete interrupt flag for stream 0 */
#define DMAx_LIFCR_CLEARALL_MASK	(0x0000007D)	/* clears all interrupt flags for stream 0*/
