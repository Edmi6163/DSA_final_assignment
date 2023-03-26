CC=gcc
CFLAGS= -Wall -g 
ARGS= input/dictionary.txt  input/correctme.txt

all: libs obj test

libs:
	mkdir ex2/build/
	$(CC) $(CFLAGS)  ex2/src/skip_list.c ex2/src/main.c -o ex2/build/ex2
run:
	./ex2/build/main_ex2 $(ARGS)

clean:
	rm -rf ex2/build
