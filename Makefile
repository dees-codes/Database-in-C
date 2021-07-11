#makefile for this program


# .o files, their dependencies and rules

main.o: main.c mod1.h 
	gcc -c -Wall --pedantic main.c

mod1.o: mod1.c mod1.h 
	gcc -c -Wall --pedantic mod1.c


# dependencies for the executable and rules for compiling it
db: main.o mod1.o
	gcc -o db main.o mod1.o

#rule for clean
clean:
	rm -f db main.o mod1.o

#dependency for db
all: db

#dependencies for tarball and rull to archive all files into tarball
tarball: main.c mod1.c mod1.h Makefile
	tar -cvf db.tar db main.c mod1.c mod1.h textfile.txt Makefile
