CC = gcc
CFLAGS= -Wpedantic -Wall -Wextra -g -std=c11
TESTFLAG = -DUNITY_OUTPUT_COLOR
ARGS= ../data/dictionary.txt  ../data/correctme.txt 8

quick: clean all

all: libs test

run_all: run_test run

libs:
	mkdir build/
	$(CC) $(CFLAGS) skip_list.c main.c -o build/main_ex2

run:
	./build/main_ex2 $(ARGS) 
# $(ARGS)

debug:
	gdb --args ./build/main_ex2 $(ARGS)  
 
debug_test:
	gdb ./build/skip_list_test

mem_check:
	valgrind --log-file="valgrind.log" -s ./build/skip_list_test
	

test:
	$(CC) $(CFLAGS) $(TESTFLAG) unity/unity.c skip_list.c skip_list_test.c -o build/skip_list_test 

run_test:
	./build/skip_list_test
clean:
	rm -r build
#	rm valgrind.log
#	rm valgrind.log.core.*


