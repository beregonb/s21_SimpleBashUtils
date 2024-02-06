CC=gcc

CFLAGS=-Wall -Werror -Wextra

all: s21_cat

s21_cat: s21_cat.o
	$(CC) $(CFLAGS) s21_cat.o -o s21_cat
	rm -f s21_cat.o

s21_cat.o: s21_cat.c
	$(CC) -c $(CFLAGS) s21_cat.c

test_start: all test test_sh clean

test: test.o 
	$(CC) $(CFLAGS) test.o -o test

test.o: test.c
	$(CC) -c $(CFLAGS) test.c	

test_sh:
	sh test.sh
	
clean:
	rm -rf *.o test
	rm -rf s21_cat test

rebuild: clean all