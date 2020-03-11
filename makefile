CC=gcc
ifeq ($(OS),Windows_NT)
TARGETNAME=gsclib.dll
else
TARGETNAME=gsclib.so
endif

SRCDIR=.
OBJDIR=obj
TARGETDIR=bin

SRCS=$(shell find $(SRCDIR) -name "*.c")
OBJS=$(SRCS:$(SRCDIR)/%.c=$(OBJDIR)/%.o)
TREE=$(patsubst %/,%,$(dir $(OBJS)))
CFLAGS=-m32 -Wall -O1 -s -mtune=core2
LDFLAGS=-m32 -s -shared -static-libgcc -static-libstdc++ -L../ -lcom_plugin

.PHONY: all clean

all: $(OBJS)
	$(CC) -o $(TARGETDIR)/$(TARGETNAME) $(OBJS) $(LDFLAGS)

.SECONDEXPANSION:
$(OBJDIR)/%.o: $(SRCDIR)/%.c | $$(@D)
	$(CC) $(CFLAGS) -o $@ -c $<

$(TREE): %:
	mkdir -p $@

clean:
	$(RM) -r $(OBJDIR)