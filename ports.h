#ifndef _COCK_PORTS_
#define _COCK_PORTS_

#include "types.h"

void outb(uint16 port, uint8 value);
uint8 inb(uint16 port);
uint8 inw(uint16 port);
#endif

