OUTPUT_FORMAT	(elf32-i386)
ENTRY(_start)
SECTIONS {
	. = 0x100000;
	.code : { *(.code) }
	.text : { *(.text) }
	.data : { *(.data) }
	.bss  : { *(.bss) }
 }
