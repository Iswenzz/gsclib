CC=gcc
ifeq ($(OS),Windows_NT)
INCLUDES=-Ideps/mysql/windows/include -Ideps/dre2 -Ideps/cgsc -Ideps/curl/windows/include
LIBDIRS=-Ldeps/dre2 -Ldeps/mysql/windows/lib -Ldeps/curl/windows/lib
LIBS=../libcom_plugin.a -ldre2 -lmysql -lcurl
TARGETNAME=gsclib.dll
OSFLAG=-Wl,-enable-stdcall-fixup
else
INCLUDES=-Ideps/mysql/unix/include -Ideps/dre2 -Ideps/cgsc -Ideps/curl/unix/include
LIBDIRS=-Ldeps/dre2 -Ldeps/mysql/unix/lib -Ldeps/curl/unix/lib
LIBS=-ldre2 -lmysqlclient -lcurl
TARGETNAME=gsclib.so
OSFLAG=
endif

SRCDIR=.
OBJDIR=obj
TARGETDIR=bin

SRCS=$(shell find $(SRCDIR) -name "*.c")
OBJS=$(SRCS:$(SRCDIR)/%.c=$(OBJDIR)/%.o)
CFLAGS=-m32 -Wall -Wno-missing-braces -O1 -s -mtune=core2 $(INCLUDES)
LDFLAGS=-m32 -s -shared -static-libgcc -static-libstdc++ $(OSFLAG) $(LIBDIRS) $(LIBS)

# C build rule
$(OBJDIR)/%.o: $(SRCDIR)/%.c
	@mkdir -p $(@D)
	@echo $@
	@$(CC) $(CFLAGS) -o $@ -c $<

.PHONY: all install uninstall clean

all: $(OBJS)
	@echo -e \\nLinking DLL\\n
	@echo $(TARGETNAME)
	@mkdir -p $(TARGETDIR)
	@$(CC) -o $(TARGETDIR)/$(TARGETNAME) $(OBJS) $(LDFLAGS)

install:
	@echo "installing gsclib [admin required]"
ifeq ($(OS),Windows_NT)
	@powershell Set-ExecutionPolicy -ExecutionPolicy RemoteSigned -Scope LocalMachine -Force;
	@powershell ./scripts/windows_setup.ps1 install;
else
	@./scripts/linux_setup.sh install
endif

uninstall:
	@echo "uninstalling gsclib [admin required]"
ifeq ($(OS),Windows_NT)
	@powershell Set-ExecutionPolicy -ExecutionPolicy RemoteSigned -Scope LocalMachine -Force;
	@powershell ./scripts/windows_setup.ps1 uninstall;
else
	@./scripts/linux_setup.sh uninstall
endif

clean:
	@rm -r $(OBJDIR)