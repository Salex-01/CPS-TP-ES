all : test_read test_write

test_read : test_read.o bit_operations.o
	gcc -Wall test_read.o bit_operations.o -o test_read

test_write : test_write.o bit_operations.o
	gcc -Wall test_write.o bit_operations.o -o test_write

bit_operations.o: bit_operations.c bit_operations.h
	gcc -c bit_operations.c -o bit_operations.o

test_write.o: test_write.c
	gcc -c test_write.c -o test_write.o

test_read.o: test_read.c
	gcc -c test_read.c -o test_read.o

clean :
	rm -f *.o *~ test_read test_write
