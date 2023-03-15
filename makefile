CC = gcc
CFLAGS = -Wall -g

main:
	$(CC) $(CFLAGS) ex1/main.c -o ex1/build/main_ex1

run:
	./ex1/build/main_ex1 data/records.csv data/sorted.csv