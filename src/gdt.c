#include <gdt.h>
#include <boot.h>


struct GDT_entry GDT[5];

void load_gdt() // must cover all linear address space, but first entry is null
{
    GDT[0] = (struct GDT_entry) {0 ,} ;
    GDT[1] = (struct GDT_entry) // data sec
    {
        .base_lo = data_addr,
        .base_hi = (data_addr >> 23),
        .limit_lo = data_size,
        .limit_hi = (data_size >> 16),
        .access = 0 | (1 << 7) | (1 << 4) | 0,
        .flags = 0 | (1 << 2)
    };
    GDT[2] = (struct GDT_entry) // text sec
    {
        .base_lo = text_addr,
        .base_hi = (text_addr >> 23),
        .limit_lo = text_size,
        .limit_hi = (text_size >> 16),
        .access = 0 | (1 << 7) | (1 << 4) | (1 << 3) | (1 << 1),
        .flags = 0 | (1 << 2)
    };
    GDT[3] = (struct GDT_entry) // stack sec
    {
        .base_lo = (mbinfo->mem_upper << 10),
        .base_hi = (mbinfo->mem_upper >> 13),
        .limit_lo = 0x2000,
        .limit_hi = 0,
        .access = 0 | (1 << 7) | (1 << 4) | (1 << 2) | (1 << 1),
        .flags = 0 | (1 << 2)
    };
    GDT[4] = (struct GDT_entry) // bss sec
    {
        .base_lo = 0,
        .base_hi = 0,
        .limit_lo = 0x0100,
        .limit_hi = 0,
        .access = 0 | (1 << 7) | (1 << 4) | (1 << 1),
        .flags = 0 | (1 << 2) | (1 << 1)
    };
    asm_load_gdt(sizeof(GDT)/sizeof(struct GDT_entry), &GDT[0]);
}