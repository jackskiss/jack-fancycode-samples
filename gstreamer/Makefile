# MAKEFILE

# Written By Jack

# Compile 
CC = gcc
SRC = $(wildcard *.c)
OBJECTS = $(SRC:.c=.o)
FLAGS = 
CFLSGS = -Wall
LIBS =
DIRS = .  
INCLUDES =

TARGET = gsample

EXECUTEBIN = $(TARGET).bin
TARGETELF = $(TARGET).elf

# Tool Option
BINTOOL = fromelf

# Build
$(TARGET) : $(TARGETELF)
$(BINTOOL) -bin -o $@ @^

$(TARGETELF) : $(OBJECTS)
$(CC) -o $@ $^

# Clean
.PHOHY : clean
	@rm *.o
	@gsample
