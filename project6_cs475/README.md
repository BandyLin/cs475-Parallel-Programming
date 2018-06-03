Run on Rabbit
g++ -o first first.cpp libOpenCL.so -lm -fopenmp
first

On Flip compile with
g++ -o first first.cpp libOpenCL.so -lm -fopenmp

To run multiply 
Open first.cl set i = 1

To run mutliply & sum
Open first.cl set i = 2

To run reduction
Open first.cl set i = 3
