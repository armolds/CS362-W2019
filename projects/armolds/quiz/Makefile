CFLAGS= -Wall -fpic -coverage -lm -std=c99

testme: testme.c
	gcc -o testme testme.c -g $(CFLAGS)

all: testme

clean:
	rm -f *.o *.gcno *.gcda testme
