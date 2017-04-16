#the compiler
CC = gcc

#compiler options
COPTS = -O3 -g -Wall -lmingw32 -lSDLmain -lSDL -mwindows

#header files
INCLUDES = \
	-I. \
	$(NULL)

#library directories
LIBDIRS = \
	$(NULL)

#libraries to link with
LIBS = \
	$(NULL)

#all compiler flags
CFLAGS = $(COPTS) $(INCLUDES)
CFLAGS  += `pkg-config cairo --cflags`

#all linker options and libs
LFLAGS = $(LIBDIRS) $(shell sdl-config --libs)
LFLAGS += `pkg-config cairo --libs`

#default compilation rules
%.o:    %.c
	$(CC) -c $< $(CFLAGS) -o $@

#local headers to depend on
HEADERS = \
	$(NULL)

#files to compile
CCFILES = \
	sdl-clock.c     \
	$(NULL)

#all local .o files
OBJS =  ${CCFILES:.c=.o}

default: sdl-clock

sdl-clock: $(OBJS) $(HEADERS)
	$(CC) $(LFLAGS) $(OBJS) $(LIBS) -o $@

clean:
	rm -f core $(OBJS) sdl-clock *~

indent:
	indent -kr -i8 *.c

new: clean default

