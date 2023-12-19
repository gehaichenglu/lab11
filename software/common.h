#ifndef COMMON_H__                                                                                                                             
#define COMMON_H__
typedef  unsigned char uint8_t;
typedef unsigned short	uint16_t ;
typedef unsigned int uint32_t ;
typedef unsigned long long uint64_t ;
typedef unsigned int uintptr_t ;
typedef long long int64_t;

unsigned int __mulsi3(unsigned int a, unsigned int b);
unsigned int __umodsi3(unsigned int a, unsigned int b);
unsigned int __udivsi3(unsigned int a, unsigned int b);
unsigned long long __umodsi6(unsigned long long a, unsigned long long b);
unsigned long long __udivsi6(unsigned long long a, unsigned long long b);

#include "am.h"  
extern Area heap;
#include "klib-macros.h"
#include "klib.h"
#include "amdev.h"
#endif
