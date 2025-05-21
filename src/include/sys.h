#ifndef _SYS_H__
#define _SYS_H__

#include <types.h>

ssize_t write(int fd, const void *buf, size_t length);
int sched_yield(void);
void exit(int);
void *mmap(void *addr, size_t length, int prot, int flags, int fd,
	   off_t offset);
int munmap(void *addr, size_t length);

#endif /* _SYS_H__ */
