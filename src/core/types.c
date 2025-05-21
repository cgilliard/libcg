#include <types.h>

int printf(const char *, ...);
void exit(int);

#define CheckType(t, exp)                                                 \
	if (sizeof(t) != exp) {                                           \
		printf("expected sizeof(%s) == %d, Found %lu\n", #t, exp, \
		       sizeof(t));                                        \
		exit(-1);                                                 \
	}

#define CheckEndian()                                                \
	uint16_t test = 0x1234;                                      \
	uint8_t *bytes = (uint8_t *)&test;                           \
	if (bytes[0] != 0x34) {                                      \
		printf("Error: Big-endian systems not supported\n"); \
		exit(-1);                                            \
	}

static __attribute__((constructor)) void check_sizes(void) {
	CheckEndian();
	CheckType(uint8_t, 1);
	CheckType(int8_t, 1);
	CheckType(uint16_t, 2);
	CheckType(int16_t, 2);
	CheckType(uint32_t, 4);
	CheckType(int32_t, 4);
	CheckType(uint64_t, 8);
	CheckType(int64_t, 8);
	CheckType(uint128_t, 16);
	CheckType(int128_t, 16);
	CheckType(byte, 1);
	CheckType(unsigned long, 8);
	CheckType(size_t, 8);
	CheckType(ssize_t, 8);
	if (!true) {
		printf("expected true to be true\n");
		exit(-1);
	}
	if (false) {
		printf("expected false to be false\n");
		exit(-1);
	}
	if (!true) {
		printf("expected true to be true\n");
		exit(-1);
	}
}

