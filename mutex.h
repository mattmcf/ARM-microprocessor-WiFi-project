#pragma once

#include "stdint.h"

#define MUTEX_LOCKED      (1)
#define MUTEX_LOCK_FAILED (0)

/* Initialize a mutex variable */
void mutex_init(uint32_t *pmutex);

/* Attempt to lock a mutex variable - returns MUTEX_LOCKED on success or MUTEX_LOCK_FAIL */
uint32_t mutex_lock(uint32_t *pmutex);

/* Free an actively held lock */
void mutex_unlock(uint32_t *pmutex);
