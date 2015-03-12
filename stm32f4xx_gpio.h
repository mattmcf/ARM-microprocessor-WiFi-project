#pragma once

#include <stdint.h>

/* GPIO Registers, see the reference manual sections 7.4.X */
volatile typedef struct
{
	uint32_t MODER;                /* Mode register                    - offset 0x00 */
	uint32_t OTYPER;               /* Output type register             - offset 0x04 */
	uint32_t OSPEEDR;              /* Output speed register            - offset 0x08 */
	uint32_t PUPDR;                /* Port pull-up/pull-down register  - offset 0x0C */
	uint32_t IDR;                  /* Input data register              - offset 0x10 */
	uint32_t ODR;                  /* Output data register             - offset 0x14 */
	uint32_t BSRR;                 /* Bit set-reset register           - offset 0x18 */
	uint32_t LCKR;                 /* Port configuration lock register - offset 0x1C */
	uint32_t AFRL;                 /* Alternate function low register  - offset 0x20 */
	uint32_t AFRH;                 /* Alternate function high register - offset 0x24 */
} GPIO_TypeDef;

/*
 * GPIOA & GPIOD
 */
#define GPIOA_BASE   (0x40020000)  /* Base address of GPIOA peripheral */
#define GPIOA        ((GPIO_TypeDef*)GPIOA_BASE)
#define GPIOB_BASE   (0x40020400)  /* Base address of GPIOB peripheral */
#define GPIOB        ((GPIO_TypeDef*)GPIOB_BASE)
#define GPIOC_BASE   (0x40020800)  /* Base address of GPIOC peripheral */
#define GPIOC        ((GPIO_TypeDef*)GPIOC_BASE)
#define GPIOD_BASE   (0x40020C00)  /* Base address of GPIOD peripheral */
#define GPIOD        ((GPIO_TypeDef*)GPIOD_BASE)
#define GPIOE_BASE   (0x40021000)
#define GPIOE        ((GPIO_TypeDef*)GPIOE_BASE)

#define GPIOx_MODER_PIN1_MASK   (0xfffffff3)
#define GPIOx_MODER_PIN2_MASK   (0xffffffcf)
#define GPIOx_MODER_PIN3_MASK   (0xffffff3f)
#define GPIOx_MODER_PIN4_MASK   (0xfffffcff)
#define GPIOx_MODER_PIN5_MASK   (0xfffff3ff)
#define GPIOx_MODER_PIN6_MASK   (0xffffcfff)
#define GPIOx_MODER_PIN7_MASK   (0xffff3fff)
#define GPIOx_MODER_PIN8_MASK   (0xfffcffff)
#define GPIOx_MODER_PIN9_MASK   (0xfff3ffff)
#define GPIOx_MODER_PIN10_MASK  (0xffcfffff)
#define GPIOx_MODER_PIN11_MASK  (0xff3fffff)
#define GPIOx_MODER_PIN12_MASK  (0xfcffffff)
#define GPIOx_MODER_PIN13_MASK  (0xf3ffffff)
#define GPIOx_MODER_PIN14_MASK  (0xcfffffff)
#define GPIOx_MODER_PIN15_MASK  (0x3fffffff)
#define GPIOx_MODER_PIN1_GPOUT  (0x00000004)
#define GPIOx_MODER_PIN2_GPOUT  (0x00000010)
#define GPIOx_MODER_PIN3_GPOUT  (0x00000040)
#define GPIOx_MODER_PIN4_GPOUT  (0x00000100)
#define GPIOx_MODER_PIN5_GPOUT  (0x00000400)
#define GPIOx_MODER_PIN6_GPOUT  (0x00001000)
#define GPIOx_MODER_PIN8_GPOUT  (0x00010000)
#define GPIOx_MODER_PIN12_GPOUT (0x01000000)
#define GPIOx_MODER_PIN13_GPOUT (0x04000000)
#define GPIOx_MODER_PIN14_GPOUT (0x10000000)
#define GPIOx_MODER_PIN15_GPOUT (0x40000000)
#define GPIOx_MODER_PIN1_AF     (0x00000008)
#define GPIOx_MODER_PIN2_AF     (0x00000020)
#define GPIOx_MODER_PIN3_AF     (0x00000080)
#define GPIOx_MODER_PIN4_AF     (0x00000200)
#define GPIOx_MODER_PIN5_AF     (0x00000800)
#define GPIOx_MODER_PIN6_AF     (0x00002000)
#define GPIOx_MODER_PIN7_AF     (0x00008000)
#define GPIOx_MODER_PIN8_AF     (0x00020000)
#define GPIOx_MODER_PIN9_AF     (0x00080000)
#define GPIOx_MODER_PIN10_AF    (0x00200000)
#define GPIOx_MODER_PIN11_AF    (0x00800000)
#define GPIOx_MODER_PIN12_AF    (0x02000000)
#define GPIOx_MODER_PIN13_AF    (0x08000000)
#define GPIOx_MODER_PIN14_AF    (0x20000000)
#define GPIOx_MODER_PIN15_AF    (0x80000000)
#define GPIOx_MODER_PIN0_ANALOG (0x00000003)
#define GPIOx_MODER_PIN1_ANALOG (0x0000000C)
#define GPIOx_MODER_PIN2_ANALOG (0x00000030)
#define GPIOx_MODER_PIN3_ANALOG (0x000000C0)
#define GPIOx_MODER_PIN4_ANALOG (0x00000300)
#define GPIOx_MODER_PIN5_ANALOG (0x00000C00)
#define GPIOx_MODER_PIN6_ANALOG (0x00003000)
#define GPIOx_MODER_PIN7_ANALOG (0x0000C000)

#define GPIOx_OSPEEDR_PIN1_MASK   (0xfffffff3)
#define GPIOx_OSPEEDR_PIN2_MASK   (0xffffffcf)
#define GPIOx_OSPEEDR_PIN4_MASK   (0xfffffcff)
#define GPIOx_OSPEEDR_PIN5_MASK   (0xfffff3ff)
#define GPIOx_OSPEEDR_PIN6_MASK   (0xffffcfff)
#define GPIOx_OSPEEDR_PIN7_MASK   (0xffff3fff)
#define GPIOx_OSPEEDR_PIN12_MASK  (0xfcffffff)
#define GPIOx_OSPEEDR_PIN13_MASK  (0xf3ffffff)
#define GPIOx_OSPEEDR_PIN14_MASK  (0xcfffffff)
#define GPIOx_OSPEEDR_PIN15_MASK  (0x3fffffff)
#define GPIOx_OSPEEDR_PIN1_25MHZ  (0x00000004)
#define GPIOx_OSPEEDR_PIN2_25MHZ  (0x00000010)
#define GPIOx_OSPEEDR_PIN4_25MHZ  (0x00000100)
#define GPIOx_OSPEEDR_PIN5_25MHZ  (0x00000400)
#define GPIOx_OSPEEDR_PIN6_25MHZ  (0x00001000)
#define GPIOx_OSPEEDR_PIN7_25MHZ  (0x00004000)
#define GPIOx_OSPEEDR_PIN12_25MHZ (0x01000000)
#define GPIOx_OSPEEDR_PIN13_25MHZ (0x04000000)
#define GPIOx_OSPEEDR_PIN14_25MHZ (0x10000000)
#define GPIOx_OSPEEDR_PIN15_25MHZ (0x40000000)

#define GPIOx_AFRL_AFRL1_MASK   (0xffffff0f)
#define GPIOx_AFRL_AFRL2_MASK   (0xfffff0ff)
#define GPIOx_AFRL_AFRL3_MASK   (0xffff0fff)
#define GPIOx_AFRL_AFRL4_MASK   (0xfff0ffff)
#define GPIOx_AFRL_AFRL5_MASK   (0xff0fffff)
#define GPIOx_AFRL_AFRL6_MASK   (0xf0ffffff)
#define GPIOx_AFRL_AFRL7_MASK   (0x0fffffff)
#define GPIOx_AFRL_AFRL1_AF8    (0x00000080)
#define GPIOx_AFRL_AFRL2_AF7    (0x00000700)
#define GPIOx_AFRL_AFRL2_AF8    (0x00000800)
#define GPIOx_AFRL_AFRL3_AF7    (0x00007000)
#define GPIOx_AFRL_AFRL4_AF7    (0x00070000)
#define GPIOx_AFRL_AFRL5_AF5    (0x00500000)
#define GPIOx_AFRL_AFRL5_AF7    (0x00700000)
#define GPIOx_AFRL_AFRL6_AF5    (0x05000000)
#define GPIOx_AFRL_AFRL6_AF7    (0x07000000)
#define GPIOx_AFRL_AFRL7_AF5    (0x50000000)

#define GPIOx_AFRH_AFRH8_MASK   (0xfffffff0)
#define GPIOx_AFRH_AFRH9_MASK   (0xffffff0f)
#define GPIOx_AFRH_AFRH10_MASK  (0xfffff0ff)
#define GPIOx_AFRH_AFRH11_MASK  (0xffff0fff)
#define GPIOx_AFRH_AFRH12_MASK  (0xfff0ffff)
#define GPIOx_AFRH_AFRH13_MASK  (0xff0fffff)
#define GPIOx_AFRH_AFRH14_MASK  (0xf0ffffff)
#define GPIOx_AFRH_AFRH15_MASK  (0x0fffffff)
#define GPIOx_AFRH_AFRH8_AF7	(0x00000007)
#define GPIOx_AFRH_AFRH9_AF7    (0x00000070)
#define GPIOx_AFRH_AFRH10_AF7   (0x00000700)
#define GPIOx_AFRH_AFRH12_AF2   (0x00020000)
#define GPIOx_AFRH_AFRH13_AF2   (0x00200000)
#define GPIOx_AFRH_AFRH13_AF5   (0x00500000)
#define GPIOx_AFRH_AFRH14_AF2   (0x02000000)
#define GPIOx_AFRH_AFRH14_AF5   (0x05000000)
#define GPIOx_AFRH_AFRH15_AF2   (0x20000000)
#define GPIOx_AFRH_AFRH15_AF5   (0x50000000)

#define GPIOx_PUPDR_PUPDR3_MASK  (0x000000C0)
#define GPIOx_PUPDR_PUPDR3_UP    (0x00000040)
#define GPIOx_PUPDR_PUPDR11_MASK (0x00C00000)
#define GPIOx_PUPDR_PUPDR11_UP   (0x00400000)

#define GPIOx_IDR_PIN1_MASK		(0x01)

#define GPIOx_BSRR_PIN_6_SET     (0x00000040)
#define GPIOx_BSRR_PIN_6_RESET   (0x00400000)
#define GPIOx_BSRR_PIN_8_SET     (0x00000100)
#define GPIOx_BSRR_PIN_8_RESET   (0x01000000)
#define GPIOx_BSRR_PIN_12_SET    (0x00001000)
#define GPIOx_BSRR_PIN_12_RESET  (0x10000000)

#define GPIOx_PIN_8              (0x0100)
#define GPIOx_PIN_11             (0x0800)
