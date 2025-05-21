#include <misc.h>
#include <types.h>

void copy_bytes(byte *dst, const byte *src, size_t n) {
	if (dst == NULL || src == NULL || n == 0) return;
	while (n--) *dst++ = *src++;
}

size_t strlen(const char *X) {
	const char *Y;
	if (X == NULL) return 0;
	Y = X;
	while (*X) X++;
	return X - Y;
}

int cstring_compare(const char *X, const char *Y) {
	if (X == NULL || Y == NULL) {
		if (X == Y) return 0;
		return X == NULL ? -1 : 1;
	}
	while (*X == *Y && *X) {
		X++;
		Y++;
	}
	if ((byte)*X > (byte)*Y) return 1;
	if ((byte)*Y > (byte)*X) return -1;
	return 0;
}

int cstring_compare_n(const char *X, const char *Y, size_t n) {
	if (X == NULL || Y == NULL) {
		if (X == Y) return 0;
		return X == NULL ? -1 : 1;
	}
	while (n > 0 && *X == *Y && *X != '\0') {
		X++;
		Y++;
		n--;
	}
	if (n == 0) return 0;
	return (byte)*X - (byte)*Y;
}

const char *cstring_strstr(const char *X, const char *Y) {
	if (X == NULL || Y == NULL) {
		if (Y == NULL || *Y == '\0') return NULL;
		return NULL;
	}
	for (; *X; X++) {
		const char *tmpX = X, *tmpY = Y;
		while (*(byte *)tmpX == *(byte *)tmpY && *tmpX) {
			tmpX++;
			tmpY++;
		}
		if (*tmpY == '\0') return X;
	}
	return NULL;
}

void *memset(void *dest, int c, size_t n) {
	size_t i;
	unsigned char *s = dest;
	for (i = 0; i < n; i++) {
		s[i] = (unsigned char)c;
	}
	return dest;
}

void *memcpy(void *dest, const void *src, size_t n) {
	size_t i;
	unsigned char *d = dest;
	const unsigned char *s = src;
	for (i = 0; i < n; i++) {
		d[i] = s[i];
	}
	return dest;
}

void write_uint64(int fd, uint64_t num) {
	char buf[32];
	int i = 0, j;

	do {
		buf[i++] = '0' + (num % 10);
		num /= 10;
	} while (num && i < 31);

	for (j = 0; j < i / 2; j++) {
		char tmp = buf[j];
		buf[j] = buf[i - 1 - j];
		buf[i - 1 - j] = tmp;
	}

	buf[i++] = '\n';

	write(fd, buf, i);
}
