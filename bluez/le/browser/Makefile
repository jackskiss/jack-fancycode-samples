#Makefile

CC=g++
LFLAGS=
DEBUG=-g2
CFLAGS=-Wall $(DEBUG) 
CPPFLAGS=
LIBS=
LIBSPATH=
INCLUDES=
INCPATH=
TARGET=browser
OUTPATH=build

EXCUTABLE_BIN=$(TARGET).bin
TARGETELF=$(TARGET).elf

BINTOOL=fromelf

#include path
KERNEL_PATH = /usr/src/linux-headers-3.13.0-52
KERNEL_GEN_PATH = /usr/src/linux-headers-3.13.0-52-generic
KERNEL_INC = $(KERNEL_PATH)/include
KERNEL_GEN_INC = $(KERNEL_GEN_PATH)/include
X86_INC = $(KERNEL_PATH)/arch/x86/include
NET_PATH = $(KERNEL_INC)/net

INCPATH = -I$(KERNEL_INC) -I$(X86_INC) -I$(NET_PATH) -I$(KERNEL_GEN_INC)

C_SRC=$(wildcard *.c)

#Wildcard is a fuction to get list of the files from the directory
CPP_SRC=$(wildcard *.cpp)
OBJECTS=$(C_SRC:.c=.o)

# Suffix source for $^ target for $@
$(TARGET): $(OBJECTS)
	@(LD) $(LFLAGS) $(LIBSPATH) $(LIBS) -o $@ $^ 

#$(OUTPATH)/%.o: %.c
%.o: %.c
	@$(CC) -c $(CFLAGS) $(INCPATH) -o $@ $< 

.PHONY:clean

clean:
ifneq (, $(wildcard, *.o))
	@rm *.o
	@rm $(TARGET) 
endif

# Should be defined to protect using another place. 
.PHONY:clean

.PHONY: status

status:
	@echo Check Status of Configuration
	@echo $(INCLUDES) $(INCPATH)
