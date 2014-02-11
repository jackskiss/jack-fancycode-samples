CC = gcc
CROSS_COMPILE = arm-linux-gnueabihf-
AR = ar

# Your Toolchain
PREFIX = $(HOME)/toolchains/gcc-linaro-arm-linux-gnueabihf-4.7-2013.03-20130313_linux/bin/
ROOT = .
OBJ_DIR = ./obj

# Your sysroot
ROOTFS = $(HOME)/targetfs/TI/OMAP5/6.03

RELEASE_DIR = $(ROOT)

CONFIGS += -DTEST

CC_WARNINGS += -W
CC_WARNINGS += -Wall
CC_WARNINGS += -Wextra
CC_WARNINGS += -Wformat
CC_WARNINGS += -Wuninitialized
CC_WARNINGS += -Wmissing-declarations
CC_WARNINGS += -Wmissing-prototypes
CC_WARNINGS += -Wmissing-braces
#CC_WARNINGS += -Wredundant-decls
CC_WARNINGS += -Wshadow
CC_WARNINGS += -Wbad-function-cast
CC_WARNINGS += -Wcast-qual
CC_WARNINGS += -Wunused-value
CC_WARNINGS += -Wunused-variable
CC_WARNINGS += -Wunused-result
CC_WARNINGS += -Wunused-parameter
CC_WARNINGS += -Wunused-label
CC_WARNINGS += -Wunused-function
CC_WARNINGS += -Wno-cast-align
CC_WARNINGS += -Wparentheses
CC_WARNINGS += -Wsign-compare
CC_WARNINGS += -Wswitch
CC_WARNINGS += -Wunknown-pragmas
CC_WARNINGS += -Wdeclaration-after-statement
CC_WARNINGS += -Wlong-long
CC_WARNINGS += -pedantic

CC_SWITCHES = \
$(CC_WARNINGS) \
-O3 \
-pg \
-std=c99 \
$(CONFIGS)

INCLUDES = \
	-I $(RELEASE_DIR)/inc

#--------------------------- Objects ---------------------------
TEST_SRC = \
	$(RELEASE_DIR)/src/main.c

test:$(TEST_SRC)
	$(PREFIX)$(CROSS_COMPILE)$(CC) $(CC_SWITCHES) $(INCLUDES) $(TEST_SRC) -L. -o main.out

clean:
	rm -f main.out
