CC = gcc
CFLAGS = -g -Wall
ARGS = input/dictionary.txt input/correcteme.txt


all: libs obj test

libs:	
	mkdir ex2/build/
	$(CC) $(CFLAGS) ex2/skip_list.c -o ex2/build/ex2

run: 
	./ex1/buidl/ex2 %(ARGS)

clean:
	rm -rf ex2/build
	rm ex2/*o
