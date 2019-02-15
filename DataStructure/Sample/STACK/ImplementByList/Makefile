CC = gcc
CFLAGS = -g -DRPC_SVC_FG
RPCGEN_FLAG = -C

all: sl_test maze

# the executables: sa_test

sl_test: sl_test.o sl.o
	$(CC) -o sl_test sl_test.o sl.o

maze: maze.o sl.o
		$(CC) -o maze maze.o sl.o

# object files for the executables

sl_test.o: sl_test.c sl.h
	$(CC) $(CFLAGS) -c sl_test.c

maze.o: maze.c sl.h
		$(CC) $(CFLAGS) -c maze.c

sl.o: sl.c sl.h
	$(CC) $(CFLAGS) -c sl.c

clean:
	rm -f sl_test maze *.o
