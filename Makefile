CC = clang
CFLAGS = -fPIC -std=c89 -pedantic -Wall -Wextra -O3 -D_GNU_SOURCE
LDFLAGS = -O3
ALLOCFLAGS =
BENCHFLAGS = -O3 -flto
TESTFLAGS = -DTEST -g

# Directories
OBJDIR = .obj
LIBDIR = lib
BINDIR = .

# Default target
all:

$(OBJDIR)/lock.o: include/lock.h src/lock.c
	$(CC) -Iinclude $(CFLAGS) -c src/lock.c -o $@



# Clean up
clean:
	rm -fr $(OBJDIR)/* $(LIBDIR)/*

# Phony targets
.PHONY: all test bench clean
