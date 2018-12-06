# Computational Geometry Algorithms

Algorithms implemented for my AMS 345 course at Stony Brook University

I chose to write the implementations in C because of its execution speed,
my familiarity with the language, and because I enjoy coding in it. I also
wished to learn a C/C++ unit testing framework, as I have had only minimal exposure
to such libraries in the past. I settled on using the Criterion library found here:
https://github.com/Snaipe/Criterion. 

### Current implementations:

**Graham Scan**

My graham scan implementation runs through the following steps:

1) Parse the input from an input file. This is done using regex splitting.
2) Find the lowest point by y-coordinate. This is done in O(n) time by iterating over the array of points.
3) Compute the angles between the lowest point and every other point. I assigned -1 to the lowest point, 
and for all other points, I computed using arccos, because arccos gives a value between 0 and pi, and
all of the angles will be in this range.
4) Sort the points by the angle with the lowest point. Because the lowest point angle is -1 it will always be first. This
is done using mergesort in O(nlogn) time.
5) Use a stack to run the Graham Scan algorithm on the set of sorted points.
6) Save the remaining stack to an output file.



### Unit testing

Unit tests for these algorithms are written with the help of the Criterion C/C++ unit testing library.

In order to install criterion for running tests, run the following:
```
git clone --recursive https://github.com/Snaipe/Criterion
cd Criterion
mkdir build
cd build
cmake ..
cmake --build .
sudo make install
```

Note that there are several dependencies that must be installed first.
