CC      = clang
CFLAGS  = -fPIC \
	 -std=c89 \
	 -pedantic \
	 -Wall \
	 -Wextra \
	 -O3 \
	 -D_GNU_SOURCE \
	 -Wno-variadic-macros \
	 -Wno-long-long \
	 -fno-builtin
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

$(LIBDIR)/libcg.so: $(OBJECTS) | $(LIBDIR)
	$(CC) $(LDFLAGS) -o $@ $(OBJECTS)

# Clean up
clean:
	rm -fr $(OBJDIR)/* $(LIBDIR)/*

# Phony targets
.PHONY: all test bench clean
