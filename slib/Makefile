CC = gcc

demo: demo.o read.o write.o open.o
	$(CC) -o demo demo.o read.o write.o open.o

demo.o: demo.c
	$(CC) -c -o demo.o demo.c

read.o: read.c
	$(CC) -c -o read.o read.c

write.o: write.c
	$(CC) -c -o write.o write.c

open.o: open.c
	$(CC) -c -o open.o open.c

clean:
	rm -rf demo demo.o write.o read.o open.o
