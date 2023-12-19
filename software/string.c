#include "klib.h"
#include "common.h"
#include "klib-macros.h"
//#include <stdint.h>
//#include <stdio.h>

size_t strlen(const char *s) {
  const char* p;
  for(p = s; *p; p++);
  return p - s;
}

char *strcpy(char *dst, const char *src) {
  char* p;
  for(p = dst; *src; p++, src++)
    *p = *src;
  *p = '\0';
  return dst;
}


char *strncpy(char *dst, const char *src, size_t n) {
  size_t idx;
  char *p;
  for(idx = 0, p = dst; *src && idx < n; idx++, p++, src++)
    *p = *src;
  while(idx++ < n) *p++ = '\0';
  return dst;
}

char *strcat(char *dst, const char *src) {
  char* p;
  for(p = dst + strlen(dst); *src; p++, src++)
    *p = *src;
  *p = '\0';
  return dst;
}

int strcmp(const char *s1, const char *s2) {
  const char* p1, *p2;
  for(p1 = s1, p2 = s2; *p1 == *p2 && *p1; p1++, p2++);
  return (unsigned char)*p1 - (unsigned char)*p2;
}

int strncmp(const char *s1, const char *s2, size_t n) {
  size_t idx;
  const char* p1, *p2;
  for(idx = 0, p1 = s1, p2 = s2; *p1 == *p2 && *p1 && idx < n; idx++ , p1++, p2++);
  if(idx == n)  return 0;
  return (unsigned char)*p1 - (unsigned char)*p2;
}

void *memset(void *s, int c, size_t n) {
  for(uint8_t* temp = (uint8_t*)s + n - 1; temp >= (uint8_t*)s; temp--)
    *temp = (uint8_t)c;
  return s;
}

void *memmove(void *dst, const void *src, size_t n) {
  uint8_t* dst_temp;
  uint8_t* src_temp;
  if(dst > src && (uint8_t*)src + n > (uint8_t*)dst){
    for(dst_temp = (uint8_t*)dst + n - 1, src_temp = (uint8_t*)src + n - 1;
        dst_temp >= (uint8_t*)dst; dst_temp--, src_temp--)
      *dst_temp = *src_temp;
  }
  else{
    for(dst_temp = (uint8_t*)dst, src_temp = (uint8_t*)src; dst_temp < (uint8_t*)dst + n;
        dst_temp++, src_temp++)
      *dst_temp = *src_temp;
  }
  return dst;
}

void *memcpy(void *out, const void *in, size_t n) {
  uint8_t* out1;
  uint8_t* in1;
  for(out1 = (uint8_t*)out + n - 1, in1 = (uint8_t*)in + n - 1; out1 >= (uint8_t*)out; out1--, in1--)
    *out1 = *in1;
  return out;
}

int memcmp(const void *s1, const void *s2, size_t n) {
  size_t idx;
  for(idx = 0; *(uint8_t*)s1 == *(uint8_t*)s2 && idx < n; idx++, s1 = (void*)((uint8_t*)s1 + 1), s2 = (void*)((uint8_t*)s2 + 1));
  if(idx == n) return 0;
  return (int)*(uint8_t*)s1 - (int)*(uint8_t*)s2;
}

