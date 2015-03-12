/*
 * ping.h contains structures and routines for pings
 */

#define PING 1
#define UPDATE 2

#include "stdint.h"

// 8 byte ping structure
typedef struct{
	int type;
	int id;
} Ping_t;

typedef struct{
	int type;
	int id;
	int value;
} Update_req_t;

typedef struct{
	int type;
	int id;
	int average;
	int values[30];
} Update_resp_t;

/*
 * Initializes ping mutex
 */
void ping_init(void);

#define PING_LOCK_FAILED   (0)
#define PING_LOCK_ACQUIRED (1)
uint8_t ping_lock(void);
void ping_unlock(void);

/*
 * sends a ping structure
 */
void sendPing( Ping_t * tosend);

/*
 * adds a received byte to a ping buffer structure
 */
void addByte( Ping_t * buf, uint8_t byte );

/*
 * resets a ping structure to zeros
 */
void resetPing( Ping_t * reset );

/*
 * prints ping structure to USART2
 */
void printPing( Ping_t * toprint);

/*
 * sends an update structure over wifi
 */
void sendUpdate( Update_req_t * tosend );

/*
 * addUpdatebyte = adds received byte to update buffer structure
 */
void addUpdateByte( Update_resp_t * buf, uint8_t byte);

/*
 * resets a update response structure to zeros
 */
void resetUpdate( Update_resp_t * reset );

/*
 * prints update_req struct to usart2
 */
void printUpdateReq( Update_req_t * toprint);

/*
 * prints update response structure to USART2
 */
void printUpdateResponse( Update_resp_t * toprint);

