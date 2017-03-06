# Nonlinear second order differential equation solver for Brownian motor systems

This instructuon file  explains about how the names of directories and and code files made. And brief instruction how to run the codes are explaiend.

Hoseong Asher Lee. 
May 8th 2015.


###Nomenclature for folders

average: a folder that includes codes for averaged trajectories and variance.
dist: a folder that includes codes for probability distribution functions.
poincare: a foler that includes codes for Poincare section graphs.
single: a folder that includes codes for single trajectories.

###Nomenclature for files
fl: "fl" refers to a system used is a simulation or a paper in which the system is proposed. It's named after a main author's name, S. Flach.
1, 2, and 3: 1, 2, and 3 refers to the certain case that determines parameters of the system.
avg: It refers to a file associated with averaged trajectories.
pc: It refers to a file associated with Poincare sections.
d: It refers to a file associated with probability distribution function graphs.
s: It refers to a file associated with single trajectories.

###Example
sfl1.c: a code file associated with single trajectoty of a case (a).
flpc3.c: a code file associated with Poincare section of a case (c).

###Usage of file
** My computer system was Ubuntu 14.04, one of Linux-based OS. For other OS, the compiling codes might be different.

1. Compilation
  ```
  gcc filename.c -c -Wall -O3
  ```
  Then, you will have filename.o file in a directory.

2. Making executable files.
  ```
  gcc filename.o -lgsl -lgslcblas -lm -O3
  ```
  Then, you will have a.out file in a directory.

3. Running program.
  ```
  ./a.out
  ```
  or
  ```
  ./a.out > filename.dat
  ```
  ./a.out will print all the data values on the dos window. If you want to put the data values in a text file, try the second one.

4. Drawing graphs.

In drawing graphs, GNUPLOT was used. For more detail about the usage of the program, see http://www.gnuplot.info/.

** For probability distribution function codes, single trajectories data files has to be prepared before running the codes. 

Thank you!
