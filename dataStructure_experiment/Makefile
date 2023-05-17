CC=gcc
CFLAGS=-I.
DEPS = csv.h avlTree.h
OBJ = main.o csv.o avlTree.o

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

main: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS)

.PHONY: clean

clean:
	rm -f $(OBJ) main

