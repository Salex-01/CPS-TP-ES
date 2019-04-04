all : test_read test_write

%.o : %.c
	gcc -Wall -c $<

test_read : test_read.o bit_operations.o
	gcc -Wall -o $^

test_write : test_write.o bit_operations.o
	gcc -Wall -o $^

clean : rm -f *.o *~ test_read test_write
