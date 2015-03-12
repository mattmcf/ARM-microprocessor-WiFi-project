#include "fsm.h"
#include "USART2.h"
#include "userbutton.h"
#include "wait.h"
#include "servo.h"
#include "timer.h"
#include "LED.h"
#include "ping.h"
#include "ADC.h"
#include "printHex.h"

#define CLOSED 1600
#define OPEN 800
#define DEBOUNCE 25		// milliseconds

#define ID_BUF_SIZE 50	// chars

#define MY_ID	18

// globally visible ping structures
Ping_t ping;
Ping_t received;
int rec_count;

Update_req_t update;
Update_resp_t received_update;
int update_count;

char id_buf[ID_BUF_SIZE];
int id_count;
int track_id;


void addCharIDBuf( uint8_t byte){
	if( id_count < ID_BUF_SIZE ){
		*(id_buf + id_count) = (char) byte;
		id_count++;
	}
}

void resetCharIDBuf( void ){
	int i;
	for( i = 0; i < ID_BUF_SIZE; i++){
		*(id_buf + i) = '\0';
	}
	id_count = 0;
}

/*
 * checks if ID is a valid string ("00" - "30")
 *
 * returns 1 on success
 * else 0
 */
int checkID(){
	int count = 0;
	int status = 0;
	int i = 0;
	char d1 = *(id_buf + 0);
	char d2 = *(id_buf + 1);
	char d3 = *(id_buf + 2);

	if( d3 != '\r' )
		return 0;
	else if( d1 > '3' || d1 < '0')
		return 0;
	else if( d2 > '9' || d2 < '0')
		return 0;

	if( d1 == '3' && d2 != '0')
		return 0;

	return 1;
}

void setTrackID(){
	// translates characters in IDbuffer to a decimal
	char d1 = id_buf[0];
	char d2 = id_buf[1];

	switch( d1 )
	{
	case '3':
		track_id = 30;
		break;
	case '2':
		track_id = 20;
		break;
	case '1':
		track_id = 10;
		break;
	case '0':
	default:
		track_id = 0;
		break;
	}

	switch( d2 )
	{
	case '9':
		track_id += 9;
		break;
	case '8':
		track_id += 8;
		break;
	case '7':
		track_id += 7;
		break;
	case '6':
		track_id += 6;
		break;
	case '5':
		track_id += 5;
		break;
	case '4':
		track_id += 4;
		break;
	case '3':
		track_id += 3;
		break;
	case '2':
		track_id += 2;
		break;
	case '1':
		track_id += 1;
		break;
	default:
		break;
	}
}

/*
 * called when ADC finishes conversion
 *
 * prints ADC data to console
 */
void ADC_callback_fn( uint16_t * buffer, uint32_t size)
{
	int max = 0x000;
	int min = 0xFFF;
	int sum = 0;
	int avg;
	int i;

	if( fsm_lock() == FSM_LOCK_ACQUIRED)
	{
		switch( fsm_get_state() )
		{
		case WAITb:
			//USART2_putstr("Printing data buffer: \n\r");
			for( i = 0; i < size; i++){
				sum += buffer[i];
				if( buffer[i] < min )
					min = buffer[i];
				if( buffer[i] > max )
					max = buffer[i];
			}
			avg = sum / size;

			USART2_putstr("\n\r\n\r");
			USART2_putstr("ADC DATA -- avg: ");
			printHex(avg);
			USART2_putstr(" max: ");
			printHex(max);
			USART2_putstr(" min: ");
			printHex(min);
			USART2_putstr("\n\r");

			// set update req value to avg
			update.value = avg;
			//printUpdateReq( &update );
			fsm_set_state(UPDATEmodeA);

			//sendUpdate( &update );
			break;
		case WAIT2b:
		//case UPDATE2modeB:
			//USART2_putstr("Printing data buffer: \n\r");
			for( i = 0; i < size; i++){
				sum += buffer[i];
				if( buffer[i] < min )
					min = buffer[i];
				if( buffer[i] > max )
					max = buffer[i];
			}
			avg = sum / size;

			USART2_putstr("\n\r\n\r");
			USART2_putstr("ADC DATA -- avg: ");
			printHex(avg);
			USART2_putstr(" max: ");
			printHex(max);
			USART2_putstr(" min: ");
			printHex(min);
			USART2_putstr("\n\r");

			// set update req value to avg
			update.value = avg;
			//printUpdateReq( &update );
			fsm_set_state( UPDATE2modeA);
			//sendUpdate( &update );
			break;
		default:
			USART2_putstr("adc returned\n\r");
			break;
		}
		state_t st = fsm_get_state();
		fsm_unlock();
	}

}

void USART2_callback_fn(uint8_t byte)
{

	if( fsm_lock() == FSM_LOCK_ACQUIRED)
	{
		switch( fsm_get_state() )
		{
		case GetID:
			addCharIDBuf( byte );
			if( (char) byte == '\r' ) {
				USART2_putstr(id_buf);
				USART2_putstr("\n\r");
				if( checkID() ){
					USART2_putstr("Tracking ID Number for servo position: ");
					USART2_putstr(id_buf);
					USART2_putstr("\n\r");
					setTrackID();
					resetCharIDBuf();
					resetUpdate(&received_update);
					fsm_set_state(UPDATE2modeA);
				} else {
					USART2_putstr("ID was invalid. Send two numbers for ID (00 - 30)\n\r");
					resetCharIDBuf();
				}
			}
			break;
		case CMDmode:
			USART3_putchar(byte);
			break;
		default:
			//USART3_putchar(byte);
			break;
		}
		fsm_unlock();
	}
}

void USART3_callback_fn(uint8_t byte)
{
	//USART2_putchar(byte);

	if( fsm_lock() == FSM_LOCK_ACQUIRED )
	{
		switch( fsm_get_state() )
		{
		case CMDmode:
			USART2_putchar(byte);
			break;

		//case PINGlisten:
		case PINGmode:
			if( ping_lock() == PING_LOCK_ACQUIRED ){
				addByte( &received, byte );
				ping_unlock();
			}
			break;

		case UPDATEmodeA:
		case UPDATEmodeB:
		case WAITb:
		case UPDATE2modeA:
		case UPDATE2modeB:
		case WAIT2b:
			addUpdateByte( &received_update, byte );
			break;

		default: 	// CMDmode
			//USART2_putchar(byte);
			break;
		}
		fsm_unlock();
	}

}

void userbutton_callback_fn(void)
{
	if( fsm_lock() == FSM_LOCK_ACQUIRED )
	{
		switch( fsm_get_state() )
		{
		case STATE_RESET:
			break;

		case CMDmode:
		case PINGmode:
		case UPDATEmodeA:
		case UPDATEmodeB:
		case WAITb:
		case GetID:
		case UPDATE2modeA:
		case UPDATE2modeB:
		case WAIT2b:
			timer3_start();
			break;

		default:
			USART2_putstr("FSM state unaffected by button push\n\r");
			break;
		}
		fsm_unlock();
	}
}

void systick_callback_fn(void)
{
	int id;

	if( fsm_lock() == FSM_LOCK_ACQUIRED )
	{
		switch( fsm_get_state() )
		{
		case STATE_RESET:
			break;

		//case PINGlisten:
		case PINGmode:
			USART2_putstr("Received data: ");
			printPing( &received );							// print received ping
			USART2_putchar('\n');
			if( ping_lock() == PING_LOCK_ACQUIRED ){		// reset received ping buffer
				resetPing( &received );
				ping_unlock();
			}
			USART2_putstr("Sending ping ");
			printPing( &ping );
			sendPing( &ping );						// send ping

			break;

		case UPDATEmodeA:
			fsm_set_state(UPDATEmodeB);
			break;

		case UPDATEmodeB:
			fsm_set_state(WAITb);
			break;

		case UPDATE2modeA:
			fsm_set_state(UPDATE2modeB);
			break;

		case UPDATE2modeB:
			fsm_set_state(WAIT2b);
			break;

		default:
			//USART2_putstr("FSM state unaffected by timer termination\n\r");
			break;
		}
		fsm_unlock();
	}
}

/* need to define the tim3 callback function */
void timer3_callback_fn(void)
{
	timer3_disable();

	/* debug */
	//USART2_putstr("timer3 expired\r\n");

	if( fsm_lock() == FSM_LOCK_ACQUIRED )
	{
		switch( fsm_get_state() )
		{
		case STATE_RESET:
			fsm_set_state(CMDmode);
			break;

		case CMDmode:
			if( userbutton_read() )
				fsm_set_state(PINGmode);
			break;

		case PINGmode:
			if( userbutton_read() ) {

				fsm_set_state(UPDATEmodeA);
			}
			break;

		case UPDATEmodeA:
		case UPDATEmodeB:
			if( userbutton_read() ){
				resetUpdate(&received_update);
				fsm_set_state(GetID);
			}

			break;

		case GetID:
			if( userbutton_read() )
				fsm_set_state(CMDmode);
			break;

		case UPDATE2modeA:
		case UPDATE2modeB:
			if( userbutton_read() ){
				resetUpdate(&received_update);
				fsm_set_state(CMDmode);
			}
			break;

		default:
			//USART2_putstr("FSM state unaffected by timer 3 termination\n\r");
			break;
		}
		fsm_unlock();
	}

}

/*
 * Using UDP protocols highlighted by WiFly-RN-UM reference document section 11
 *
 * Should called only to initialize WiFly module for the first time
 * Upon successive restarts, the WiFly module will have correct configuration
 *
 * Revision: should implement with confirmation checking
 */
void setWiFi(void){

	USART3_putstr("exit\r");
	USART2_putstr("Initializing Wifi module\r\n");
	waitmsn(1000);
	// enter command mode
	USART3_putstr("$$$");
	waitmsn(1000);
	// set join mode to autoconnect
	//USART3_putstr("set sys autoconn 1\r");
	USART3_putstr("set wlan join 1\r");
	waitmsn(1000);
	// set wireless authentication to WPA-2 PSK
	USART3_putstr("set wlan auth 4\r");
	waitmsn(1000);
	// set wireless ssid to "ENGS62"
	USART3_putstr("set wlan ssid ENGS62\r");
	waitmsn(1000);
	// set wireless passphrase to "Engs62connect"
	USART3_putstr("set wlan phrase Engs62connect\r");
	waitmsn(1000);
	// set protocol to UDP
	USART3_putstr("set ip proto 1\r");
	waitmsn(1000);
	// set IP remote host to 129.170.66.33
	USART3_putstr("set ip host 129.170.66.33\r");
	waitmsn(1000);
	// set IP remote port number to 8880
	USART3_putstr("set ip remote 8880\r");
	waitmsn(1000);
	// set IP configuration to use DHCP from access point
	USART3_putstr("set ip dhcp 1\r");
	waitmsn(1000);
	// save
	USART3_putstr("save\r");
	waitmsn(1000);
	// reboot with saved settings
	USART3_putstr("reboot\r");
	waitmsn(1000);
	//USART3_putstr("join\r");
	USART2_putstr("Initialized and rebooted Wifi module\r\n");
	// exit command mode
	USART3_putstr("exit \r");
}



void main(void)
{
	/* Set up the USART2 9600-8N1 and to call USART2_callback_fn when new data arrives */
	USART2_init(USART2_callback_fn);
	USART2_putstr("Starting program\n\r");

	/* Set up the USART3 9600-8N1 adn to call USART3_callback_fn when new data arrives */
	USART3_init(USART3_callback_fn);

	/* configure ping structure */
	ping.type = PING;
	ping.id = MY_ID;

	resetPing( &received );

	printPing( &ping );
	printPing( &received );

	/* configure update structures */
	update.type = UPDATE;
	update.id = 18;
	update.value = 0;

	resetUpdate( &received_update );

	/* set id_buf to all nulls */
	resetCharIDBuf();

	/* initialize LEDS */
	LED_init();

	// configure wifi module
	//setWiFi();

	/* Configure user pushbutton and call pushbutton_callback_fn when button press-released */
 	userbutton_init(userbutton_callback_fn);

	/* configure systick interrupts */
	systick_init(systick_callback_fn);

	/* configure timer interrupts for debouncing */
	timer3_init(timer3_callback_fn, 25);

	/* configure and init the pwm'ed servo */
 	servo_init();
	servo_closegate();
	servo_opengate();

	/* configure and init the ADC port connected to a potentiometer */
	ADC_init( ADC_callback_fn );

	/* Enable interrupts - do this after initializing the system */
	__asm ("  cpsie i \n" );


	// display settings
	//USART3_putstr("$$$");
	//waitmsn(1000);
	//USART3_putstr("get ip\r");
	//waitmsn(1000);
	//USART3_putstr("get wlan\r");
	//waitmsn(1000);
	//USART3_putstr("exit\r");
	//waitmsn(1000);

	/* initialize the finite state machine */
	fsm_init();

	USART2_putstr("Finished Initialization\r\n");

	track_id = MY_ID;

	/* Wait here forever - everything is now interrupt driven */
	while(1)
	{
		;;;
	}
}
