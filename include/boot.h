#ifndef BOOT_H
#define BOOT_H

#define	BOOT_FLAGS (0 | (1 << 1) | (1 << 2) )
#define BOOT_MAGIC 0x1BADB002
#define	BOOT_CHECKSUM (0x100000000 - (BOOT_MAGIC + BOOT_FLAGS )) & 0xFFFFFFFF

extern char* cmdline;

extern void setup_stack(void);
extern void error_handler(void);
extern void _start(void);

#endif