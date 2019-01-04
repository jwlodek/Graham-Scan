# Graham Scan

Author: Jakub Wlodek

Graham Scan algorithm implementation for my AMS 345/CSE 355 course at Stony Brook University

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
5) Use a stack to run the Graham Scan algorithm on the set of sorted points in O(n) time.
6) Run a function to remove degeneracies (3-points colinear) from the output set
7) Save the remaining stack to an output file.

**Compiling/Running**

**NOTE:** I have only tested program compilation on a Debian 9 Linux machine using gcc version 6.3.*

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

Here is the most recent output of executing the unit tests for my program.
There are 14 unit tests total, about half test the helper functions, and the rest run the algorithm on certain input sets and test whether or not they match the expected result. All inputs and output files used for testing are available in their respective directories.
```
jwlodek@debianVM:~/Documents/ProgrammingWorkspace/CompGeoAlgorithms$ ./gstest ---------------------------------------
Testing calulating angles for each point...
Angles computed successfully.
---------------------------------------
Testing convex hull on set with 3 colinear...
Computing Convex hull using Graham scan...
Finding the lowest point by y-coordinate...
Lowest point found.
Computing angles with lowest point...
Angles computed. Sorting using merge-sort
Finished sorting points by angle
Initialized the stack.
Finished computing Convex Hull using Graham Scan.
Handling degeneracies...
Convex hull computed successfully.
---------------------------------------
Testing convex hull on set with colinear that include start point...
Computing Convex hull using Graham scan...
Finding the lowest point by y-coordinate...
Lowest point found.
Computing angles with lowest point...
Angles computed. Sorting using merge-sort
Finished sorting points by angle
Initialized the stack.
Finished computing Convex Hull using Graham Scan.
Handling degeneracies...
Convex hull computed successfully.
---------------------------------------
Testing convex hull on large point set w/ degeneracy...
Computing Convex hull using Graham scan...
Finding the lowest point by y-coordinate...
Lowest point found.
Computing angles with lowest point...
Angles computed. Sorting using merge-sort
Finished sorting points by angle
Initialized the stack.
Finished computing Convex Hull using Graham Scan.
Handling degeneracies...
Convex hull computed successfully.
---------------------------------------
Testing convex hull graham scan on blackboard input set...
Computing Convex hull using Graham scan...
Finding the lowest point by y-coordinate...
Lowest point found.
Computing angles with lowest point...
Angles computed. Sorting using merge-sort
Finished sorting points by angle
Initialized the stack.
Finished computing Convex Hull using Graham Scan.
Convex hull computed successfully.
---------------------------------------
Testing large point set wo/ degeneracy...
Computing Convex hull using Graham scan...
Finding the lowest point by y-coordinate...
Lowest point found.
Computing angles with lowest point...
Angles computed. Sorting using merge-sort
Finished sorting points by angle
Initialized the stack.
Finished computing Convex Hull using Graham Scan.
Handling degeneracies...
Convex hull computed successfully.
---------------------------------------
Testing convex hull with on blackboard set w/ degeneracy handling...
Computing Convex hull using Graham scan...
Finding the lowest point by y-coordinate...
Lowest point found.
Computing angles with lowest point...
Angles computed. Sorting using merge-sort
Finished sorting points by angle
Initialized the stack.
Finished computing Convex Hull using Graham Scan.
Handling degeneracies...
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
Left turn type calculation passed.
---------------------------------------
Testing calulating turn type...
Right turn type calculation passed.
---------------------------------------
Testing calulating turn type...
Inline turn type calculation passed.
[====] Synthesis: Tested: 14 | Passing: 14 | Failing: 0 | Crashing: 0 
```

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
