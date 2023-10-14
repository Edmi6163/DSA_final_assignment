CC = gcc
CFLAGS = -Wpedantic -Wall -g -O1
ARGS = data/records.csv data/sorted.csv 1 2

all: lib test 

all_dbg: lib dump

run_all: test run

lib:
	$(CC) $(CFLAGS) ex1/main.c ex1/merge_binary_insertion_sort.c ex1/comparable.c ex1/csvReader.c -o build/main_ex1

run:
	./build/main_ex1 $(ARGS)

mem_check:
	valgrind --log-file="valgrind.log" -s ./build/test

gdb:
	gdb ./build/main_ex1

dump:
	./build/main_ex1 $(ARGS) >> log.log

test:
	$(CC) $(CFLAGS) ex1/merge_binary_insertion_sort.c ex1/comparable.c ex1/test/unity.c ex1/test/merge_binary_insertion_sort_test.c -o build/test

run_test:
	./build/test

clean:
	rm valgrind.log
	rm log.log
	rm -r build/*
