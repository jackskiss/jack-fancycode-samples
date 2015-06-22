#Makefile

CC=g++
C_SRC=$(wildcard *.c)

#Wildcard is a fuction to get list of the files from the directory
CPP_SRC=$(wildcard *.cpp)
OBJECTS=$(C_SRC:.c=.o)

LFLAGS=
DEBUG=-g2
CFLAGS=-Wall $(DEBUG) 
CPPFLAGS=
LIBS=
LIBSPATH=
INCLUDES=
INCPATH=
TARGET=browser
OUTPATH=

EXCUTABLE_BIN=$(TARGET).bin
TARGETELF=$(TARGET).elf

BINTOOL=fromelf


# Suffix source for $^ target for $@
$(TARGET) : $(OBJECTS)
	@(LD) $(LFLAGS) $(LIBSPATH) $(LIBS) -o $@ $^ 


%o : %c
	@$(CC) $(CFLAGS) $(INCPATH) $(INCLUDES) -o $@ $<

.PHONY:clean

clean:
ifneq (, $(wildcard, *.o))
	@rm *.o
	@rm $(TARGET) 
endif

# Should be defined to protect using another place. 
.PHONY:clean
