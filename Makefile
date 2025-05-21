CC = clang
CFLAGS = -fPIC -std=c89 -pedantic -Wall -Wextra -O3 -D_POSIX_C_SOURCE=200809L
LDFLAGS = -O3
ALLOCFLAGS =
BENCHFLAGS = -O3 -flto
TESTFLAGS = -DTEST -g

# Directories
OBJDIR  = .obj
LIBDIR  = lib
BINDIR  = .
INCLDIR = src/include
SRCDIR  = src

# Default target
all: $(LIBDIR)/libcg.so

$(OBJDIR)/lock.o: $(INCLDIR)/lock.h $(SRCDIR)/core/lock.c
	$(CC) -I$(INCLDIR) $(CFLAGS) -c $(SRCDIR)/core/lock.c -o $@

$(LIBDIR)/libcg.so: $(OBJDIR)/lock.o
	$(CC) $(LDFLAGS) -shared -o $@ $(OBJDIR)/lock.o

# Clean up
clean:
	rm -fr $(OBJDIR)/* $(LIBDIR)/*

# Phony targets
.PHONY: all test bench clean
