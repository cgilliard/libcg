#ifndef _SYS_H__
#define _SYS_H__

#include <types.h>

ssize_t write(int fd, const void *buf, size_t length);
int sched_yield(void);

#endif /* _SYS_H__ */
