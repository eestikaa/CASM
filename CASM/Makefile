LIBDIR  = randlib
OBJDIR  = obj
LIBSRCS = $(wildcard $(LIBDIR)/*.asm)
LIBOBJS = $(LIBSRCS:$(LIBDIR)/%.asm=$(OBJDIR)/%.o)
LIBOUT  = randlib.lib
SRCS  = $(wildcard *.c)
OBJS  = $(SRCS:%.c=$(OBJDIR)/%.o)
CFLAGS = -std=c11
LIBS  = $(LIBOUT)
OUT   = War.exe

all: $(OUT)
clean:
	rm -rf $(OBJDIR) $(LIBOUT) $(OUT)
	
# declare all the autodeps
-include $(OBJDIR)/*.d
	
#ld: -Wl,-X: discard nasm locals
# OUT depends on OBJDIR, LIBOUT, C-OBJS
$(OUT): $(OBJDIR) $(LIBOUT) $(OBJS)
	gcc -Wl,-X -o $(OUT) $(OBJDIR)/*.o $(LIBS)
$(OBJDIR)/%.o: %.c
	gcc $(CFLAGS) -Wall -c $*.c -o $(OBJDIR)/$*.o -MD

$(LIBOUT): $(LIBOBJS)
	ar rcs $(LIBOUT) $(LIBOBJS)
$(OBJDIR):
	mkdir $(OBJDIR)
$(OBJDIR)/%.o: $(LIBDIR)/%.asm
	nasm -i$(LIBDIR)/ -f win32 -g $(LIBDIR)/$*.asm -o $(OBJDIR)/$*.o -MD $(OBJDIR)/$*.d
