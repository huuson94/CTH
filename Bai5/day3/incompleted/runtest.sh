#!/bin/bash
echo "---- EX1"
./kplc ../tests/example1.kpl > myre ; diff ./myre ../tests/example1
echo "---- EX2"
./kplc ../tests/example2.kpl > myre ; diff ./myre ../tests/example2
echo "---- EX2"
./kplc ../tests/example3.kpl > myre ; diff ./myre ../tests/example3
echo "---- EX2"
./kplc ../tests/example4.kpl > myre ; diff ./myre ../tests/example4
echo "---- EX2"
./kplc ../tests/example5.kpl > myre ; diff ./myre ../tests/example5
echo "---- EX2"
./kplc ../tests/example6.kpl > myre ; diff ./myre ../tests/example6
echo "---- EX2"
./kplc ../tests/example7.kpl > myre ; diff ./myre ../tests/example7
echo "---- EX2"
./kplc ../tests/example8.kpl > myre ; diff ./myre ../tests/example8
echo "---- EX2"
./kplc ../tests/example9.kpl > myre ; diff ./myre ../tests/example9

