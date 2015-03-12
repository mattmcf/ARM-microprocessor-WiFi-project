/*
 * wait.S contains routines for waiting n seconds and ns milliseconds
 */


 	.syntax unified   			/* Use unified style assembly syntax */
	.thumb            			/* Cortex-M3 only supports Thumb code */

    /* Make these routines visible to other modules */
    .global waitmsn
    .global waitn


    .text

/* Func: Waitmsn
 * Args: r0
 * Desc: Delay (sec), <r0>
 *
 *		 Occupies processor for Delay milliseconds
*/
waitmsn:
	push {r0,r1,lr}
ms_secondcmp:
	cmp r0, #0
	ble ms_endwaitn			/* exit if second count is <= 0  */
ms_secondwait:
	/* Wait for 1 second */
	.equ BUSYWAIT_1_SECOND, 3200
	ldr r1, =BUSYWAIT_1_SECOND		/* cycle counter held in r2 */
ms_waitloop:
	sub r1, r1, #1
	cmp r1, #0
	bne ms_waitloop

	/* Decrement second counter */
	sub r0, r0, #1
	cmp r0, #0
	bgt ms_secondwait
ms_endwaitn:
	pop {r0,r1,pc}

/* Func: Waitn
 * Args: r0
 * Desc: Delay (sec), <r0>
 *
 *		 Occupies processor for Delay seconds
*/
waitn:
	push {r0,r1,lr}
secondcmp:
	cmp r0, #0
	ble endwaitn			/* exit if second count is <= 0  */
secondwait:
	/* Wait for 1 second */
	.equ BUSYWAIT_1_SECOND, 3200000
	ldr r1, =BUSYWAIT_1_SECOND		/* cycle counter held in r2 */
waitloop:
	sub r1, r1, #1
	cmp r1, #0
	bne waitloop

	/* Decrement second counter */
	sub r0, r0, #1
	cmp r0, #0
	bgt secondwait
endwaitn:
	pop {r0,r1,pc}

	.end
