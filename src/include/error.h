#ifndef _ERROR_H__
#define _ERROR_H__

extern int err;

typedef enum { Todo = 100000, IndexOutOfBounds, IllegalArgument } Errors;

const char *error_string(int err_code);
int perror(const char *);

#endif /* _ERROR_H__ */
