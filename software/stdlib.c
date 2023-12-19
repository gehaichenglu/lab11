#include "am.h"
#include "common.h"
#include "klib.h"
#include "klib-macros.h"
unsigned int __mulsi3(unsigned int a, unsigned int b);
unsigned int __udivsi3(unsigned int a, unsigned int b);
unsigned int __umodsi3(unsigned int a, unsigned int b);

static unsigned long int next = 1;

int rand(void) {
  // RAND_MAX assumed to be 32767
  next = __mulsi3(next,1103515245) + 12345;
  return (unsigned int)__umodsi3(__udivsi3(next,65536), 32768);
}

void srand(unsigned int seed) {
  next = seed;
}

int abs(int x) {
  return (x < 0 ? -x : x);
}

int atoi(const char* nptr) {
  int x = 0;
  while (*nptr == ' ') { nptr ++; }
  while (*nptr >= '0' && *nptr <= '9') {
    x = __mulsi3(x, 10) + *nptr - '0';
    nptr ++;
  }
  return x;
}

char* itoa(int num, char* buffer, int radix, bool usigned){ // I add this function to for convenience. When radix is bigger than 36, return NULL;
  char buffer_temp[128];
  int idx = 0;
  bool flag = false;// this flag is used to check whether n is negtive or not in decimal;
  if(radix == 10 && num < 0 && !usigned)
    flag = true, num = -num;
  uint32_t n = (uint32_t)num;
  if(n == 0){
    buffer[0] = '0';
    buffer[1] = '\0';
    return buffer;
  }
  while(n){ // when n isn't zero;
    int remainder = __umodsi3(n,radix);
    if(remainder <= 9)
      buffer_temp[idx++] = remainder + '0';
    else if(remainder >= 10 && remainder < 36)
      buffer_temp[idx++] = remainder - 10 + 'a';

    n = __udivsi3(n, radix);
  }
  if(flag) buffer_temp[idx++] = '-';
  buffer[idx--] = '\0';
  for(int i = 0; idx >= 0; i++, idx--)
    buffer[i] = buffer_temp[idx];

  return buffer;
}

void *hAddr;
void *malloc(size_t size) {
  if(hAddr + size >= heap.end)
    return NULL;
  void* temp = hAddr;
  hAddr = (void*)ROUNDUP(hAddr + size, 8);
  return temp;
}
void free(void *ptr) {

}
