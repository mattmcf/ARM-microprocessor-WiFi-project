#pragma once

#include "stdint.h"

void userbutton_init(void(*button_callback_fn)(void));

uint32_t userbutton_read( void );
