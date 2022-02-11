#include <stdint.h>
#include <serial.h>
#include <fmt.h>
#include <boot.h>
#include <gdt.h>

char buf[11];

void kmain()
{

	serial_write((char*)mbinfo->cmdline);
	serial_write("\nLoading GDT..\0");
	load_gdt();
	serial_write("\tOK\n\0");
	serial_write("Avaible memory:\t\0");
	char* memval_s = atos_s((uint32_t)mbinfo->mem_upper, &buf[0], sizeof(buf));
	serial_write(memval_s);
	serial_write(" KiB\n\0");
}
