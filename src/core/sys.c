#include <error.h>

#ifdef __linux__
long syscall_wrapper(long id, ...);
__asm__(
    "syscall_wrapper:\n"
    "    movq %rdi, %rax\n"
    "    movq %rsi, %rdi\n"
    "    movq %rdx, %rsi\n"
    "    movq %rcx, %rdx\n"
    "    movq %r8, %r10\n"
    "    movq %r9, %r8\n"
    "    movq 8(%rsp), %r9\n"
    "    syscall\n"
    "    ret\n");
#endif

#ifdef __linux__
#define DECLARE_SYSCALL(name, linux_num, macos_num, ...) \
	int syscall_##name(__VA_ARGS__) { return syscall_wrapper(linux_num); }
#elif defined(__APPLE__)
#define DECLARE_SYSCALL(name, linux_num, macos_num, ...) \
	int syscall_##name(__VA_ARGS__);                 \
	__asm__(".global _syscall_" #name                \
		"\n"                                     \
		"_syscall_" #name                        \
		":\n"                                    \
		"    sub sp, sp, #32\n"                  \
		"    str x30, [sp]\n"                    \
		"    mov x16, #" #macos_num              \
		"\n"                                     \
		"    orr x16, x16, #0x2000000\n"         \
		"    svc #0x80\n"                        \
		"    b.cc 1f\n"                          \
		"    neg x0, x0\n"                       \
		"1:  ldr x30, [sp]\n"                    \
		"    add sp, sp, #32\n"                  \
		"    ret\n");
#endif /* __APPLE__ */

DECLARE_SYSCALL(sched_yield, 24, 158, void)
int sched_yield(void) {
	int v = syscall_sched_yield();
	if (v < 0) {
		err = -v;
		return -1;
	}
	return v;
}
