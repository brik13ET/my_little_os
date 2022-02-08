ENTRY(_start)
SECTIONS {
	.multiboot 0x0000000 :
	{
		. = ALIGN(8);
		KEEP(*(.multiboot))
	}
	.text :
	{
		*(.text)
		*(.code)
	}
	.data : 
	{
		*(.data)
		*(.rodata)
	}
	.bss  : { *(.bss) }
	
	data_size = SIZEOF(.data) ;
	text_size = SIZEOF(.text) ;

	data_addr = ADDR(.data) ;
	text_addr = ADDR(.text) ;
 }
