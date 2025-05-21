CC = clang
CFLAGS = -fPIC \
	 -std=c89 \
	 -pedantic \
	 -Wall \
	 -Wextra \
	 -O3 \
	 -D_POSIX_C_SOURCE=200809L \
	 -Wno-variadic-macros \
	 -Wno-c2x-extensions \
	 -Wno-gnu-zero-variadic-macro-arguments
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

$(OBJDIR)/sys.o: $(INCLDIR)/sys.h $(SRCDIR)/core/sys.c
	$(CC) -I$(INCLDIR) $(CFLAGS) -c $(SRCDIR)/core/sys.c -o $@

$(OBJDIR)/error.o: $(INCLDIR)/error.h $(SRCDIR)/core/error.c
	$(CC) -I$(INCLDIR) $(CFLAGS) -c $(SRCDIR)/core/error.c -o $@

$(LIBDIR)/libcg.so: $(OBJDIR)/lock.o $(OBJDIR)/sys.o $(OBJDIR)/error.o
	$(CC) $(LDFLAGS) -shared -o $@ $(OBJDIR)/*.o

# Clean up
clean:
	rm -fr $(OBJDIR)/* $(LIBDIR)/*

# Phony targets
.PHONY: all test bench clean
