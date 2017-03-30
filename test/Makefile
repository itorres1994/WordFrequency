CC = gcc
CFLAGS = -I/usr/include --std=c99 -Wall -g $(XCFLAGS)
LDFLAGS = -L/usr/lib/i386-linux-gnu -lrt -lm -lpthread $(XLDFLAGS)
LDTESTFLAGS = -lcheck $(LDFLAGS)
OBJS = ../wset.o ../words.o

all: public-test

public-test: public-test.o $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) public-test.o -o public-test $(LDTESTFLAGS)

public-test.o: public-test.c 
	$(CC) $(CFLAGS) -c public-test.c

clean:
	rm -f *.o
	rm -f public-test
