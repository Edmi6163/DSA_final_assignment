CC = gcc
CFLAGS = -Wpedantic -Wall -Wextra -g
TESTFLAGS = -DUNITY_INCLUDE_DOUBLE -DUNITY_OUTPUT_COLOR
ARGS = data/records.csv data/sorted.csv 15 1

all: lib test 

all_dbg: lib dump

run_all: test run

lib:
	$(CC) $(CFLAGS) main.c merge_binary_insertion_sort.c comparable.c csvReader.c -o build/main_ex1

run:
	./build/main_ex1 $(ARGS)

mem_check:
	valgrind --log-file="valgrind.log" -s ./build/test

debug:
	gdb --args ./build/main_ex1 $(ARGS)

debug_test:
	gdb  ./build/test 


dump:
	./build/main_ex1 $(ARGS) >> log.log

test:
	$(CC) $(CFLAGS) $(TESTFLAGS) merge_binary_insertion_sort.c test/generic_comparable.c test/unity.c test/merge_binary_insertion_sort_test.c -o build/test

run_test:
	./build/test

clean:
	rm data/sorted.csv
	rm valgrind.log
	rm log.log
	rm -r build/*
