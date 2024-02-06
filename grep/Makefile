CC=gcc

CFLAGS=-Wall -Werror -Wextra

all: s21_grep

s21_grep: s21_grep.o
	$(CC) $(CFLAGS) s21_grep.o -o s21_grep
	rm -f s21_grep.o

s21_grep.o: s21_grep.c
	$(CC) -c $(CFLAGS) s21_grep.c


test_start:all test test_sh clean

test: test.o 
	$(CC) $(CFLAGS) test.o -o test

test.o: test.c
	$(CC) -c $(CFLAGS) test.c	

test_sh:
	sh test.sh
	
clean:
	
	rm -rf *.o test
	rm -rf s21_grep test

rebuild: clean all

