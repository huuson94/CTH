#!/bin/bash
echo "---- EX1"
./kplc ../test/example1.kpl > myre.txt ; diff ./myre.txt ../test/result1.txt 
echo "---- EX2"
./kplc ../test/example2.kpl > myre.txt ; diff ./myre.txt ../test/result2.txt 
echo "---- EX3"
./kplc ../test/example3.kpl > myre.txt ; diff ./myre.txt ../test/result3.txt 
echo "---- EX4"
./kplc ../test/example4.kpl > myre.txt ; diff ./myre.txt ../test/result4.txt 
echo "---- EX5"
./kplc ../test/example5.kpl > myre.txt ; diff ./myre.txt ../test/result5.txt 
echo "---- EX6"
./kplc ../test/example6.kpl > myre.txt ; diff ./myre.txt ../test/result6.txt 

