/*
 * wait.h contains routines for waiting n seconds and n milliseconds
 */
#pragma once

#include "stdint.h"

/*
 * void waitn( uint32_t )
 *
 * Waits n seconds
 */
void waitn( uint32_t secs );

/*
 * void waitmsn( uint32_t );
 *
 * Waits n milliseconds
 */
void waitmsn( uint32_t millis );
