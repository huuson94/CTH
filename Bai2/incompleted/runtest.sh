#!/bin/bash
echo "---- EX1"
./scanner ../test/example1.kpl > myre.txt ; diff ./myre.txt ../test/result1.txt 
echo "---- EX2"
./scanner ../test/example2.kpl > myre.txt ; diff ./myre.txt ../test/result2.txt 
echo "---- EX3"
./scanner ../test/example3.kpl > myre.txt ; diff ./myre.txt ../test/result3.txt 
echo "---- EX4"
./scanner ../test/example4.kpl > myre.txt ; diff ./myre.txt ../test/result4.txt 
echo "---- EX5"
./scanner ../test/example5.kpl > myre.txt ; diff ./myre.txt ../test/result5.txt 
echo "---- EX6"
./scanner ../test/example6.kpl > myre.txt ; diff ./myre.txt ../test/result6.txt 
echo "---- EX7"
./scanner ../test/example7.kpl > myre.txt ; diff ./myre.txt ../test/result7.txt 
