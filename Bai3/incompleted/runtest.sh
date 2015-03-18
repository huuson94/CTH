#!/bin/bash

echo "---- EX2"
./parser ../test/example2.kpl > myre.txt ; diff ./myre.txt ../test/result2.txt
echo "---- EX3"
./parser ../test/example3.kpl > myre.txt ; diff ./myre.txt ../test/result3.txt  
echo "---- EX4"
./parser ../test/example4.kpl > myre.txt ; diff ./myre.txt ../test/result4.txt 
echo "---- EX5"
./parser ../test/example5.kpl > myre.txt ; diff ./myre.txt ../test/result5.txt 
echo "---- EX6"
./parser ../test/example6.kpl > myre.txt ; diff ./myre.txt ../test/result6.txt 
echo "---- EX7"
./parser ../test/example7.kpl > myre.txt ; diff ./myre.txt ../test/result7.txt 

