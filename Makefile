CC      = clang
CFLAGS  = -fPIC \
	 -std=c89 \
	 -pedantic \
	 -Wall \
	 -Wextra \
	 -O3 \
	 -D_POSIX_C_SOURCE=200809L \
	 -Wno-variadic-macros \
	 -Wno-c2x-extensions
LDFLAGS = -shared

# Directories
OBJDIR  = .obj
LIBDIR  = lib
BINDIR  = .
INCLDIR = src/include
SRCDIR  = src

SOURCES = $(wildcard $(SRCDIR)/core/*.c)
OBJECTS = $(patsubst $(SRCDIR)/core/%.c,$(OBJDIR)/%.o,$(SOURCES))

# Default target
all: $(LIBDIR)/libcg.so

$(OBJDIR)/%.o: $(SRCDIR)/core/%.c $(INCLDIR)/%.h
	$(CC) -I$(INCLDIR) $(CFLAGS) -c $< -o $@

$(OBJDIR)/stubs.o: $(SRCDIR)/core/stubs.c
	$(CC) -I$(INCLDIR) $(CFLAGS) -c $< -o $@

$(LIBDIR)/libcg.so: $(OBJECTS) | $(LIBDIR)
	$(CC) $(LDFLAGS) -o $@ $(OBJECTS)

# Clean up
clean:
	rm -fr $(OBJDIR)/* $(LIBDIR)/*

# Phony targets
.PHONY: all test bench clean
