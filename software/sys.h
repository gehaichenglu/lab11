
#ifndef SYS_H
#define SYS_H

#define VGA_START    0x00200000
#define VGA_LINE_O   0x00210000
#define VGA_MAXLINE  30
#define LINE_MASK    0x003f
#define VGA_MAXCOL   80
#define KEY_START 0x00300000
#define KEY_HEAD 0x003ffff0
#define KEY_TAIL 0x003fffe0
#define VGA_CONTROL 0x00400000
#define VGA_MEM 0x00600000
#define TIME 0x00500000
#define TIME_RESET 0x00800000

#define VGA_WIDTH 640
#define VGA_DEPTH 480

#define keybuf 32
void putstr(char* str);
void putch(char ch);
int puts(const char* string);
void vga_init(void);

#endif
