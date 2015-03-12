#include <mutex.h>
#include "ping.h"
#include "USART2.h"
#include "stdint.h"
#include "ADC.h"
#include "printHex.h"

static uint32_t ping_mutex;

extern int rec_count;
extern int update_count;

void initPing(void){
	mutex_init(&ping_mutex);
	while( ping_lock() != PING_LOCK_ACQUIRED );
	ping_unlock();
}

uint8_t ping_lock(void)
{
	uint8_t retval = PING_LOCK_FAILED;

	if( mutex_lock(&ping_mutex) == MUTEX_LOCKED )
		retval = PING_LOCK_ACQUIRED;

	return retval;
}

void ping_unlock(void)
{
	mutex_unlock(&ping_mutex);
}

void sendPing( Ping_t * tosend){

	int size = sizeof(*tosend);
	int i;
	uint8_t* ptr = (void *)tosend;

	for( i = 0; i < size; i++){
		USART3_putchar(*(ptr + i));
	}
	//USART2_putstr("SENT PING\r\n");
}

void addByte( Ping_t * buf, uint8_t byte ){

	if( ping_mutex == MUTEX_LOCKED )
	{
		int size = sizeof(*buf);
		uint8_t * ptr = (void *)buf;

		if( rec_count < size){
			*(ptr + rec_count) = byte;
			rec_count++;
		}
	}
}

void resetPing( Ping_t * reset ){
	int i;
	int size = sizeof( *reset );
	uint8_t * ptr = (void *)reset;

	for( i = 0; i < size; i++ ){
		*(ptr + i) = 0;
	}
	rec_count = 0;
}

void printPing( Ping_t * toprint){
	// convert binary to chars?
	USART2_putstr("Ping: ");
	USART2_putstr("type: ");
	printHex( toprint->type );
	USART2_putstr(" id: ");
	printHex( toprint->id );
	USART2_putstr("\n\r");
}

/*
 * sends an update structure over wifi
 */
void sendUpdate( Update_req_t * tosend )
{
	int i;
	int size = sizeof( *tosend );
	uint8_t * ptr = (void *)tosend;

	for( i = 0; i < size; i++){
		USART3_putchar(*(ptr + i));
	}
}

/*
 * addUpdatebyte = adds received byte to update buffer structure
 */
void addUpdateByte( Update_resp_t * buf, uint8_t byte)
{
	int size = sizeof(*buf);
	uint8_t * ptr = (void *)buf;

	if( update_count < size ){
		*(ptr + update_count) = byte;
		update_count++;
	}
}

/*
 * resets a ping structure to zeros
 */
void resetUpdate( Update_resp_t * reset )
{
	int i = 0;
	int size = sizeof( *reset );
	uint8_t * ptr = (void *)reset;

	for( i = 0; i < size; i++){
		*(ptr + i) = 0;
	}

	update_count = 0;
}

void printUpdateReq( Update_req_t * toprint)
{
	int i;
	USART2_putstr("Transmitted Update Request -- [type: ");
	printHex( toprint->type);
	USART2_putstr(", id: ");
	printHex( toprint->id);
	USART2_putstr(", value: ");
	printHex( toprint->value);
	USART2_putstr("]\n\r");
}

/*
 * prints ping structure to USART2
 */
void printUpdateResponse( Update_resp_t * toprint)
{
	int i;

	USART2_putstr("Received Update Response -- type: ");
	printHex( toprint->type);
	USART2_putstr(", id: ");
	printHex( toprint->id);
	USART2_putstr(" average: ");
	printHex( toprint->average);
	USART2_putstr(" [ ");

	for( i = 0; i < 30; i++){
		printHex( toprint->values[i]);
		USART2_putchar(' ');
	}
	USART2_putstr("]\n\r");
}
