#ifndef FMT_H
#define FMT_H

#include <stdint.h>

extern uint32_t atos_s(uint32_t, char*, uint32_t);
extern uint32_t stoa_s(uint32_t, char*, uint32_t);
extern uint32_t strlen(char*);
extern uint32_t strcat_s(char*, char*, uint32_t);
extern uint32_t strcmp_s(char*, char*, uint32_t);

extern void clear(void);
extern void print(char*);
extern void putch(char);

extern uint8_t fmt;

#endif