#include <stdint.h>

#define	BOOT_FLAGS (0 | (1 << 1))
#define BOOT_MAGIC 0x1BADB002
#define	BOOT_CHECKSUM (0x100000000 - (BOOT_MAGIC + BOOT_FLAGS )) & 0xFFFFFFFF

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

struct	multiboot_information
{
	uint32_t flags;
	uint32_t mem_lower;
	uint32_t mem_upper;
	uint32_t boot_device;
	uint32_t cmdline;
	uint32_t mods_count;
	uint32_t mods_addr;
	uint8_t	syms[12];
	uint32_t mmap_length;
	uint32_t mmap_addr;
	uint32_t drives_addr;
	uint32_t config_table;
	uint32_t boot_loader_name;
	uint32_t apm_table;
	uint32_t vbe_control_info;
	uint32_t vbe_mode_info;
	uint32_t vbe_mode;
	uint32_t vbe_interface_seg;
	uint32_t vbe_interface_off;
	uint32_t vbe_interface_len;
	uint32_t framebuffer_addr;
	uint32_t framebuffer_pitch;
	uint32_t framebuffer_width;
	uint32_t framebuffer_height;
	uint32_t framebuffer_bpp;
	uint32_t framebuffer_type;
	uint32_t color_info_low;
	uint8_t color_info_high;
} __attribute__((packed)) ;

const struct BOOT_HEADER_s
BOOT_HEADER
__attribute__((section(".multiboot")))  = 
{
	.MAGIC = BOOT_MAGIC, 
	.FLAGS = BOOT_FLAGS, 
	.CHECKSUM = BOOT_CHECKSUM, 
	/*.mode_type = 1,
	.width = 80,
	.height = 25,
	.depth = 0
	*/
};

uint32_t process_boot_info ( struct multiboot_information* info)
{
	if (info->mem_lower < 640)
		return (info->mem_lower << 10) ;
	return (info->mem_upper << 10) ;
}
