#!/bin/sh


# build program
cd build
mkdir output
cd output
cmake ../../ && cmake --build .
cp ./class_generator ../
cd ..

# create app.dir



