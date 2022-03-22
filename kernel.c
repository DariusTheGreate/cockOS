#include "vga.h"
#include "gdt.h"

typedef void (*constructor)();
//extern cause c doesnt have name mangling
constructor start_ctors;
constructor end_ctors;

void callConstructors()
{
    for(constructor* i = &start_ctors; i != &end_ctors; i++)
        (*i)();
}

//this parameters set in loader.s
void kernelMain(const void* multiboot_structure, unsigned int multiboot_magic)
{
    init_gdt();
   // printf((char*)"so i was pooping\nin the toilet\ni was all over the place\niv been doing kaka for a whole day\n\n\n\nwhoel day shiiting this bad boy\nhes wanna to kaka but i dont so i kaka myself\n\n\nkak is not taht easy u kno\n for starters i need to take of my pants\n...\ntahts hard\n if you one of this buulshoters that shit like a pro\nyes..\nbut im not the one okay?\nstop asking me if i am\n\n\nim not\n\n\n\n\nthats the end of the story\n\n2022");
    printf("aaaaaa\nbbbbb\nccccc\nddddd\neeeee\nfffff\ngggggo\naaaaa\nbbbbb\nccccc\nddddd\neeeee\nfffff\ngggggo\naaaaa\nbbbbb\nccccc\nddddd\neeeee\nfffff\ngggggo\naaaaa\nbbbbb\nccccc\nddddd\neeeee\nfffff\ngggggo\naaaa\nbbbbb\nccccc\nddddd\neeeee\nfffff\ngggggo\n");
    while(1);
}

