#include <stdint.h>

#ifndef BOOT_FLAGS
#define	BOOT_FLAGS 0 | 1 << 2
#endif

#define	BOOT_CHECKSUM - ( 0x1BADB002 + BOOT_FLAGS )

extern void kmain (void);

struct	BOOT_HEADER_s
{
	uint32_t	MAGIC;
	uint32_t	FLAGS;
	uint32_t	CHECKSUM;
	uint32_t	header_addr;	
	uint32_t	load_addr;
	uint32_t	load_end_addr;
	uint32_t	bss_end_addr;
	uint32_t	entry_addr;
	uint32_t	mode_type;
	uint32_t	width;
	uint32_t	height;
	uint32_t	depth;
} __attribute__((packed));

const struct BOOT_HEADER_s
BOOT_HEADER
__attribute__((section(".multiboot")))  = 
{
	.MAGIC = 0x1BADB002, 
	.FLAGS = BOOT_FLAGS, 
	.CHECKSUM = BOOT_CHECKSUM, 
	.mode_type = 0,
	.width = 160, 
	.height = 60, 
	.depth = 0,
	.entry_addr = kmain
};
