#ifndef _COCK_IDT_
#define _COCK_IDT_

#include "types.h"
typedef struct _idt_entry {
    uint16 base_low; 
} __attribute__((packed)) idt_entry;

#endif

