#include "sys.h"
#include "common.h"

int main();

//setup the entry point
void entry()
{
    asm("lui sp, 0x00140"); //set stack to high address of the dmem
    asm("addi sp, sp, -4");
    main();
}

extern char shell[];

int64_t atoi_c(int idx){
	while(shell[idx] == ' ') idx++;
	bool minus = false;
	int n = 0;
	if(shell[idx] == '-'){
		idx++;
		minus = true;
	}
	while(shell[idx] <= '9' && shell[idx] >= '0'){
		n = __mulsi3(n, 10);
		n += shell[idx] - '0';
		idx++;
	}
	uint32_t nidx;
	if(shell[idx] != 0 && shell[idx] != ' '){
		nidx = strlen(shell);
	}
	else
		nidx = idx;
	if(minus){
		n = -n;
	}
	return (((int64_t)n << 32) | (int64_t)nidx);
}

void putint(int n){
	char temp[32];               
  int idx = 0;                 
  int minus = 0;               
  if(n < 0){                   
    minus = 1;                 
    n = -n;
  }
  char str[32];                
  if(n == 0){                  
    str[0] = '0'; str[1] = '\0';    
    putstr(str);               
    return;
  } 
  while(n){                    
    temp[idx++] = __umodsi3(n, 10) + '0';
    n = __udivsi3(n, 10);      
  }
  if(minus){
    temp[idx++] = '-';
  }
  str[idx--] = '\0';
  for(int i = 0; idx >= 0; idx--, i++)
    str[idx] = temp[i];
  putstr(str);
}



char hello[]="Hello World 2022!\n";
char unknown[] = "unknown command\n";
extern int vga_line;
extern int vga_ch;
void exec_hello(){
	putstr(hello);
}
void exec_clear(){
	for(int i = 0; i < VGA_MAXLINE; i++)
		putch('\n');
	vga_line = 0;
	vga_ch = 0;
}
void exec_dry();
void exec_type();
int fib(int n){
	if(n == 1 || n == 2) return 1;
	int f0 = 1, f1 = 1, f2 = 2;
	for(int i = 3; i < n; i++){
		f0 = f1;
		f1 = f2;
		f2 = f0 + f1;
	}
	return f2;
}
void exec_fib(){
	uint32_t idx = 3;
	//putstr("before atoi\n");
	int64_t ret = atoi_c(idx);
	//putstr("after atoi\n");
	int n = ret >> 32;
	uint32_t nidx = ret & 0xffffffff;
	int ans = fib(n);
	idx = nidx;
	//putint(ans);
	//putch('\n');
	printf("fib[%d]=%d\n", n, ans);
}

int partition(int arr[], int l, int r){
	int tmp;
  int x = arr[r];              
  int i = l - 1;               
  for(int j = l; j < r; j++){  
    if(arr[j] <= x){           
      i++;
      tmp = arr[i];
      arr[i] = arr[j];         
      arr[j] = tmp;            
    }
  }
  tmp = arr[i + 1];
  arr[i + 1] = arr[r];
  arr[r] = tmp;
  return i + 1;
}

void sort(int arr[], int l, int r){
	if(l < r){
		int q = partition(arr, l, r);
		sort(arr, l, q - 1);
		sort(arr, q + 1, r);
	}
}
static int sort_arr[64];
static int num = 0;
void exec_sort(){
	num = 0;
	int idx = 4;
	int len = strlen(shell);
	while(idx < len){
		int64_t ret = atoi_c(idx);
		idx = ret & 0xffffffff;
		sort_arr[num++] = ret >> 32;
	}
	sort(sort_arr, 0, num - 1);
	for(int i = 0; i < num; i++){
		//putint(sort_arr[i]);
		//putch(' ');
		printf("%d ", sort_arr[i]);
	}
	putch('\n');
}

void exec_dry();
void exec_type();
void video_test();

typedef struct{
	char name[16];
	void	(*exec)();
}task;

task task_table[7] = {
	[0] = { "hello" , exec_hello},
	[1] = { "clear" , exec_clear},
	[2] = { "fib"   , exec_fib},
	[3] = { "sort"	, exec_sort},
	[4] = { "dry"   , exec_dry},
	[5] = { "type"	, exec_type},
	[6] = { "video" , video_test},
};


extern char _heap_start;
Area heap = RANGE(&_heap_start, 0x00120000);


void trm_init(){
	hAddr = heap.start;
}

char shell[256];
extern char keytoascii[];
extern char keytocapascii[];
int shell_idx = 0;	
bool in_shell = true;
int main()
{		
		trm_init();
    vga_init();
		ioe_init(); 
		AM_INPUT_KEYBRD_T keyrd;
		bool capital = false;
		bool caplock = false;
		bool shellOF = false;
    //putstr(hello);
    while (1)
    {	
			in_shell = true;
			shellOF = false;
			shell_idx = 0;
			memset(shell, 0, strlen(shell));
			printf("nyarukoSAN $");
			//printf("Starker:");
			ioe_read(AM_INPUT_KEYBRD, &keyrd);
			while(keyrd.keycode != AM_KEY_RETURN || (keyrd.keycode == AM_KEY_RETURN && !keyrd.keydown)){

				if(keyrd.keycode == AM_KEY_LSHIFT || keyrd.keycode == AM_KEY_RSHIFT){
					if(keyrd.keydown == true){
						capital = caplock ^ true;
					}
					else {
						capital = caplock;
					}
				}
				if(keyrd.keycode == AM_KEY_CAPSLOCK && keyrd.keydown){
					caplock = !caplock;
					capital = !capital;
				}
				char ch;
				if(capital){
					ch = keytocapascii[keyrd.keycode];
				}
				else{
					ch = keytoascii[keyrd.keycode];
				}
				if(keyrd.keydown){
					if(ch != 0){
						if(ch != 8){
							shell[shell_idx++] = ch;
							putch(ch);	
						}
						else if(shell_idx >= 1){
							shell[shell_idx--] = '\0';
							putch(ch);
						}
					}
				}
				if(shell_idx >= 256){
					shellOF = true;
					break;
				}
				ioe_read(AM_INPUT_KEYBRD, &keyrd);
			}
			if(shellOF){
				putstr("shell buffer overflow!\n");	
				continue;
			}
			if(keyrd.keydown){
				bool hit = false;
				shell_idx = 0;
				for(int i = 0; i < 7; i++){
					if(strncmp(task_table[i].name, shell, strlen(task_table[i].name)) == 0){
						putch('\n');
						in_shell = false;
						(task_table[i].exec)();
						hit = true;
						break;
					}
				}
				if(!hit){
					putch('\n');		
					putstr(unknown);
				}
			}
    };
    return 0;
}
