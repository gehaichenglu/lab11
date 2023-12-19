#!/bin/sh
rm -r ./bin
make clean
make

mkdir bin
mv *.coe ./bin
mv *.o ./bin
mv *.hex ./bin
mv *.mif ./bin
mv *.tmp ./bin
mv *.dump ./bin
