#ifndef _COCK_GDT_
#define _COCK_GDT_

#include "types.h"

typedef struct _gdt_entry {
    uint16 segment_limit;
    uint16 base_low;
    uint8 base_mid;
    uint8 acess;
    uint8 granularity;
    uint8 base_high;
} __attribute__((packed)) gdt_entry;

typedef struct  _gdt_ptr{
    uint16 cap;
    gdt_entry* start;
} __attribute__((packed)) gdt_ptr;

typedef struct _gdt_table {
    gdt_entry entries[3];
} gdt_table;

void init_gdt();

#endif

