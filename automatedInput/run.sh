#!/bin/bash 

g++ test.cpp -o test
for filename in $PWD/Data/*.txt; do
	cat "$filename" | ./test
done

