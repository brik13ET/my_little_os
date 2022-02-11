#include <assert.h>
#include <fmt.h>
uint8_t fmt = 0x07;

struct vidChar
{
	uint8_t sym;
	uint8_t fmt;
} __attribute__((packed));

volatile struct vidChar * const vidbuf = (struct vidChar *)0xb8000;

uint32_t position = 0;


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

char* xtos_s(uint32_t x, char* buf, uint32_t buf_len)
{
	char symbols[] = "0123456789ABCDEF";
	uint32_t buff_i = 0;
	do
	{
		buf[buf_len - 2 - buff_i] = symbols[x % 16];
		x = x / 16;
		buff_i ++;
	} while (x > 0 && buff_i < buf_len);
	buf[buf_len - 1] = 0;
	return buf + buff_i;
}

char* atos_s(uint32_t a, char* buf, uint32_t buf_len)
{
    char symbols[] = "0123456789";
	uint32_t buff_i = 0;
	do
	{
		buf[buf_len - 2 - buff_i] = symbols[a % 10];
		a = a / 10;
		buff_i ++;
	} while (a > 0 && buff_i < buf_len);
	buf[buf_len - 1] = 0;
	return buf + buff_i;
}

char* btos_s(uint32_t b, char* s, uint32_t buf_len)
{
	char symbols[] = "01";
	uint32_t buff_i = 0;
	do
	{
		s[buf_len - 2 - buff_i] = symbols[b % 2];
		b = b / 2;
		buff_i ++;
	} while (b > 0 && buff_i < buf_len);
	s[buf_len - 1] = 0;
	return s + buff_i;
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