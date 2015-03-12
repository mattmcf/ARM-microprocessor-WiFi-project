#pragma once

/* Reset and Clock Control Registers, see User's Manual section 6.3.X */
volatile typedef struct
{
	uint32_t CR;                   /* Clock control register           - offset 0x00 */
	uint32_t PLLCFGR;              /* PLL configuration register       - offset 0x04 */
	uint32_t CFGR;                 /* RCC clock configuration register - offset 0x08 */
	uint32_t CIR;                  /* Clock configuration register     - offset 0x0C */
	uint32_t AHB1RSTR;             /* AHB1 peripheral reset register   - offset 0x10 */
	uint32_t AHB2RSTR;             /* AHB2 peripheral reset register   - offset 0x14 */
	uint32_t AHB3RSTR;             /* AHB3 peripheral reset register   - offset 0x18 */
	uint32_t RES0;                 /* Reserved                         - offset 0x1C */
	uint32_t APB1RSTR;             /* APB1 peripheral reset register   - offset 0x20 */
	uint32_t APB2RSTR;             /* APB2 peripheral reset register   - offset 0x24 */
	uint32_t RES1;                 /* Reserved                         - offset 0x28 */
	uint32_t RES2;                 /* Reserved                         - offset 0x2C */
	uint32_t AHB1ENR;              /* AHB1 peripheral clock enable     - offset 0x30 */
	uint32_t AHB2ENR;              /* AHB2 peripheral clock enable     - offset 0x34 */
	uint32_t RES4;                 /* Reserved                         - offset 0x38 */
	uint32_t RES5;                 /* Reserved                         - offset 0x3C */
	uint32_t APB1ENR;              /* APB1 peripheral clock enable     - offset 0x40 */
	uint32_t APB2ENR;              /* APB2 peripheral clock enable     - offset 0x44 */
	/* Rest of registers not utilized in lab 3 */
} RCC_TypeDef;

#define RCC_BASE     (0x40023800)
#define RCC          ((RCC_TypeDef*)RCC_BASE)

#define RCC_AHB1ENR_GPIOAEN     (0x01)
#define RCC_AHB1ENR_GPIOBEN     (0x02)
#define RCC_AHB1ENR_GPIOCEN     (0x04)
#define RCC_AHB1ENR_GPIODEN     (0x08)
#define RCC_AHB1ENR_GPIOEEN     (0x10)
#define RCC_AHB1ENR_DMA1        (0x00200000)
#define RCC_AHB1ENR_DMA2        (0x00400000)

#define RCC_AHB1RSTR_DMA1       (0x00200000)
#define RCC_AHB1RSTR_DMA2       (0x00400000)
#define RCC_APB1RSTR_USART2     (0x00020000)
#define RCC_APB1RSTR_USART3		(0x00040000)
#define RCC_APB1RSTR_UART4      (0x00080000)
#define RCC_APB1RSTR_UART5      (0x00100000)
#define RCC_APB1RSTR_SPI2       (0x00004000)
#define RCC_APB1RSTR_TIM2       (0x00000001)
#define RCC_APB1RSTR_TIM6       (0x00000010)
#define RCC_APB1RSTR_TIM7	    (0x00000020)
#define RCC_APB2RSTR_USART1     (0x00000010)
#define RCC_APB2RSTR_ADC1       (0x00000100)
#define RCC_APB2RSTR_SPI1       (0x00001000)

#define RCC_APB1ENR_TIM2        (0x01)
#define RCC_APB1ENR_TIM3		(0x02)
#define RCC_APB1ENR_TIM4        (0x04)
#define RCC_APB1ENR_TIM6        (0x10)
#define RCC_APB1ENR_TIM7        (0x20)
#define RCC_APB1ENR_SPI2        (0x00004000)
#define RCC_APB1ENR_USART2      (0x00020000)
#define RCC_APB1ENR_USART3		(0x00040000)
#define RCC_APB1ENR_UART4       (0x00080000)
#define RCC_APB1ENR_UART5       (0x00100000)

#define RCC_APB2ENR_USART1      (0x00000010)
#define RCC_APB2ENR_ADC1        (0x0100)
#define RCC_APB2ENR_SPI1        (0x1000)
#define RCC_APB2ENR_SYSCFGEN    (0x4000)
