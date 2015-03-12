/*
 * printHex.c - contains routines for printing 32 bit number to console in hex
 */

#include "stdint.h"
#include "printHex.h"
#include "USART2.h"

void printHex(uint32_t toPrint)
{
	char send[8];
	int index;
	uint32_t mask = 15; 		/* 0x0000000F */
	uint32_t examine;

	for( index = 0; index < 8; index++){
		examine = mask & toPrint;
		switch( (int) examine ){
		case 0:
			send[index] = '0';
			break;
		case 1:
			send[index] = '1';
			break;
		case 2:
			send[index] = '2';
			break;
		case 3:
			send[index] = '3';
			break;
		case 4:
			send[index] = '4';
			break;
		case 5:
			send[index] = '5';
			break;
		case 6:
			send[index] = '6';
			break;
		case 7:
			send[index] = '7';
			break;
		case 8:
			send[index] = '8';
			break;
		case 9:
			send[index] = '9';
			break;
		case 10:
			send[index] = 'A';
			break;
		case 11:
			send[index] = 'B';
			break;
		case 12:
			send[index] = 'C';
			break;
		case 13:
			send[index] = 'D';
			break;
		case 14:
			send[index] = 'E';
			break;
		case 15:
			send[index] = 'F';
			break;
		default:
			break;
		}
		toPrint = toPrint >> 4;
	}

	USART2_putchar('0');
	USART2_putchar('x');
	for( index = 7; index >= 0; index--){
		USART2_putchar( (uint32_t)send[index]);
	}
}
