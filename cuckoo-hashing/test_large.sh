#!/bin/bash

g++ -O3 ideal.cc -o ideal
g++ -O3 solution.cc -o sol

for ((i=0; i<5; i++)); do
    input_file="test_$i.in"
    python gen_large.py > $input_file

    ideal_out="ideal_$i.out"
    ./ideal < $input_file > $ideal_out

    sol_out="sol_$i.out"
    ./sol < $input_file > $sol_out

    diff -w $ideal_out $sol_out

    if [ $? -ne 0 ]; then
        echo "Failed test $i."
        break
    fi
    echo "Test $i passed"
    rm $input_file $ideal_out $sol_out
done

rm ideal sol