#include <assert.h>
#include <fmt.h>
uint8_t fmt = 0x07;

struct vidChar
{
	uint8_t sym;
	uint8_t fmt;
} __attribute__((packed));

volatile struct vidChar * const vidbuf = (struct vidChar *)0xb8000;

volatile uint32_t position = 0;


void clear (void)
{
	position = 0;
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
		vidbuf[position].sym = s[0];
		vidbuf[position].fmt = fmt;
		s++;
		position ++;
	}
}

void putch(char c)
{
    vidbuf[position].sym = c;
    vidbuf[position].fmt = fmt;
    position ++;
}

uint32_t atos_s(uint32_t a, char* buf, uint32_t buf_len)
{
    assert_reached();
}

uint32_t stoa_s(uint32_t a, char* buf, uint32_t buf_len)
{
    assert_reached();
}

uint32_t strlen(char* s)
{
    uint32_t ret = 0;
    while(s[ret] != 0 && ret < -1)
        ret++;
    return ret;
}

uint32_t strcat_s(char* s1, char* s2, uint32_t max_len)
{
    assert_reached();
}

uint32_t strcmp_s(char* s1, char* s2, uint32_t max_len)
{
    assert_reached();
}