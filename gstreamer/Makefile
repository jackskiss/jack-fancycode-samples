# Master Makefile

DIR = src
OBJECTS = src.o
TARGET = sample

all : objs
	
objs : 
	@for dir in $(DIR); do \
	make -C $$ dir
	done

# using vpath
# TOPDIR = c:/project
# vpath %.c $(TOPDIR)
# vpath %.h $(TOPDIR)


