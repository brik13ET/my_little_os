#include <stdint.h>
#include <serial.h>

uint8_t fmt = 0x07;

struct vidChar
{
	uint8_t sym;
	uint8_t fmt;
} __attribute__((packed));

struct vidChar * const vidbuf = (struct vidChar *)0xb8000;

uint32_t current = 0;


void clear (void)
{
	current = 0;
	for (uint16_t i = 0; i < 80*25; i++)
	{
		vidbuf[i].sym = 0;
		vidbuf[i].fmt = 0;
	}
}

void print (char* s)
{

	while (s[0] != 0)
	{
		vidbuf[current].sym = s[0];
		vidbuf[current].fmt = fmt;
		s++;
		current ++;
	}
}

void kmain()
{
	char tmp[] = "kmain()\0";
	serial_init();
	serial_write(&tmp[0]);
	clear();
	print(&tmp[0]);
}
