CC=gcc
CFLAGS= -Wall -g 
ARGS= input/dictionary.txt  input/correctme.txt

all: libs test

libs:
	mkdir ex2/build/
	$(CC) $(CFLAGS)  ex2/skip_list.c ex2/main.c -o ex2/build/main_ex2
run:
	./ex2/build/main_ex2 $(ARGS)
# TODO remember to put back arguments

debug:
	gdb ./ex2/build/main_ex2 $(ARGS)

test:
	$(CC) $(CFLAGS) ex2/skip_list.c skip_list_test.c -o test 

clean:
	rm -rf ex2/build
