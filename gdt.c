#include "gdt.h"
#include "types.h"

static gdt_table main_gdt_table;
static gdt_ptr main_gdt_ptr;

void load_gdt(gdt_entry* p){
    uint32 i[2];
    i[1] = (uint32)p;
    i[0] = sizeof(gdt_entry) << 16;
    asm volatile("lgdt (%0)": :"p" (((uint8 *) i)+2));
    return;
}

void init_gdt(){
    main_gdt_table.entries[0] = (gdt_entry){0,0,0,0,0,0};
    main_gdt_table.entries[1] = (gdt_entry){0xffff, 0, 0, 0x9a, 0b11001111, 0};
    main_gdt_table.entries[2] = (gdt_entry){0xffff, 0, 0, 0x92, 0b11001111, 0};
    
    main_gdt_ptr.cap = sizeof(main_gdt_table.entries) - 1;
    main_gdt_ptr.start = (gdt_entry*)&main_gdt_table.entries;
    load_gdt(main_gdt_ptr.start);
}

