#!/bin/bash

g++ -O3 gen.cc -o gen
g++ -O3 ideal.cc -o ideal
g++ -O3 solution.cc -o solution

for ((i=0; i<5; i++)); do
    input_file="test_$i.in"
    ./gen > $input_file

    ideal_out="ideal_$i.out"
    ./ideal < $input_file > $ideal_out

    solution_out="solution_$i.out"
    ./solution < $input_file > $solution_out

    diff -w $ideal_out $solution_out
    if [ $? -ne 0 ]; then
        echo "Found difference at test $input_file".
        break
    fi
    echo "Passed test $i"
    rm $input_file $ideal_out $solution_out
done

rm gen ideal solution