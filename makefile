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
	@echo -e \\t$@
ifeq ($(MAKECMDGOALS),nocgsc)
	@$(CC) $(CFLAGS) -D_NO_CGSC -o $@ -c $<
else
	@$(CC) $(CFLAGS) -o $@ -c $<
endif

.PHONY: all nocgsc install uninstall clean
all: notify main
nocgsc: notify_nocgsc main

main: $(OBJS)
	@echo Linking DLL:
	@echo -e \\t$(TARGETNAME)
	@mkdir -p $(TARGETDIR)
	@$(CC) -o $(TARGETDIR)/$(TARGETNAME) $(OBJS) $(LDFLAGS)

notify:
	@echo Compiling gsclib:
notify_nocgsc:
	@echo Compiling gsclib without CGSC features:

install:
	@echo Installing gsclib [admin required]
ifeq ($(OS),Windows_NT)
	@powershell Set-ExecutionPolicy -ExecutionPolicy RemoteSigned -Scope LocalMachine -Force;
	@powershell ./scripts/windows_setup.ps1 install;
else
	@./scripts/linux_setup.sh install
endif

uninstall:
	@echo Uninstalling gsclib [admin required]
ifeq ($(OS),Windows_NT)
	@powershell Set-ExecutionPolicy -ExecutionPolicy RemoteSigned -Scope LocalMachine -Force;
	@powershell ./scripts/windows_setup.ps1 uninstall;
else
	@./scripts/linux_setup.sh uninstall
endif

clean:
	@echo Cleaning $(OBJDIR) directory.
	@rm -f -r $(OBJDIR)