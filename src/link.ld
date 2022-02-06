ENTRY(kmain)
SECTIONS {
	.multiboot 0x0000000 :
	{
		* ( .multiboot )
	}
	. = 0x100000;
	.code : { *(.code) }
	.text : { *(.text) }
	.data : 
	{
		*(.data)
		*(.rodata)
	}
	.bss  : { *(.bss) }
 }
