CC = gcc # Compiler
CFLAGS = -Wall -Wextra -fPIC -c # C compiler flags
LDFLAGS = -lncursesw # Linker flags

all: ant run # run will automatically run ant with a VARIANT passed in

ant: main.o visualiser.o langton.o
	$(CC) main.o visualiser.o langton.o -o ant $(LDFLAGS)

# Defining the executable files needed to build ant.o
main.o: main.c langton.h visualiser.h
	$(CC) $(CFLAGS) main.c -o main.o

visualiser.o: visualiser.c langton.h visualiser.h
	$(CC) $(CFLAGS) visualiser.c $(LDFLAGS) -o visualiser.o

langton.o: langton.c langton.h
	$(CC) $(CFLAGS) langton.c $(LDFLAGS) -o langton.o

library: libant.so

libant.so: visualiser.o langton.o # Will create a shared library with functions from visualiser and langton
	$(CC) -shared visualiser.o langton.o -o libant.so $(LDFLAGS)

clean: # Will remove any executable files and library
	rm -f ant libant.so *.o

run:
	./ant $(VARIANT)