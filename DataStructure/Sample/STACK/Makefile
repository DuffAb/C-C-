CC = gcc
CFLAGS = -g -DRPC_SVC_FG
RPCGEN_FLAG = -C

all: sa_test sl_test maze

# the executables: sa_test

sa_test: sa_test.o sa.o
	$(CC) -o sa_test sa_test.o sa.o

sl_test: sl_test.o sl.o
		$(CC) -o sl_test sl_test.o sl.o

maze: maze.o sl.o
			$(CC) -o maze maze.o sl.o

# object files for the executables
sa_test.o: sa_test.c sa.h
	$(CC) $(CFLAGS) -c sa_test.c

sl_test.o: sl_test.c sl.h
	$(CC) $(CFLAGS) -c sl_test.c

maze.o: maze.c sl.h
	$(CC) $(CFLAGS) -c maze.c

sa.o: sa.c sa.h
	$(CC) $(CFLAGS) -c sa.c

sl.o: sl.c sl.h
		$(CC) $(CFLAGS) -c sl.c
clean:
	rm -f sa_test *.o
