#ifndef AM_H__
#define AM_H__

//#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>
#include <stdarg.h>
//#include "common.h"
// Memory protection flags
#define MMAP_NONE  0x00000000 // no access
#define MMAP_READ  0x00000001 // can read
#define MMAP_WRITE 0x00000002 // can write

// Memory area for [@start, @end)
typedef struct {
  void *start, *end;
} Area;

// ----------------------- TRM: Turing Machine -----------------------
extern   void*       hAddr;//add
extern   Area        heap;
//void     putch       (char ch);
//void     halt        (int code) __attribute__((__noreturn__));

// -------------------- IOE: Input/Output Devices --------------------
bool     ioe_init    (void);
void     ioe_read    (int reg, void *buf);
void     ioe_write   (int reg, void *buf);
#include "amdev.h"
#endif
