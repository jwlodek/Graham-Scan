# Graham Scan

Graham Scan algorithm implemented for my AMS 345/CSE 355 course at Stony Brook University

I chose to write the implementations in C because of its execution speed,
my familiarity with the language, and because I enjoy coding in it. I also
wished to learn a C/C++ unit testing framework, as I have had only minimal exposure
to such libraries in the past. I settled on using the Criterion library found here:
https://github.com/Snaipe/Criterion. 

### Current implementation:

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

**Compiling/Running**

**NOTE:** I have only tested program compilation on a Debian 9 machine using gcc version 6.3.*

To compile the program, there are three options.  

First, you may compile with
```
make clean gs
```
This will compile the program with the basic configration. You then run it with the following:
```
./gs INPUT_FILE OUTPUT_FILE
```
where the two arguments are the path to the input file, and the path for the output file. For example,
```
./gs inputs/graham_input2.txt outputs/graham_output2.txt
```
would run the algorithm on input file graham_input2.txt and print the resulting convex hull to graham_output2.txt.

Second, you can compile for unit testing with:
```
make clean test
```
Note that to use this option you will need to have the criterion unit testing library installed and in your library path. Instructions for doing this are below.

Then, to run the program, simply type:
```
./gstest
```
and it will print information on the tests being run and whether or not they passed.

Finally, you may also compile with debug markers for use with gdb with:
```
make clean debug
```
and run it with:
```
./gsdebug INPUT_FILE OUTPUT_FILE
```
### Current Results

I was able to run my algorithm on a number of inputs and it was successfully able to compute the convex hull. One thing to note is that while it does print the points in counterclockwise order for the hull, it always starts with the lowest point as was found during the course of the algorithm execution.

Here is the most recent output of executing the unit tests for my program:
```
jwlodek@debianVM:~/Documents/ProgrammingWorkspace/CompGeoAlgorithms$ ./gstest 
---------------------------------------
Testing calulating angles for each point...
Angles computed successfully.
---------------------------------------
Testing convex hull graham scan on input set...
Finding the lowest point by y-coordinate...
Lowest point found.
Computing angles with lowest point...
Angles computed. Sorting using merge-sort
Finished sorting points by angle
Initialized the stack.
Finished computing Convex Hull using Graham Scan.
Convex Hull (in counter-clockwise order):
12
[-25,-200] -> -1.000000
[25,-200] -> 0.000000
[200,-125] -> 0.321751
[200,125] -> 0.965252
[25,200] -> 1.446441
[-25,200] -> 1.570796
[-150,125] -> 1.937970
[-175,100] -> 2.034444
[-200,50] -> 2.181522
[-200,-50] -> 2.432966
[-175,-100] -> 2.553590
[-150,-125] -> 2.601173
Convex hull computed successfully.
---------------------------------------
Testing sorting points by angle...
Points sorted correctly.
---------------------------------------
Testing calulating lowest point by y-coord...
Lowest point found.
---------------------------------------
Testing calulating lowest point by y-coord...
Lowest point found.
---------------------------------------
Testing input file parsing...
Input file parsing passed.
---------------------------------------
Testing calulating turn type...
Turn type calculation passed.
---------------------------------------
Testing calulating turn type...
Turn type calculation passed.
---------------------------------------
Testing calulating turn type...
Turn type calculation passed.
[====] Synthesis: Tested: 9 | Passing: 9 | Failing: 0 | Crashing: 0 
```
**Note** The numbers printed beside the points are the angles they made with the original, hence why the lowest point is given the arbitrary '-1' value.

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

Note that there are several dependencies that must be installed first. Running the above will print errors prompting you to install these dependencies prior to compiling the library.
