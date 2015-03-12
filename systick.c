/*
 * Systick.c - routines for initialization and handling of systick interrupt
 */

#include "systick.h"
#include "stm32f4xx_systick.h"

static void(*callback_fn)(void);

void __attribute__ ((interrupt)) systick_handler(void)
{
	/* Call the user-specified callback function */
	if( callback_fn ){
		callback_fn();
	}

}

/*
 * Sets systick up for a 1 second tick
 */
void systick_init(void(*fn)(void))
{
	callback_fn = fn;
	SYSTICK->CTRL = (uint32_t) 0;
	SYSTICK->LOAD = 16000000;
	SYSTICK->VAL = (uint32_t) 0;
	SYSTICK->CTRL = 0x00000007;
}

/*
 * systick_start( uint32_t secs);
 *
 * loads and then starts systick timer with argument in seconds
 *
 * maybe it's better to leave reload value at zero and then put current value at SECs?
 */
void systick_start( uint32_t secs)
{
	// using system clock / 8 = 16,000,000 / 8 = 2,000,000
	uint32_t towait = secs * 2000000;

	SYSTICK->CTRL = (uint32_t) 0;
	SYSTICK->LOAD = towait;
	SYSTICK->VAL = (uint32_t) 0;
	SYSTICK->CTRL = (uint32_t) 7;	// use system clock divided by 8

	/*
	SYSTICK->CTRL = (uint32_t) 0;
	SYSTICK->LOAD = towait;
	SYSTICK->VAL = (uint32_t) 0;
	SYSTICK->CTRL = 0x00000007;
	*/
}

/*
 * void systick_stop( void );
 *
 * disables systick timer
 */
void systick_stop( void )
{
	SYSTICK->CTRL = (uint32_t) 0;
	SYSTICK->VAL = (uint32_t) 0;
}
