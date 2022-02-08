ENTRY(_start)
SECTIONS {
	.multiboot 0x0000000 :
	{
		. = ALIGN(8);
		KEEP(*(.multiboot))
	}
	.code : { *(.code) }
	.text : { *(.text) }
	.data : 
	{
		*(.data)
		*(.rodata)
	}
	.bss  : { *(.bss) }
 }
