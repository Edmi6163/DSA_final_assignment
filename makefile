CC=gcc
CFLAGS= -Wall -g 
ARGS= input/dictionary.txt  input/correctme.txt

quick: clean all

all: libs test

libs:
	mkdir ex2/build/
	$(CC) $(CFLAGS)  ex2/skip_list.c ex2/main.c -o ex2/build/main_ex2
run:
	./ex2/build/main_ex2 
# $(ARGS)

debug:
	gdb ./ex2/build/main_ex2 
# $(ARGS)

test:
	$(CC) $(CFLAGS) ex2/unity/unity.c ex2/skip_list.c ex2/skip_list_test.c -o ex2/build/skip_list_test 

run_test:
	./ex2/build/skip_list_test
clean:
	rm -rf ex2/build

