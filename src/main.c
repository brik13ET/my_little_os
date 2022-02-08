#include <stdint.h>
#include <serial.h>
#include <boot.h>
#include <gdt.h>

void kmain()
{
	serial_write((char*)mbinfo->cmdline);
	serial_write("\nLoading GDT..\0");
	load_gdt();
	serial_write("\tOK\n\0");
}
