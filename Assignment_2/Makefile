CC=gcc
OBJ1=find.o


all: find clean

%.o:%.c
	$(CC) -c -o $@ $^

find:$(OBJ1)
	$(CC) -o $@ $^

clean:
	rm -f *.o
