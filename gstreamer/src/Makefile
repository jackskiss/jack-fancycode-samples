# MAKEFILE

# Written By Jack

# Compile 
CC = gcc
SRC = $(wildcard *.c)
OBJECTS = $(SRC:.c=.o)
FLAGS = 
CFLAGS = -Wall
LIBS =
DIRS = .  

GSTREAMER_DIRH = -I/usr/include/gstreamer-1.0

INCLUDES = $(GSTREAMER_DIRH)

TARGET = gsample

EXECUTEBIN = $(TARGET).bin
TARGETELF = $(TARGET).elf

# Tool Option
BINTOOL = fromelf

# Build
$(TARGET) : $(TARGETELF)
	$(BINTOOL) -bin -o $@ @^

$(TARGETELF) : $(OBJECTS)
	$(CC) $(CFLAGS) $(INCLUDES) -o $@ $^

# Clean
.PHOHY : clean
	@rm *.o
	@gsample
