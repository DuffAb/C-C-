CC = gcc
CFLAGS = -g -DRPC_SVC_FG
RPCGEN_FLAG = -C

all: sa_test

# the executables: sa_test

sa_test: sa_test.o sa.o
	$(CC) -o sa_test sa_test.o sa.o

# object files for the executables

sa_test.o: sa_test.c sa.h
	$(CC) $(CFLAGS) -c sa_test.c

sa.o: sa.c sa.h
	$(CC) $(CFLAGS) -c sa.c

clean:
	rm -f sa_test *.o
