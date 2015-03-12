/*
 * kmutex.S
 *
 * Kernel level mutex support.  NOTE: kernel locks are spinlocks - we do not yield the processor
 * to another task.  It is expected that user-level locks would yield to another process if the
 * lock is held by another task when requested....
 *
 * TODO: this code needs references to the relevant ARM synchronization documentation
 */

    .syntax unified     /* Use the unified instruction syntax */
    .thumb              /* Assemble thumb instruction set */

    .equ locked, 1
    .equ unlocked, 0

    .global mutex_init   /* void mutex_init(void *mutex); */
    .global mutex_lock   /* void mutex_lock(void *mutex); */
    .global mutex_unlock /* void mutex_unlock(void *mutex); */

    .text

mutex_init:
    push    {r1}
    ldr	    r1, =unlocked	
    str	    r1,[r0]
    pop     {r1}
    bx	    lr

mutex_lock:
    push    {r1,r2}
    ldr     r1, =locked
try_lock:
    ldrex   r2, [r0]      /* Fetch mutex using exclusive monitor */
    cmp     r2, r1        /* Test if locked */
    beq     lock_failed   /* If locked, retry until we find it unlocked */
    strex   r2, r1, [r0]  /* Try to store "locked" state w/ exclusive monitor */
    cmp     r2, #1        /* Check if strexne succeded */
    beq     lock_failed   /* If strexne failed, return with failure */
    dmb                   /* Succeeded, do not allow any memory reads until write completes */
    mov     r0, #1        /* Return 1 for success */
    b 		lock_return
lock_failed:
  	mov		r0, #0
lock_return:
    pop	    {r1,r2}
    bx      lr            /* Return */

mutex_unlock:
    push    {r1}
    ldr     r1, =unlocked
    dmb                   /* finish all pending memory accesses before releasing lock */
    str     r1, [r0]
    pop	    {r1}
    bx      lr

    .end
