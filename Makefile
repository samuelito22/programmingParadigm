CC = gcc # Compiler
CFLAGS = -Wall -Wextra -fPIC -c -std=c11 # C compiler flags
LDFLAGS = -lncursesw # Linker flags
RPATH = -Wl,-rpath,'$$ORIGIN' # Telling the linker where to look for the libraries

all: ant run # run will automatically run ant with a VARIANT passed in

ant: clean library
	$(CC) -L. -lant -o ant $(LDFLAGS) $(RPATH)

# Defining the executable files needed to build ant.o
library: libant.so

libant.so: visualiser.o langton.o main.o# Will create a shared library with functions from visualiser and langton
	$(CC) -shared visualiser.o langton.o main.o -o libant.so $(LDFLAGS)

main.o: main.c langton.h visualiser.h
	$(CC) $(CFLAGS) main.c $(LDFLAGS) -o main.o

visualiser.o: visualiser.c langton.h visualiser.h
	$(CC) $(CFLAGS) visualiser.c $(LDFLAGS) -o visualiser.o

langton.o: langton.c langton.h
	$(CC) $(CFLAGS) langton.c $(LDFLAGS) -o langton.o

clean: # Will remove any executable files and library
	rm -f ant libant.so *.o

run:
	./ant $(VARIANT)