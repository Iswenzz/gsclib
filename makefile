CC=gcc
ifeq ($(OS),Windows_NT)
INCLUDES=-Ideps/mysql/windows/include -Ideps/dre2 -Ideps/cgsc
LIBDIRS=-Ldeps/dre2 -Ldeps/mysql/windows/lib
LIBS=../libcom_plugin.a -ldre2 -lmysql
TARGETNAME=gsclib.dll
else
INCLUDES=-Ideps/mysql/unix/include -Ideps/dre2 -Ideps/cgsc
LIBDIRS=-Ldeps/dre2 -Ldeps/mysql/unix/lib
LIBS=../libcom_plugin.a -ldre2 -lmysqlclient
TARGETNAME=gsclib.so
endif

SRCDIR=.
OBJDIR=obj
TARGETDIR=bin

SRCS=$(shell find $(SRCDIR) -name "*.c")
OBJS=$(SRCS:$(SRCDIR)/%.c=$(OBJDIR)/%.o)
TREE=$(patsubst %/,%,$(dir $(OBJS)))
CFLAGS=-m32 -Wall -O1 -s -mtune=core2 $(INCLUDES)
LDFLAGS=-m32 -s -shared -static-libgcc -static-libstdc++ -Wl,-enable-stdcall-fixup $(LIBDIRS) $(LIBS)

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