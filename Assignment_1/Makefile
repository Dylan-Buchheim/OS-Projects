CC=gcc
OBJ1=child_processes.o
OBJ2=child_processes_chain.o

all: child_processes child_processes_chain clean

%.o:%.c
	$(CC) -c -o $@ $^

child_processes:$(OBJ1)
	$(CC) -o $@ $^

child_processes_chain:$(OBJ2)
	$(CC) -o $@ $^

clean:
	rm -f *.o
