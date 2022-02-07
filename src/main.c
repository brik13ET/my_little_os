#include <stdint.h>

uint8_t fmt = 0x07;

struct vidChar
{
	uint8_t fmt;
	uint8_t sym;
} __attribute__((packed));

struct vidChar * const vidbuf = 0xb8000;

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
		vidbuf[current].sym = s;
		vidbuf[current].fmt = fmt;
		s++;
		current ++;
	}
}

extern void process_boot_info(void);

extern void setup_stack(void);

void kmain()
{

	print(__FUNCTION__);
}
