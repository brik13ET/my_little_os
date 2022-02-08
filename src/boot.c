#include <stdint.h>
#include <boot.h>

char* cmdline;

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
	.MAGIC = BOOT_MAGIC, 
	.FLAGS = BOOT_FLAGS, 
	.CHECKSUM = BOOT_CHECKSUM, 
	.mode_type = 1,
	.width = 120,
	.height = 40,
	.depth = 0
	
};

struct multiboot_information * mbinfo;

uint32_t process_boot_info ( struct multiboot_information* info)
{
	mbinfo = info;
	cmdline = (char*)info->cmdline;
	if (info->mem_lower < 640)
		return (info->mem_lower << 10) ;
	return (info->mem_upper << 10) ;
}
