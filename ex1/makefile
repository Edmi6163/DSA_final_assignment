CC = gcc
CFLAGS = -Wpedantic -Wall -Wextra -g
TESTFLAGS = -DUNITY_INCLUDE_DOUBLE -DUNITY_OUTPUT_COLOR
ARGS = ../data/records.csv ../data/sorted.csv 6 2

all: lib test 

all_dbg: lib dump

run_all: run_test run

lib:
	$(CC) $(CFLAGS)  merge_binary_insertion_sort.c main.c comparable.c csvReader.c -o build/main_ex1

run:
	./build/main_ex1 $(ARGS)

mem_check:
	valgrind --log-file="valgrind.log" -s ./build/merge_binary_insertion_sort_test

debug:
	gdb --args ./build/main_ex1 $(ARGS)

debug_test:
	gdb  ./build/test 

dump:
	./build/main_ex1 $(ARGS) >> log.log

test:
	$(CC) $(CFLAGS) $(TESTFLAGS)  merge_binary_insertion_sort.c test/merge_binary_insertion_sort_test.c test/generic_comparable.c test/unity.c -o build/merge_binary_insertion_sort_test

run_test:
	./build/merge_binary_insertion_sort_test

clean:
	rm -r build/*
	rm ../data/sorted.csv
	rm valgrind.log
	rm log.log
