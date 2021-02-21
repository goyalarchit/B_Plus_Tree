#!/bin/bash
echo Running Test Cases;
test_dir="./test_data/"
input_files=("input1.txt" "input2.txt" "input3.txt" "input.txt")
output_files=("out1.txt" "out2.txt" "out3.txt" "out.txt")
for i in "${!input_files[@]}";
do
    echo Test Case $i
    file=$test_dir${input_files[i]}
    echo running test file $file
    ./a.out $file > out.txt
    echo comparing results out.txt with $test_dir${output_files[i]}
    diff out.txt $test_dir${output_files[i]}
    echo
    
done
rm out.txt