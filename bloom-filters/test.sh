#!/bin/bash

g++ -O3 ideal.cc -o ideal
g++ -O3 solution.cc -o sol

test_count=100

for ((i=0; i<$test_count; i++)); do
    input_file="test_$i.in"
    python gen.py > $input_file

    ideal_out="test_$i.ideal.out"
    ./ideal < $input_file > $ideal_out

    sol_out="test_$i.sol.out"
    ./sol < $input_file > $sol_out

    diff -w $ideal_out $sol_out

    if [ $? -ne 0 ]; then
        echo "Failed test $i"
        break
    fi

    echo "Passed test $i"
    rm $input_file $ideal_out $sol_out
done
rm ideal sol