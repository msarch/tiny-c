# makefile :2008-09-08.µ5
# projet : ascii

#ne fonctionne pas pour bin ni obj ????


CC=gcc
EXEC=ascii
LDFLAGS=-lconio
CFLAGS=-Wall -ansi -pedantic
SRC_DIR=src
OBJ_DIR=obj
EXE_DIR=bin

SRC= $(wildcard $(SRC_DIR)/*.c)
OBJ= $(SRC:$(SRC_DIR)/.c=$(OBJ_DIR)/.o)

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
	