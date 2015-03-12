/*
 * init.S - Vector table, reset_handler, generic interrupt handlers and C startup
 *
 * Target: STM32F4-Discovery w/ STM32F407VGT6 processor,
 *         ROM = 1M   @ 0x08000000
 *         RAM = 192k @ 0x20000000
 *
 */
	.syntax unified   			/* Use unified style assembly syntax */
	.thumb            			/* Cortex-M3 only supports Thumb code */

	/*
	 * Stack size is defined here.  Actual location is set in the
	 * linker script (based on __stack_size, below).  Stack size must
	 * be aligned to a 64-bit word boundary.
	 *
	 * NOTE: unused RAM is allocated to the heap, and described by
	 * symbols __heap_start and __heap_end, also set in the linker
	 * script.
	 */
	.equ __stack_size, 0x0800   /* 2kb stack */
	.global __stack_size        /* make available to the linker */

	/*
	 * FULL STM32F40x VECTOR TABLE - see Table 43 in Reference Manual pp 248
	 */
	.section vectors
	/*
	 * System Handlers for Exceptions
	 */
	/*    HANDLER                      POS. PRI. ADDR. EXCEPTION DESCRIPTION           */
	.word __stack_top                /*      -   0000  Stack Top (from linker script)  */
	.word reset_handler              /*      -3  0004  Called on system power-on/reset */
	.word NMI_handler                /*      -2  0008  Non-maskable interrupts         */
	.word fault_handler              /*      -1  000C  All class of faults             */
	.word mem_manage_handler         /*       0  0010  Memory Management               */
	.word bus_fault_handler          /*       1  0014  Pre-fetch / memory access fault */
	.word usage_fault_handler        /*       2  0018  Undefined instructions/bad state*/
	.word 0                          /*       -  001C  <reserved>                      */
	.word 0                          /*       -  0020  <reserved>                      */
	.word 0                          /*       -  0024  <reserved>                      */
	.word 0                          /*       -  0028  <reserved>                      */
	.word svcall_handler             /*       3  002C  System service call via SWI     */
	.word debug_handler              /*       4  0030  Debug Monitor                   */
	.word 0                          /*       -  0034  <reserved>                      */
	.word pendsv_handler             /*       5  0038  Pendable request for system svc.*/
	.word systick_handler            /*       6  003C  System tick timer               */
	/*
	 * Peripheral Handlers for Interrupts
	 */
	/*    HANDLER                      POS. PRI. ADDR. INTERRUPT DESCRIPTION           */
	.word WWDG_handler               /*   0   7  0040  Window watchdog                 */
	.word PVD_handler                /*   1   8  0044  PVD through EXTI line detection */
	.word TAMP_STAMP_handler         /*   2   9  0048  Tamper and TimeStamp via EXTI   */
	.word RTC_WKUP_handler           /*   3  10  004C  RTC Wakeup via EXTI             */
	.word FLASH_handler              /*   4  11  0050  Flash global interrupt          */
	.word RCC_handler                /*   5  12  0054  RCC global interrupt            */
	.word EXTI0_handler              /*   6  13  0058  EXTI Line 0 interrupt           */
	.word EXTI1_handler              /*   7  14  005C  EXTI Line 1 interrupt           */
	.word EXTI2_handler              /*   8  15  0060  EXTI Line 2 interrupt           */
	.word EXTI3_handler              /*   9  16  0064  EXTI Line 3 interrupt           */
	.word EXTI4_handler              /*  10  17  0068  EXTI Line 4 interrupt           */
	.word DMA1_stream0_handler       /*  11  18  006C  DMA 1 Stream 0 global interrupt */
	.word DMA1_stream1_handler       /*  12  19  0070  DMA 1 Stream 1 global interrupt */
	.word DMA1_stream2_handler       /*  13  20  0074  DMA 1 Stream 2 global interrupt */
	.word DMA1_stream3_handler       /*  14  21  0078  DMA 1 Stream 3 global interrupt */
	.word DMA1_stream4_handler       /*  15  22  007C  DMA 1 Stream 4 global interrupt */
	.word DMA1_stream5_handler       /*  16  23  0080  DMA 1 Stream 5 global interrupt */
	.word DMA1_stream6_handler       /*  17  24  0084  DMA 1 Stream 6 global interrupt */
	.word ADC_handler                /*  18  25  0088  Analog to digital converters 1-3*/
	.word CAN1_TX_handler            /*  19  26  008C  CAN1 transmit interrupts        */
	/*    HANDLER                      POS. PRI. ADDR. INTERRUPT DESCRIPTION           */
	.word CAN1_RX0_handler           /*  20  27  0090  CAN1 RX0 interrupts             */
	.word CAN1_RX1_handler           /*  21  28  0094  CAN1 RX1 interrupts             */
	.word CAN1_SCE_handler           /*  22  29  0098  CAN1 SCE interrupts             */
	.word EXTI9_5_handler            /*  23  30  009C  EXTI line[9:5] interrupts       */
	.word TIM1_BRK_TIM9_handler      /*  24  31  00A0  TIM 1 Break & TIM 9 Global Ints */
	.word TIM1_UP_TIM10_handler      /*  25  32  00A4  TIM1 Update & TIM 10 Global     */
	.word TIM1_TRG_COM_TIM11_handler /*  26  33  00A8  TIM1 Trigger & Comm, TIM 11 Glbl*/
	.word TIM1_CC_handler            /*  27  34  00AC  TIM1 Capture & Compare          */
	.word TIM2_handler               /*  28  35  00B0  TIM2 global                     */
	.word TIM3_handler               /*  29  36  00B4  TIM3 global                     */
	.word TIM4_handler               /*  30  37  00B8  TIM4 global                     */
	.word I2C1_EV_handler            /*  31  38  00BC  I2C1 event interrupt            */
	.word I2C1_ER_handler            /*  32  39  00C0  I2C1 error interrupt            */
	.word I2C2_EV_handler            /*  33  40  00C4  I2C2 event interrupt            */
	.word I2C2_ER_handler            /*  34  41  00C8  I2C2 error interrupt            */
	.word SPI1_handler               /*  35  42  00CC  SPI1 global interrupt           */
	.word SPI2_handler               /*  36  43  00D0  SPI2 global interrupt           */
	.word USART1_handler             /*  37  44  00D4  USART1 global interrupt         */
	.word USART2_handler             /*  38  45  00D8  USART2 global interrupt         */
	.word USART3_handler             /*  39  46  00DC  USART3 global interrupt         */
	/*    HANDLER                      POS. PRI. ADDR. INTERRUPT DESCRIPTION           */
	.word EXTI15_10_handler          /*  40  47  00E0  EXTI Line[15:10] interrupts     */
	.word RTC_alarm_handler          /*  41  48  00E4  RTC Alarms (A&B) via EXTI       */
	.word OTG_FS_WKUP_handler        /*  42  49  00E8  USB On-the-Go FS Wakeup via EXTI*/
	.word TIM8_BRK_TIM12_handler     /*  43  50  00EC  TIM8 Break & TIM12 global       */
	.word TIM8_UP_TIM13_handler      /*  44  51  00F0  TIM8 Update & TIM13 global      */
	.word TIM8_TRG_COM_TIM14_handler /*  45  52  00F4  TIM8 Trigger & Comm, TIM14 Glbl */
	.word TIM8_CC_handler            /*  46  53  00F8  TIM8 Capture Compare interrupt  */
 	.word DMA1_stream7_handler       /*  47  54  00FC  DMA 1 Stream 7 global interrupt */
 	.word FSMC_handler               /*  48  55  0100  Flexible static memory control  */
 	.word SDIO_handler               /*  49  56  0104  SDIO global interrupt           */
 	.word TIM5_handler               /*  50  57  0108  TIM5 global interrupt           */
 	.word SPI3_handler               /*  51  58  010C  SPI3 global handler             */
 	.word UART4_handler              /*  52  59  0110  UART4 global interrupt          */
 	.word UART5_handler              /*  53  60  0114  UART5 global interrupt          */
 	.word TIM6_DAC_handler           /*  54  61  0118  TIM6 global, DAC1 & 2 underrun  */
 	.word TIM7_handler               /*  55  62  011C  TIM7 global interrupt           */
 	.word DMA2_stream0_handler       /*  56  63  0120  DMA 2 Stream 0 global interrupt */
 	.word DMA2_stream1_handler       /*  57  64  0124  DMA 2 Stream 1 global interrupt */
 	.word DMA2_stream2_handler       /*  58  65  0128  DMA 2 Stream 2 global interrupt */
 	.word DMA2_stream3_handler       /*  59  66  012C  DMA 2 Stream 3 global interrupt */
	/*    HANDLER                      POS. PRI. ADDR. INTERRUPT DESCRIPTION           */
 	.word DMA2_stream4_handler       /*  60  67  0130  DMA 2 Stream 4 global interrupt */
 	.word ETH_handler                /*  61  68  0134  Ethernet global interrupt       */
 	.word ETH_WKUP_handler           /*  62  69  0138  Ethernet wakeup through EXTI    */
 	.word CAN2_TX_handler            /*  63  70  013C  CAN2 TX interrupts              */
 	.word CAN2_RX0_handler           /*  64  71  0140  CAN2 RX0 interrupt              */
 	.word CAN2_RX1_handler           /*  65  72  0144  CAN2 RX1 interrupt              */
 	.word CAN2_SCE_handler           /*  66  73  0148  CAN2 SCE interrupt              */
 	.word OTG_FS_handler             /*  67  74  014C  USB On-the-Go FS global int.    */
 	.word DMA2_stream5_handler       /*  68  75  0150  DMA 2 Stream 5 global interrupt */
 	.word DMA2_stream6_handler       /*  69  76  0154  DMA 2 Stream 6 global interrupt */
 	.word DMA2_stream7_handler       /*  70  77  0158  DMA 2 Stream 7 global interrupt */
 	.word USART6_handler             /*  71  78  015C  USART6 global interupt          */
 	.word I2C3_EV_handler            /*  72  79  0160  I2C3 event interrupt            */
 	.word I2C3_ER_handler            /*  73  80  0164  I2C3 error interrupt            */
 	.word OTG_HS_EP1_OUT_handler     /*  74  81  0168  USB On-the-Go HS End Point 1 Out*/
 	.word OTG_HS_EP1_IN_handler      /*  75  82  016C  USB On-the-Go HS End Point 1 In */
 	.word OTG_HS_WKUP_handler        /*  76  83  0170  USB On-the-Go HS Wakeup (EXTI)  */
 	.word OTG_HS_handler             /*  77  84  0174  USB On-the-Go HS global int     */
 	.word DCMI_handler               /*  78  85  0178  DCMI global interrupt           */
 	.word CRYP_handler               /*  79  86  017C  CRYP crypto global interrupt    */
 	.word HASH_RNG_handler           /*  80  87  0180  Hash and RNG global interrupt   */
 	.word FPU_handler                /*  81  88  0184  FPU global interrupt            */

	/*
	 * Provide hints to the linker for routines in the vector table - target addr must
	 * end in '1' to indicate THUMB mode, not ARM mode...
	 */
	.type reset_handler, %function
	.type NMI_handler, %function
	.type fault_handler, %function
	.type mem_manage_handler, %function
	.type bus_fault_handler, %function
	.type usage_fault_handler, %function
	.type svcall_handler, %function
	.type debug_handler, %function
	.type pendsv_handler, %function
	.type systick_handler, %function
	.type WWDG_handler, %function
	.type PVD_handler, %function
	.type TAMP_STAMP_handler, %function
	.type RTC_WKUP_handler, %function
	.type FLASH_handler, %function
	.type RCC_handler, %function
	.type EXTI0_handler, %function
	.type EXTI1_handler, %function
	.type EXTI2_handler, %function
	.type EXTI3_handler, %function
	.type EXTI4_handler, %function
	.type DMA1_stream0_handler, %function
	.type DMA1_stream1_handler, %function
	.type DMA1_stream2_handler, %function
	.type DMA1_stream3_handler, %function
	.type DMA1_stream4_handler, %function
	.type DMA1_stream5_handler, %function
	.type DMA1_stream6_handler, %function
	.type ADC_handler, %function
	.type CAN1_TX_handler, %function
	.type CAN1_RX0_handler, %function
	.type CAN1_RX1_handler, %function
	.type CAN1_SCE_handler, %function
	.type EXTI9_5_handler, %function
	.type TIM1_BRK_TIM9_handler, %function
	.type TIM1_UP_TIM10_handler, %function
	.type TIM1_TRG_COM_TIM11_handler, %function
	.type TIM1_CC_handler, %function
	.type TIM2_handler, %function
	.type TIM3_handler, %function
	.type TIM4_handler, %function
	.type I2C1_EV_handler, %function
	.type I2C1_ER_handler, %function
	.type I2C2_EV_handler, %function
	.type I2C2_ER_handler, %function
	.type SPI1_handler, %function
	.type SPI2_handler, %function
	.type USART1_handler, %function
	.type USART2_handler, %function
	.type USART3_handler, %function
	.type EXTI15_10_handler, %function
	.type RTC_alarm_handler, %function
	.type OTG_FS_WKUP_handler, %function
	.type TIM8_BRK_TIM12_handler, %function
	.type TIM8_UP_TIM13_handler, %function
	.type TIM8_TRG_COM_TIM14_handler, %function
	.type TIM8_CC_handler, %function
 	.type DMA1_stream7_handler, %function
 	.type FSMC_handler, %function
 	.type SDIO_handler, %function
 	.type TIM5_handler, %function
 	.type SPI3_handler, %function
 	.type UART4_handler, %function
 	.type UART5_handler, %function
 	.type TIM6_DAC_handler, %function
 	.type TIM7_handler, %function
 	.type DMA2_stream0_handler, %function
 	.type DMA2_stream1_handler, %function
 	.type DMA2_stream2_handler, %function
 	.type DMA2_stream3_handler, %function
 	.type DMA2_stream4_handler, %function
 	.type ETH_handler, %function
 	.type ETH_WKUP_handler, %function
 	.type CAN2_TX_handler, %function
 	.type CAN2_RX0_handler, %function
 	.type CAN2_RX1_handler, %function
 	.type CAN2_SCE_handler, %function
 	.type OTG_FS_handler, %function
 	.type DMA2_stream5_handler, %function
 	.type DMA2_stream6_handler, %function
 	.type DMA2_stream7_handler, %function
 	.type USART6_handler, %function
 	.type I2C3_EV_handler, %function
 	.type I2C3_ER_handler, %function
 	.type OTG_HS_EP1_OUT_handler, %function
 	.type OTG_HS_EP1_IN_handler, %function
 	.type OTG_HS_WKUP_handler, %function
 	.type OTG_HS_handler, %function
 	.type DCMI_handler, %function
 	.type CRYP_handler, %function
 	.type HASH_RNG_handler, %function
 	.type FPU_handler, %function

	/*
	 * Only weak binding to the default handler functions below - if the same routine
	 * is declared elsewhere in the binary then prefer that routine.
	 */
	.weak reset_handler
	.weak NMI_handler
	.weak fault_handler
	.weak mem_manage_handler
	.weak bus_fault_handler
	.weak usage_fault_handler
	.weak svcall_handler
	.weak debug_handler
	.weak pendsv_handler
	.weak systick_handler
	.weak WWDG_handler
	.weak PVD_handler
	.weak TAMP_STAMP_handler
	.weak RTC_WKUP_handler
	.weak FLASH_handler
	.weak RCC_handler
	.weak EXTI0_handler
	.weak EXTI1_handler
	.weak EXTI2_handler
	.weak EXTI3_handler
	.weak EXTI4_handler
	.weak DMA1_stream0_handler
	.weak DMA1_stream1_handler
	.weak DMA1_stream2_handler
	.weak DMA1_stream3_handler
	.weak DMA1_stream4_handler
	.weak DMA1_stream5_handler
	.weak DMA1_stream6_handler
	.weak ADC_handler
	.weak CAN1_TX_handler
	.weak CAN1_RX0_handler
	.weak CAN1_RX1_handler
	.weak CAN1_SCE_handler
	.weak EXTI9_5_handler
	.weak TIM1_BRK_TIM9_handler
	.weak TIM1_UP_TIM10_handler
	.weak TIM1_TRG_COM_TIM11_handler
	.weak TIM1_CC_handler
	.weak TIM2_handler
	.weak TIM3_handler
	.weak TIM4_handler
	.weak I2C1_EV_handler
	.weak I2C1_ER_handler
	.weak I2C2_EV_handler
	.weak I2C2_ER_handler
	.weak SPI1_handler
	.weak SPI2_handler
	.weak USART1_handler
	.weak USART2_handler
	.weak USART3_handler
	.weak EXTI15_10_handler
	.weak RTC_alarm_handler
	.weak OTG_FS_WKUP_handler
	.weak TIM8_BRK_TIM12_handler
	.weak TIM8_UP_TIM13_handler
	.weak TIM8_TRG_COM_TIM14_handler
	.weak TIM8_CC_handler
 	.weak DMA1_stream7_handler
 	.weak FSMC_handler
 	.weak SDIO_handler
 	.weak TIM5_handler
 	.weak SPI3_handler
 	.weak UART4_handler
 	.weak UART5_handler
 	.weak TIM6_DAC_handler
 	.weak TIM7_handler
 	.weak DMA2_stream0_handler
 	.weak DMA2_stream1_handler
 	.weak DMA2_stream2_handler
 	.weak DMA2_stream3_handler
 	.weak DMA2_stream4_handler
 	.weak ETH_handler
 	.weak ETH_WKUP_handler
 	.weak CAN2_TX_handler
 	.weak CAN2_RX0_handler
 	.weak CAN2_RX1_handler
 	.weak CAN2_SCE_handler
 	.weak OTG_FS_handler
 	.weak DMA2_stream5_handler
 	.weak DMA2_stream6_handler
 	.weak DMA2_stream7_handler
 	.weak USART6_handler
 	.weak I2C3_EV_handler
 	.weak I2C3_ER_handler
 	.weak OTG_HS_EP1_OUT_handler
 	.weak OTG_HS_EP1_IN_handler
 	.weak OTG_HS_WKUP_handler
 	.weak OTG_HS_handler
 	.weak DCMI_handler
 	.weak CRYP_handler
 	.weak HASH_RNG_handler
 	.weak FPU_handler

 	/* Trap unhandled exceptions/interrupts to a default handler */
NMI_handler:
fault_handler:
mem_manage_handler:
bus_fault_handler:
usage_fault_handler:
svcall_handler:
debug_handler:
pendsv_handler:
systick_handler:
WWDG_handler:
PVD_handler:
TAMP_STAMP_handler:
RTC_WKUP_handler:
FLASH_handler:
RCC_handler:
EXTI0_handler:
EXTI1_handler:
EXTI2_handler:
EXTI3_handler:
EXTI4_handler:
DMA1_stream0_handler:
DMA1_stream1_handler:
DMA1_stream2_handler:
DMA1_stream3_handler:
DMA1_stream4_handler:
DMA1_stream5_handler:
DMA1_stream6_handler:
ADC_handler:
CAN1_TX_handler:
CAN1_RX0_handler:
CAN1_RX1_handler:
CAN1_SCE_handler:
EXTI9_5_handler:
TIM1_BRK_TIM9_handler:
TIM1_UP_TIM10_handler:
TIM1_TRG_COM_TIM11_handler:
TIM1_CC_handler:
TIM2_handler:
TIM3_handler:
TIM4_handler:
I2C1_EV_handler:
I2C1_ER_handler:
I2C2_EV_handler:
I2C2_ER_handler:
SPI1_handler:
SPI2_handler:
USART1_handler:
USART2_handler:
USART3_handler:
EXTI15_10_handler:
RTC_alarm_handler:
OTG_FS_WKUP_handler:
TIM8_BRK_TIM12_handler:
TIM8_UP_TIM13_handler:
TIM8_TRG_COM_TIM14_handler:
TIM8_CC_handler:
DMA1_stream7_handler:
FSMC_handler:
SDIO_handler:
TIM5_handler:
SPI3_handler:
UART4_handler:
UART5_handler:
TIM6_DAC_handler:
TIM7_handler:
DMA2_stream0_handler:
DMA2_stream1_handler:
DMA2_stream2_handler:
DMA2_stream3_handler:
DMA2_stream4_handler:
ETH_handler:
ETH_WKUP_handler:
CAN2_TX_handler:
CAN2_RX0_handler:
CAN2_RX1_handler:
CAN2_SCE_handler:
OTG_FS_handler:
DMA2_stream5_handler:
DMA2_stream6_handler:
DMA2_stream7_handler:
USART6_handler:
I2C3_EV_handler:
I2C3_ER_handler:
OTG_HS_EP1_OUT_handler:
OTG_HS_EP1_IN_handler:
OTG_HS_WKUP_handler:
OTG_HS_handler:
DCMI_handler:
CRYP_handler:
HASH_RNG_handler:
FPU_handler:
default_handler:
	b default_handler

	/* Generic code section */
	.text

/*
 * reset_handler:
 *
 * This is the code we want to run out of reset/on start-up
 */
reset_handler:
	/* Global interrupt disable - power on/reset default */
	cpsid i

	/*
	 * Initialize ".data" section by copying from flash to RAM
	 */
data_copy_init:
	ldr r0, =__text_end      /* Where .data starts in flash memory */
	ldr r1, =__data_start    /* Where .data starts in RAM memory */
	ldr r2, =__data_bytes    /* How many 8-bit bytes to copy */
	add r2, r1, r2           /* r2 <- __data_start + __data_bytes = __data_end */
data_copy:
	cmp  r1, r2
	beq bss_zero_init
	ldrb r3, [r0]
	strb r3, [r1]
	add r0, r0, #1
	add r1, r1, #1
	b data_copy

	/*
	 * Zero out ".bss" section in RAM
	 */
bss_zero_init:
	ldr r0, =__bss_start
	ldr r1, =__bss_bytes
	add r1, r0, r1           /* r1 <= __bss_start + __bss_bytes = __bss_end */
	mov r2, #0
bss_zero:
	cmp r0, r1
	beq jump_to_main
	strb r2, [r0]
	add r0, r0, #1
	b bss_zero

jump_to_main:
	/* pass control to main() */
	b main

	.end
