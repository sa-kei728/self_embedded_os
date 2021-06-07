#include "defines.h"
#include "serial.h"
#include "lib.h"

/* set memory */
void* memset(void *begin, int charactor, long len)
{
    char*   p;
    for(p = begin; len > 0; len--) *(p++) = charactor;
    return begin;
}

/* copy memory */
void* memcpy(void* dst, const void* src, long len)
{
    char*       d = dst;
    const char* s = src;
    for(; len > 0; len--)   *(d++) = *(s++);
    return dst;
}

/* compare memory */
int memcmp(const void* begin1, const void* begin2, long len)
{
    const char* p1 = begin1;
    const char* p2 = begin2;
    for(; len > 0; len--){
        if(*p1 != *p2)  return (*p1 > *p2) ? 1 : -1;
        p1++;
        p2++;
    }

    return 0;
}

/* get string length */
int strlen(const char* s)
{
    int len;
    for(len = 0; *s; s++, len++);
    return len;
}

/* copy string */
char* strcpy(char* dst, const char* src)
{
    char* d = dst;
    for(;; dst++, src++){
        *dst = *src;
        if(!*src) break;
    }
    return d;
}

/* compare string */
int strcmp(const char* s1, const char* s2)
{
    while(*s1 || *s2){
        if(*s1 != *s2) return (*s1 > *s2) ? 1 : -1;
        s1++;
        s2++;
    }
    return 0;
}

/* compare n length string */
int strncmp(const char* s1, const char* s2, int len)
{
    while((*s1 || *s2) && (len > 0)){
        if(*s1 != *s2) return (*s1 > *s2) ? 1 : -1;
        s1++;
        s2++;
        len--;
    }
    return 0;
}

/* send 1 charactor */
int putc(unsigned char c)
{
    if(c == '\n')   serial_send_byte(SERIAL_DEFAULT_DEVICE, '\r');
    return serial_send_byte(SERIAL_DEFAULT_DEVICE, c);
}

/* send string */
int puts(unsigned char *str)
{
    while(*str) putc(*(str++));
    return 0;
}

/* send hex value */
int putxval(unsigned long value, int column)
{
    char    buf[9];    /* buffer for printing string */
    char*   p;

    /* exec Lower digit */
    p = buf + sizeof(buf) - 1;
    *(p--) = '\0';

    if(!value && column) column++;

    while(value || column){
        *(p--) = "0123456789abcdef"[value & 0xf];   /* match value charactor from constant array*/
        value >>= 4;            /* go to next digit */
        if(column) column--;    /* count column */
    }

    puts(p + 1);
    return 0;
}
