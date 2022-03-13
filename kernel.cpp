//own implementation of glib functions
#define VIDEOMEMORYSTART 0xb8000

void printf(char* str)
{
    static unsigned short* VideoMemory = (unsigned short*)VIDEOMEMORYSTART;

    for(int i = 0; str[i] != '\0'; ++i)
        VideoMemory[i] = (VideoMemory[i] & 0xFF00) | str[i];
}

typedef void (*constructor)();
//extern cause c doesnt have name mangling
extern "C" constructor start_ctors;
extern "C" constructor end_ctors;

extern "C" void callConstructors()
{
    for(constructor* i = &start_ctors; i != &end_ctors; i++)
        (*i)();
}

//this parameters set in loader.s
extern "C" void kernelMain(const void* multiboot_structure, unsigned int multiboot_magic)
{
    printf((char*)"im not a gay im cockOS:(");

    while(1);
}

