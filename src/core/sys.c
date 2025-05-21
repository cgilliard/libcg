#include <error.h>
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

