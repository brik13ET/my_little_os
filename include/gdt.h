#ifndef GDT_H
#define GDT_H

#include <stdint.h>


struct GDT_entry
{
    uint16_t limit_lo;
    uint32_t base_lo : 23;
    uint8_t access;
    uint8_t limit_hi : 4;
    uint8_t flags : 4;
    uint8_t base_hi;
} __attribute__((packed));

struct GDT_entry __attribute__((packed));

extern struct GDT_entry GDT[5];

extern void load_gdt(void);
extern uint32_t asm_load_gdt(uint16_t, struct GDT_entry*);

extern uint32_t	data_size;
extern uint32_t	text_size;

extern uint32_t	data_addr;
extern uint32_t	text_addr;

#endif