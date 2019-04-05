#!/bin/sh

echo >sequence
./test_write <sequence >coded_sequence
./test_read <coded_sequence >decoded_sequence

cat decoded_sequence

if ! diff decoded_sequence sequence >/dev/null
then
    echo "Sequences differ when empty, bfile does not work"
    exit 1
fi

#-------------------------------------------------------------------------

echo 000000000000000000>sequence
./test_write <sequence >coded_sequence
./test_read <coded_sequence >decoded_sequence

cat decoded_sequence

if ! diff decoded_sequence sequence >/dev/null
then
    echo "Sequences differ when full of 0, bfile does not work"
    exit 1
fi

#-------------------------------------------------------------------------

echo 1111111111111111111111111>sequence
./test_write <sequence >coded_sequence
./test_read <coded_sequence >decoded_sequence

cat decoded_sequence

if ! diff decoded_sequence sequence >/dev/null
then
    echo "Sequences differ when full of 1, bfile does not work"
    exit 1
fi

#-------------------------------------------------------------------------
i=1
while [ $i -le 8 ]
do
	if [ $i -eq 1 ]
	then
		echo 1 >sequence
	elif [ $i -eq 2 ]
	then
		echo 01 >sequence
	elif [ $i -eq 3 ]
	then
		echo 110 >sequence
	elif [ $i -eq 4 ]
	then
		echo 0101 >sequence
	elif [ $i -eq 5 ]
	then
		echo 00101 >sequence
	elif [ $i -eq 6 ]
	then
		echo 011011 >sequence
	elif [ $i -eq 7 ]
	then
		echo 1101001 >sequence
	elif [ $i -eq 8 ]
	then
		echo 11010110 >sequence
	fi
    ./test_write <sequence >coded_sequence
    ./test_read <coded_sequence >decoded_sequence

	cat decoded_sequence

    if diff decoded_sequence sequence >/dev/null
    then
        i=`expr $i + 1`
    else
        echo "Sequences differ when if has $i bits, bfile does not work"
        exit 1
    fi
done
