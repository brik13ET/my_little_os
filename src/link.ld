#if defined (MANUAL_BOOT)
ENTRY(boot)
#else
ENTRY(kmain)
#endif
SECTIONS {
#if defined(MANUAL_BOOT)
	.boot (NOLOAD) :
	AT ( 1xFE )
	{
		* ( .boot )
	}

#else
	.multiboot 0x0000000 :
	{
		* ( .multiboot )
	}
#endif
	. = 0x100000;
	.code : { *(.code) }
	.text : { *(.text) }
	.data : { *(.data) }
	.bss  : { *(.bss) }
 }
