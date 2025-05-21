#include <misc.h>
#include <types.h>

void *memset(void *ptr, int x, size_t n) {
	set_bytes(ptr, x, n);
	return ptr;
}

void *memcpy(void *dst, const void *src, size_t n) {
	copy_bytes((byte *)dst, (const byte *)src, n);
	return dst;
}

void bzero(void *dst, size_t n) { set_bytes((byte *)dst, 0, n); }
