#pragma once

/*
 * Initializes systick for 1 second interval interrupts
 */
void systick_init(void(*fn)(void));
