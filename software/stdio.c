#include "am.h"                                                                                                                               
#include "klib.h"
#include "klib-macros.h"
#include <stdarg.h>
#include "sys.h"
#define size_of_print_buffer 1024
char pbuffer[size_of_print_buffer];

int printf(const char *fmt, ...) {
  //panic("Not implemented");
	memset(pbuffer, 0, sizeof(pbuffer));
  va_list ap;
  va_start(ap, fmt);
  int n = vsprintf(pbuffer, fmt, ap);
  putstr(pbuffer);
  va_end(ap);
  return n;
}
int vsprintf(char *out, const char *fmt, va_list ap) {
  //panic("Not implemented");
    int d;
    char* s = NULL;
    char* fmt_temp = (char*)fmt;
    char* out_temp = out;
    char buffer[128];
    int i;

//    double f;
    while(*fmt_temp){
      bool capital = false;
      bool lr_align = false;
      bool zd_type = false;
      bool inloop = true;
      int n = 0;
      int m = 0;
      bool get_m = false;
      int len;
      switch(*fmt_temp){
        case '%':{  // format
                  do{
                  fmt_temp++;
                  switch(*fmt_temp){
                    case '-': lr_align = true;break;
                    case '.': case '0': zd_type = true; break;
                    default:{
                            if(*fmt_temp >= '0' && *fmt_temp <= '9'){
                              if(!get_m){
                                m = atoi(fmt_temp);
                                get_m = true;
                              }
                              else{
                                n = atoi(fmt_temp);
                              }
                              while(*fmt_temp >= '0' && *fmt_temp <= '9') fmt_temp++;
                            }
                            if(*fmt_temp != '.') 
                              inloop = false;
                            
                        }
                    }
                  }while(inloop);

                  if(n == 0) {n = m; m = 0;}
                  switch(*fmt_temp){
                      case 'd':
                        d = va_arg(ap, int);
                        s = itoa(d, buffer, 10, false);
                        break;
                      case 'p': case 'x':
                        d = va_arg(ap, int);
                        s = itoa(d, buffer, 16, false);
                        break;
                      case 'X':
                        capital = true;break;                   
                      case 'u':
                        d = va_arg(ap, int);
                        s = itoa(d, buffer, 10, true);
                        break;
                      case 'c':
                        *out_temp++ = (char)va_arg(ap, int);
                        break;
                      case 's':
                          s = va_arg(ap, char*);
                        break;
                      case '%':
                        *out_temp++ = '%'; break;
                      case 'n':
                        *out_temp++ = '\n'; break;
                      default: ;
                   }
                   out_temp[0] = '\0'; // the strcat function firstly get the len of out_temp;a
                   len = strlen(s);
                   if( n != 0){
                     while(m-- > n) *out_temp++ = ' ';
                      if(!lr_align){
                        while(n - len > 0){
                          *out_temp++ = zd_type ? '0' : ' ';
                          n--;
                        }
                      }
                   }
                   
                   if(capital){
                    for(i = 0; i < len; i++){
                      if(*(s + i) >= 'a' && *(s + i) <= 'z')
                        *(s + i) += 'A' - 'a';
                    }
                   }
                   strcat(out_temp, s);
                   if(lr_align){
                     while(n - len > 0){
                        *out_temp++ = ' ';
                        n--;
                     }
                   }
                   out_temp += len;
                   fmt_temp++;
                   break;
                 }
        case '\\':{
                   fmt_temp++;
                    switch(*fmt_temp){
                      case '0':*out_temp++ = '\0';break;
                     case 'n':*out_temp++ = '\n';break;
                     case 't':*out_temp++ = '\t';break;
                     case 'r':*out_temp++ = '\r';break;
                     case '\'':*out_temp++ = '\'';break;
                     case '\"':*out_temp++ = '\"';break;
                     case '\\':*out_temp++ = '\\';break;
                     default: ;
                   }
                   fmt_temp++;
                   break;
                }
     default:*out_temp++ = *fmt_temp++;break;
    }
  }
  *out_temp = '\0';
  return out_temp - out;
}
int sprintf(char *out, const char *fmt, ...) {
  //panic("Not implemented");
  va_list ap;
  va_start(ap, fmt);
  int n = vsprintf(out, fmt, ap);
  va_end(ap);
  return n;
}

int snprintf(char *out, size_t n, const char *fmt, ...) {
  //panic("Not implemented");
  va_list ap;
  va_start(ap, fmt);
  int m = vsnprintf(out, n, fmt, ap);
  va_end(ap);
  return m;
}

int vsnprintf(char *out, size_t n, const char *fmt, va_list ap) {
  //panic("Not implemented");
  vsprintf( out, fmt, ap);
  *(out + n) = '\0';
  return strlen(out);
}

