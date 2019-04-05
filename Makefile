all: test_read test_write generate_sequence bitabit

test_read: test_read.o bit_operations.o
	gcc -Wall $^ -o $@

test_write: test_write.o bit_operations.o
	gcc -Wall $^ -o $@

generate_sequence: generate_sequence.o bit_operations.o
	gcc -Wall $^ -o $@

bitabit: bitabit.o bit_operations.o
	gcc -Wall $^ -o $@

bitabit.o: bitabit.c bit_operations.h
	gcc -c $< -o $@

generate_sequence.o: generate_sequence.c
	gcc -c $< -o $@

test_write.o: test_write.c bit_operations.h
	gcc -c $< -o $@

test_read.o: test_read.c bit_operations.h
	gcc -c $< -o $@

clean:
	rm -f *.o *~ test_read test_write bitabit *sequence
