#include <error.h>
#include <sys/mman.h>
#include <types.h>

#ifdef __linux__
#define DECLARE_SYSCALL(ret_type, name, linux_num, macos_num, ...) \
	ret_type syscall_##name(__VA_ARGS__);                      \
	__asm__(".global syscall_" #name                           \
		"\n"                                               \
		"syscall_" #name                                   \
		":\n"                                              \
		"    movq $" #linux_num                            \
		", %rax\n"                                         \
		"    syscall\n"                                    \
		"    ret\n");
#elif defined(__APPLE__)
#define DECLARE_SYSCALL(ret_type, name, linux_num, macos_num, ...) \
	ret_type syscall_##name(__VA_ARGS__);                      \
	__asm__(".global _syscall_" #name                          \
		"\n"                                               \
		"_syscall_" #name                                  \
		":\n"                                              \
		"    sub sp, sp, #16\n"                            \
		"    str x30, [sp]\n"                              \
		"    mov x16, #" #macos_num                        \
		"\n"                                               \
		"    orr x16, x16, #0x2000000\n"                   \
		"    svc #0x80\n"                                  \
		"    b.cc 1f\n"                                    \
		"    neg x0, x0\n"                                 \
		"1:  ldr x30, [sp]\n"                              \
		"    add sp, sp, #16\n"                            \
		"    ret\n");
#endif

#define IMPL_WRAPPER(ret_type, name, ...)         \
	ret_type v = syscall_##name(__VA_ARGS__); \
	if (v < 0) {                              \
		err = -v;                         \
		return -1;                        \
	}                                         \
	return v;

DECLARE_SYSCALL(int, sched_yield, 24, 158, void)

DECLARE_SYSCALL(ssize_t, write, 1, 4, int fd, const void *buf, size_t length)

DECLARE_SYSCALL(void, exit, 60, 1, int code)

DECLARE_SYSCALL(void *, mmap, 9, 197, void *addr, size_t length, int prot,
		int flags, int fd, off_t offset)

DECLARE_SYSCALL(int, munmap, 11, 73, void *addr, size_t length)

DECLARE_SYSCALL(long, getpagesize, 137, 33, void)

int sched_yield(void) {
	int v = syscall_sched_yield();
	if (v < 0) {
		err = -v;
		return -1;
	}
	return v;
}

ssize_t write(int fd, const void *buf, size_t length) {
	IMPL_WRAPPER(ssize_t, write, fd, buf, length)
}

void exit(int code) {
	syscall_exit(code);
	while (true);
}

void *mmap(void *addr, size_t length, int prot, int flags, int fd,
	   off_t offset) {
	write(2, "1\n", 2);
	void *v = syscall_mmap(addr, length, prot, flags, fd, offset);
	write(2, "2\n", 2);
	return v;
}

int munmap(void *addr, size_t length) {
	IMPL_WRAPPER(int, munmap, addr, length)
}

long getpagesize(void) {
	write(2, "3\n", 2);
	long v = syscall_getpagesize();
	if (v < 0) {
		err = -v;
		return -1;
	}
	write(2, "4\n", 2);
	return v;
}
