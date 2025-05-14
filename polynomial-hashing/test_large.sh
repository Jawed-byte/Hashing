#!/bin/bash

g++ -O3 gen_large.cc -o gen_large
g++ -O3 ideal.cc -o ideal
g++ -O3 solution.cc -o solution

for ((i=0; i<5; i++)); do
    input_file="large_test_$i.in"
    ./gen_large > $input_file

    ideal_out="large_ideal_$i.out"
    ./ideal < $input_file > $ideal_out

    solution_out="large_solution_$i.out"
    ./solution < $input_file > $solution_out

    diff -w $ideal_out $solution_out
    if [ $? -ne 0 ]; then
        echo "Found difference at test $input_file".
        break
    fi
    echo "Passed test $i"
    rm $input_file $ideal_out $solution_out
done

rm gen_large ideal solution