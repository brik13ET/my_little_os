#include <stdint.h>
#include <serial.h>
#include <fmt.h>
#include <boot.h>



void kmain()
{
	char tmp[] = "kmain()\0";
	char nl[] = "\n\0";
	serial_write(cmdline);
	serial_write(&nl[0]);
	clear();
	print(&tmp[0]);
}
