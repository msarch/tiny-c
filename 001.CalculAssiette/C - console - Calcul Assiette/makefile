# makefile :2008-09-07.µ5
# projet : assiette


CC=gcc
EXEC=assiette
LDFLAGS=-lconio
CFLAGS=-W -Wall -ansi -pedantic

SRC= $(wildcard *.c)
OBJ= $(SRC:.c=.o)

all: $(EXEC)
$(EXEC): $(OBJ) 
	$(CC) -o $@ $^ $(LDFLAGS) 
%.o: %.c
	$(CC) -o $@ -c $< $(CFLAGS) 

.PHONY: clean mrproper

clean:
	@rm -rf *.o
	
mrproper: clean
	@rm -rf $(EXEC)
	