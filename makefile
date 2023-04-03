CC = gcc
CFLAGS = -Wall -g
ARGS = data/records.csv data/sorted.csv

all: lib run 
all_dbg: lib dump
lib:
	$(CC) $(CFLAGS) ex1/main.c ex1/csvReader.c -o build/main_ex1

run:
	./build/main_ex1 $(ARGS)

dump:
	./build/main_ex1 $(ARGS) >> log.log
clean:
	rm log.log
	rm -r build/*
