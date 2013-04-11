# hawick_circuits
This repository contains the implementation of an algorithm for finding all
the elementary circuits in a directed (multi)graph. The graph can contain
self-loops.

The algorithm is the one described in [Enumerating Circuits and Loops in
Graphs with Self-Arcs and Multiple-Arcs][paper] by K. A. Hawick and
H. A. James.

## How to build
You don't have to. The algorithm is in a single header.


## Dependencies
Boost 1.53.00 and later.


## Tests
It is tested using the test suite [here][test_suite].


[paper]: http://www.massey.ac.nz/~kahawick/cstn/013/cstn-013.pdf
[test_suite]: https://github.com/josch/cycle_test
