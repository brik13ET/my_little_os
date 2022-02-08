#ifndef BOOT_H
#define BOOT_H

#define	BOOT_FLAGS (0 | (1 << 1) | (1 << 2) )
#define BOOT_MAGIC 0x1BADB002
#define	BOOT_CHECKSUM (0x100000000 - (BOOT_MAGIC + BOOT_FLAGS )) & 0xFFFFFFFF

#include <stdint.h>

extern char* cmdline;

extern void setup_stack(void);
extern void error_handler(void);
extern void _start(void);

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

extern struct multiboot_information * mbinfo;

#endif