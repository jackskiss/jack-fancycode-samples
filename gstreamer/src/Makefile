# MAKEFILE

# Written By Jack

# Compile 
CC = gcc
SRC = $(wildcard *.c)
OBJECTS = $(SRC:.c=.o)
FLAGS = 
CFLAGS = -Wall --sysroot=/
#CFLAGS=--sysroot=/
LD = ld
LFLAGS = 
DIRS=.  

SYSTEM_PATH =

# Gstreamer
GSTREAMER_DIRH = -I/usr/include/gstreamer-1.0 -I/usr/include/glib-2.0 -I/usr/include/glib-2.0/include -I/usr/lib/x86_64-linux-gnu/glib-2.0/include
GSTREAMER_LIB = -lgstreamer-1.0
GSTREAMER_LIB_PATH =

INCLUDES = $(GSTREAMER_DIRH)
LIBS = $(GSTREAMER_LIB)

TARGET = gsample

EXECUTEBIN = $(TARGET).bin
TARGETELF = $(TARGET).elf

# Tool Option
BINTOOL = fromelf

# Build
#$(TARGET) : $(TARGETELF)
#	$(BINTOOL) -bin -o $@ $^

$(TARGET) : $(OBJECTS)
	$(LD) -o $@ $^ $(LIBS) 

#	exit
#	echo	$(INCLUDES) 
#	$(CC) $(CFLAGS) $(INCLUDES) -o $@ $^

# Normally, it defines in makefile system. It's better to define explicit. 
%o : %c
	$(CC) -c $(CFLAGS) $(INCLUDES) $(LIBS) -o $@ $<
# Clean
#.PHOHY : clean
#	@rm *.o
#	@gsample