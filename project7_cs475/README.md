How to Run and Compile OpenCL

First compile on Flip with
g++ -o first first.cpp libOpenCL.so -lm -fopenmp

Second Run on Rabbit
ssh rabbit.engr
g++ -o first first.cpp libOpenCL.so -lm -fopenmp
first

To run multiply 
Open first.cl set i = 1

To run mutliply & sum
Open first.cl set i = 2

To run reduction
Open first.cl set i = 3


How to Compile and Run SIMD

Compile with 'make'
run 'arraymult'

How to Compile and Run OpenMP
Compile with 'make'
run 'project_7'

Change NumT to 4 then run again
Or change NumT back to 1 then run
