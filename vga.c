#include "vga.h"

#include "ports.h"
#include "types.h"

typedef struct _cursor {
    uint16 x_pos;
    uint16 y_pos;
    uint16 width;
} cursor;

typedef struct _video_memory {
    uint16* memory_ptr;
    uint32 size;
    uint32 cap;
} video_memory;

static video_memory main_video_memory = {(uint16*)VGASTART, 0, (uint32)VGACAP};

static cursor main_cursor = {0,0, 80};

void write_to_memory(uint32 pos, uint16 val){
    main_video_memory.memory_ptr[pos] = val;
}

void write_to_memory_at_cursor(uint16 data){
    uint8 backColour = 0;
    uint8 foreColour = 15;

    uint8  attributeByte = (backColour << 4) | (foreColour & 0x0F);
    uint16 attribute = attributeByte << 8;
    write_to_memory(main_cursor.y_pos * main_cursor.width + main_cursor.x_pos, attribute | data);
    //main_video_memory.size++;
    //main_video_memory.memory_ptr[(main_cursor.y_pos * main_cursor.width + main_cursor.x_pos)] = attribute | data;
}

void scroll_memory(uint16 width, uint16 dy){
    //write_to_memory(((main_video_memory.size - 1) - 75) - dy*width, main_video_memory.memory_ptr[(main_video_memory.size - 1) - 75]);
    for(uint32 x = main_video_memory.size - 1; x > 0; x--){
        if(x < main_video_memory.size - dy*width)
            break;

        write_to_memory(x - dy*width, main_video_memory.memory_ptr[x]);
        write_to_memory(x, ' ');
    }
}

void update_main_cursor(){
    uint16 pos = main_cursor.y_pos * main_cursor.width + main_cursor.x_pos; 
    outb(0x3D4, 14);
    outb(0x3D5, pos >> 8);
    outb(0x3D4, 15);
    outb(0x3D5, pos);
}

static void dispath_character(char c){
    if(c == '\n'){
        main_cursor.x_pos = 0;
        main_cursor.y_pos+=1;
        main_video_memory.size+=80;
    }
    else{
        write_to_memory_at_cursor(c);
        main_cursor.x_pos++;
    }

    if(main_cursor.y_pos >= main_cursor.width){
        main_cursor.x_pos = 0;
        main_cursor.y_pos++;
    }
    
    if(main_cursor.y_pos > 25){
      // scroll_memory(main_cursor.width, 24);
    }

    update_main_cursor();
}

void printf(char* str)
{
    uint32 i = 0;
    while(str[i]){
        dispath_character(str[i++]);
    }

    //scroll_memory(main_cursor.width, 10);
}

