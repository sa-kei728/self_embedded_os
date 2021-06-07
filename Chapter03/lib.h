#ifndef _LIB_H_INCLUDED_
#define _LIB_H_INCLUDED_

void*   memset(void *begin, int charactor, long len);
void*   memcpy(void* dst, const void* src, long len);
int     memcmp(const void* begin1, const void* begin2, long len);
int     strlen(const char* s);
char*   strcpy(char* dst, const char* src);
int     strcmp(const char* s1, const char* s2);
int     strncmp(const char* s1, const char* s2, int len);

int putc(unsigned char c);
int puts(unsigned char *str);
int putxval(unsigned long value, int column);

#endif /* _LIB_H_INCLUDED_ */
