#include "sys.h"
#include "common.h"

char* vga_start = (char*) VGA_START;
int   vga_line=0;
int   vga_ch=0;
int		vga_ctrl = 0;//0表示字符显示，1表示图形显示

void screen_down(){
	for(int i = 0; i < VGA_MAXLINE - 1; i ++){
		for(int j = 0; j < VGA_MAXCOL; j ++){
			vga_start[(i << 7) + j] = vga_start[((i + 1) << 7) + j];
		}
	}
	for(int j = 0; j < VGA_MAXCOL; j++){
		vga_start[((VGA_MAXLINE - 1) << 7) + j] = 0;
	}
}

void newline(){
	vga_line++;
	vga_ch = 0;
	while(vga_line >= VGA_MAXLINE){
		screen_down();
		vga_line--;
	}
}



void vga_init(){
    vga_line = 0;
    vga_ch =0;
    for(int i=0;i<VGA_MAXLINE;i++)
        for(int j=0;j<VGA_MAXCOL;j++)
            vga_start[ (i<<7)+j ] =0;
}
extern int shell_idx;
extern bool in_shell;
void putch(char ch) {
  if(ch==8) //backspace
  {
      //TODO
			if(in_shell){
				vga_start[ (vga_line << 7) + vga_ch ] = 0;
				if(vga_ch == 0){
					vga_ch = VGA_MAXCOL - 1;
					vga_line--;
				}
				else if(vga_ch != 0)
					vga_ch--;
				vga_start[ (vga_line << 7) + vga_ch] = '_';
			}
			else if(vga_ch > 0){
				vga_start[(vga_line << 7) + vga_ch] = 0;
				vga_ch --;
			}
			return;
  }
  if(ch==10) //enter
  {
      //TODO
			vga_start[(vga_line << 7) + vga_ch] = 0;
			newline();
      return;
  }
  vga_start[ (vga_line<<7)+vga_ch] = ch;
  vga_ch++;
  if(vga_ch>=VGA_MAXCOL)
  {
     //TODO
		 newline();
  }
	vga_start[ (vga_line << 7) + vga_ch] = '_';
  return;
}

void putstr(char *str){
    for(char* p=str;*p!=0;p++)
      putch(*p);
}
int puts(const char* string){
	putstr(string);
	putch('\n');
	return strlen(string);
}


int *key_head = (int*) KEY_HEAD;
int *key_tail = (int*) KEY_TAIL;
int *key_start = (int*) KEY_START;
int KBD_RD(){
	if(*key_head == *key_tail)
		return -1;
	int ret = key_start[*key_head];
	*key_head = __umodsi3(*key_head + 1, keybuf);	
	return ret;
}


