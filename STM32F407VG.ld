/* Minimal linker script for the STM32F407VG */

/* The STM32F processors mirror flash at 0x08000000 to address 0x00000000 */
/* This puts the vector table stored at 0x08000000 at the expected        */
/* Vector Table location of 0x00000000 on power-on/reset                  */
MEMORY
{
  flash (rx) : ORIGIN = 0x08000000, LENGTH = 1024k
  ram (rwx)  : ORIGIN = 0x20000000, LENGTH = 192k
}

/* Make sure a stack-size is specified, non-zero and correctly aligned */
EXTERN(__stack_size)
ASSERT(__stack_size, "Must provide a non-zero stack size");
ASSERT(!(__stack_size & 0xf), "Stack not aligned on 64-bit boundary");

/* Mark unused RAM as "heap" */
__heap_start = __data_end;
__heap_end = __data_start + LENGTH(ram);


SECTIONS
{
	.text :
	{
		__text_start = .;
		*(vectors)               /* Vector Table */
		*(.text)                 /* Normal Program Code */
		*(.rodata)               /* "static const <datatype>" */
		. = ALIGN(4);           
		__text_end = .;         
	} >flash
	
	.stack (NOLOAD) :            /* Place the stack at the top of RAM */
	{
		. = ALIGN(4);
		. = . + __stack_size;
		. = ALIGN(4);
		__stack_top = .;
	} >ram
	
	.data : AT (__text_end)
	{
		. = ALIGN(4);
		__data_start = .;     
		*(.data)                 /* "global/static init = non-zero" vars */
		__data_end = .;
		. = ALIGN(4);           
	} >ram
	__data_bytes = (__data_end - __data_start);  
	
	
	.bss (NOLOAD) :
	{
		. = ALIGN(4);           
		__bss_start = .;
		*(.bss)                  /* "global/static init = zero" vars */
		__bss_end = .;
		. = ALIGN(4);           
	} >ram
	__bss_bytes = (__bss_end - __bss_start);     
}