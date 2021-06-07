PREFIX  = /usr/local
ARCH	= h8300-elf
BINDIR	= $(PREFIX)/bin
ADDNAME	= $(ARCH)-

AR		= $(BINDIR)/$(ADDNAME)ar
AS		= $(BINDIR)/$(ADDNAME)as
GCC		= $(BINDIR)/$(ADDNAME)gcc
LD		= $(BINDIR)/$(ADDNAME)ld
NM		= $(BINDIR)/$(ADDNAME)nm
OBJCOPY	= $(BINDIR)/$(ADDNAME)objcopy
OBJDUMP	= $(BINDIR)/$(ADDNAME)objdump
RANLIB	= $(BINDIR)/$(ADDNAME)ranlib
STRIP	= $(BINDIR)/$(ADDNAME)strip

OBJS	= startup.o main.o
OBJS   += lib.o serial.o

TARGET	= kozos

CFLAGS	= -Wall -mh -nostdinc -nostdlib -fno-builtin -lgcc
#CFLAGS += -mint32 # can't mul/div , in case of int=32bit 
CFLAGS += -I.
#CFLAGS += -g
CFLAGS += -Os
CFLAGS += -DKOZOS

LFLAGS	= -static -T ld.scr -L.

.SUFFIXES: .c .o
.SUFFIXES: .s .o

all:	$(TARGET)

$(TARGET):		$(OBJS)
				$(GCC) $(OBJS) -o $(TARGET) $(CFLAGS) $(LFLAGS)
				cp $(TARGET) $(TARGET).elf
				$(STRIP) $(TARGET)

.c.o:			$<
				$(GCC) -c $(CFLAGS) $<

.s.o:			$<
				$(GCC) -c $(CFLAGS) $<

clean:
				rm -f $(OBJS) $(TARGET) $(TARGET).elf
