# MAKEFILE

# Written By Jack

# Compile 
CC = gcc
SRC = $(wildcard *.c)
OBJECTS = $(SRC:.c=.o)
FLAGS = 
CFLAGS = -Wall
#CFLAGS=--sysroot=/
LD = gcc
LFLAGS =
#LFLAGS =  --entry main
DIRS=.  

SYSTEM_PATH =

# Sub directory search

# Gstreamer
GSTREAMER_DIRH = -I/usr/include/gstreamer-1.0 -I/usr/include/glib-2.0 -I/usr/include/glib-2.0/gobject -I/usr/include/glib-2.0/include -I/usr/lib/x86_64-linux-gnu/glib-2.0/include
GSTREAMER_LIB = -lgstreamer-1.0 -lgobject-2.0 -lglib-2.0
GSTREAMER_LIB_PATH = -L/usr/lib/x86_64-linux-gnu

SYSTEM_LIB = -lc

INCLUDES = $(GSTREAMER_DIRH)
LIBS = $(GSTREAMER_LIB) $(SYSTEM_LIB)
LIB_PATHS = $(GSTREAMER_LIB_PATH)

TARGET = gsample

EXECUTEBIN = $(TARGET).bin
TARGETELF = $(TARGET).elf

# Tool Option
BINTOOL = fromelf

# Build
#$(TARGET) : $(TARGETELF)
#	$(BINTOOL) -bin -o $@ $^

$(TARGET) : $(OBJECTS)

	@$(LD) $(LFLAGS) -o $@ $^ $(LIB_PATHS) $(LIBS)  

# Normally, it defines in makefile system. It's better to define explicit. 
%o : %c
	@$(CC) -c $(CFLAGS) $(INCLUDES) $(LIBS) -o $@ $< 

# Clean
.PHONY : clean

clean :
ifneq (, $(wildcard *.o))
	@rm *.o 
endif

# Should be defined due to prevent to define in another location
.PHONY : clean
