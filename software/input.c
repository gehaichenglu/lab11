#include "common.h"
#include "sys.h"

#define KEYDOWN_MASK 0x8000
int KBD_RD();
extern char scantokey[];
void __am_input_keybrd(AM_INPUT_KEYBRD_T *kbd) {
	uint32_t k = AM_KEY_NONE;
	int rd = KBD_RD();
	if(rd == -1){
		k = AM_KEY_NONE;
		kbd->keycode = k & ~KEYDOWN_MASK;
		kbd->keydown = false;
		return;
	}
	else if(rd == 0xf0){
		kbd->keydown = false;
		rd = KBD_RD();
		while(rd == -1) rd = KBD_RD();
		if(rd == 0xe0) rd = KBD_RD();
		while(rd == -1) rd = KBD_RD;
		kbd->keycode = scantokey[rd] & ~KEYDOWN_MASK;
		return;
	}
	k = scantokey[rd] & ~KEYDOWN_MASK;
	kbd->keycode = k & ~KEYDOWN_MASK;
	kbd->keydown = true;
	return;
}
