#include <error.h>
#include <types.h>

int syscall_sched_yield(void);
#ifdef __linux__
__asm__(
    "_syscall_sched_yield:\n"
    "    movq $24, %rax\n"
    "    syscall\n"
    "    ret\n");
#elif defined(__APPLE__)
__asm__(
    "_syscall_sched_yield:\n"
    "    sub sp, sp, #16\n"
    "    str x30, [sp]\n"
    "    mov x16, #158\n"
    "    orr x16, x16, #0x2000000\n"
    "    svc #0x80\n"
    "    b.cc 1f\n"
    "    neg x0, x0\n"
    "1:  ldr x30, [sp]\n"
    "    add sp, sp, #16\n"
    "    ret\n");
#endif /* __APPLE__ */

int sched_yield(void) {
	int v = syscall_sched_yield();
	if (v < 0) {
		err = -v;
		return -1;
	}
	return v;
}

ssize_t syscall_write(int fd, void *buf, size_t length);
#ifdef __linux__
__asm__(
    "_syscall_write:\n"
    "    movq $1, %rax\n"
    "    syscall\n"
    "    ret\n");
#elif defined(__APPLE__)
__asm__(
    "_syscall_write:\n"
    "    sub sp, sp, #16\n"
    "    str x30, [sp]\n"
    "    mov x16, #4\n"
    "    orr x16, x16, #0x2000000\n"
    "    svc #0x80\n"
    "    b.cc 1f\n"
    "    neg x0, x0\n"
    "1:  ldr x30, [sp]\n"
    "    add sp, sp, #16\n"
    "    ret\n");
#endif /* __APPLE__ */

ssize_t write(int fd, void *buf, size_t length) {
	ssize_t v = syscall_write(fd, buf, length);
	if (v < 0) {
		err = -v;
		return -1;
	}
	return v;
}
