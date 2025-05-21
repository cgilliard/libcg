#ifndef _MISC_H__
#define _MISC_H__

#include <types.h>

void copy_bytes(byte *dest, const byte *src, size_t n);
void set_bytes(byte *dst, byte b, size_t n);
size_t cstring_len(const char *S);
int cstring_compare(const char *s1, const char *s2);
int cstring_compare_n(const char *s1, const char *s2, size_t n);
const char *cstring_strstr(const char *X, const char *Y);

#endif /* _MISC_H__ */
