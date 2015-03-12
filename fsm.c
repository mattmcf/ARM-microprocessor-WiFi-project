#include <fsm.h>

#include <LED.h>
#include <mutex.h>
#include <USART2.h>
#include "ping.h"

#define MY_ID 18
extern int track_id;
extern Update_req_t update;

static uint32_t fsm_mutex;

static state_t state = STATE_RESET;

extern Ping_t received;

extern Update_resp_t received_update;

void fsm_init(void)
{
	mutex_init(&fsm_mutex);
	while( fsm_lock() != FSM_LOCK_ACQUIRED );
	fsm_set_state(CMDmode);
	fsm_unlock();
}

uint8_t fsm_lock(void)
{
	uint8_t retval = FSM_LOCK_FAILED;

	if( mutex_lock(&fsm_mutex) == MUTEX_LOCKED )
		retval = FSM_LOCK_ACQUIRED;

	return retval;
}

void fsm_unlock(void)
{
	mutex_unlock(&fsm_mutex);
}

state_t fsm_get_state(void)
{
	return state;
}

void fsm_set_state(state_t new_state)
{
	/* only do this if the FSM has been locked! */
	if( fsm_mutex == MUTEX_LOCKED )
	{
		state = new_state;

		switch( state )
		{
		case STATE_RESET:
		default:

			/* Display usage information */
			USART2_putstr("FSM in Reset\r\n");

			/* Turn on all of the LEDs */
			LED_update( LED_ORANGE_ON | LED_RED_ON | LED_BLUE_ON | LED_GREEN_ON );

			break;

		case CMDmode:
			USART2_putstr("Entering manual mode\n\r");
			LED_update( LED_ORANGE_OFF | LED_RED_OFF | LED_BLUE_ON | LED_GREEN_OFF );
			break;

		case PINGmode:
			USART3_putstr("exit\r");
			waitmsn(500);
			resetPing(&received);
			LED_update( LED_ORANGE_ON | LED_RED_OFF | LED_BLUE_OFF | LED_GREEN_OFF );
			break;

		case UPDATEmodeA:
			LED_update( LED_ORANGE_OFF | LED_RED_OFF | LED_BLUE_OFF | LED_GREEN_ON );
			printUpdateReq( &update );
			sendUpdate( &update );
			break;

		case UPDATEmodeB:
			LED_update( LED_ORANGE_OFF | LED_RED_OFF | LED_BLUE_OFF | LED_GREEN_ON );
			break;

		case WAITb:
			LED_update( LED_ORANGE_OFF | LED_RED_OFF | LED_BLUE_OFF | LED_GREEN_ON );
			printUpdateResponse( &received_update );
			servo_mapADC( received_update.values[MY_ID] );
			resetUpdate(&received_update);
			ADC_start();
			break;

		case GetID:
			resetCharIDBuf();
			waitmsn(500);
			USART2_putstr("\n\rSend an id (00-30) to position servo with: \n\r");
			LED_update( LED_ORANGE_OFF | LED_RED_OFF | LED_BLUE_OFF | LED_GREEN_ON );
			break;

		case UPDATE2modeA:
			LED_update( LED_ORANGE_OFF | LED_RED_OFF | LED_BLUE_OFF | LED_GREEN_ON );
			printUpdateReq( &update );
			sendUpdate( &update );
			break;

		case UPDATE2modeB:
			//resetUpdate(&received_update);
			LED_update( LED_ORANGE_OFF | LED_RED_OFF | LED_BLUE_OFF | LED_GREEN_ON );
			break;

		case WAIT2b:
			LED_update( LED_ORANGE_OFF | LED_RED_OFF | LED_BLUE_OFF | LED_GREEN_ON );
			printUpdateResponse( &received_update );
			servo_mapADC( received_update.values[track_id]);
			resetUpdate(&received_update);
			ADC_start();
			break;
		}
	}
}
