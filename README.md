# SSA-OIST

A simple implementation of the Gillespie SSA algorithm in C++ (and additional concept tests in Python3).

The project was mainly guided by the paper "Exact Stochastic Simulation of Coupled Chemical Reactions" (Gillespie, 1977), and in a minor way by the project "Stochastic Kinectics" (https://ndcbe.github.io/data-and-computing/notebooks/contrib/Stochastic-Kinetics.html) from the coursework of a Chemical and Biomolecular Engineering course from the University of Notre Dame.

The following diagram explains the basic elements and their relations:
![Diagram of elements in simulation](./figs/diag.png)

## Features
* **Domain Specific Language DSL**: Define reactions using natural chemical syntax (e.g., `2*A + B >> C`).

* **Visualization**: Integrated plotting support via `matplotlib-cpp` to generate trajectory graphs directly from C++.

* **Automated Documentation**: Source code compatible with Doxygen for generating API documentation.

## Project Structure
* `cpp/include/`: Header files (`.hpp`) and template implementations (`.tpp`).
* `cpp/src/`: Implementation of Species, Composition, and the Gillespie Solver logic.
* `cpp/apps/`: Main simulation entry point.
* `cpp/build/`: CMake build artifacts and binaries.
* `python/`: Python implementation with proof of concept.

## Prerequisites
* **CMake** (v3.14 or higher).
* **Python 3** (with `matplotlib` and `numpy` development headers) for plotting.
* **Doxygen** (optional, for generating documentation).

## Building the Project
Navigate to the project root and run:
```bash
mkdir build && cd build
cmake ..
make
```

## Generating Documentation
Navigate to the project root and run:
```bash
doxygen -g Doxyfile
doxygen Doxyfile
```

Then open the index.html file from $PROJECT_ROOT/html/ folder using the browser.

## To Do

1. Implement higher level abstractions (e.g., a volume to contain the reaction channels).
2. Create a separate utility class (to contain, for example, the heuristical combinatory function that is currently inside the ReactionChannel class)
3. Implement a timer input in the solver to limit simulation time.
4. Implement an analogous to the Java's BigInteger for the combinatorial factor h => currently it is done using an heuristic that avoids big multiplications, but it might crash for larger quantities (e.g., a pretty reasonable amount 1e7 molecules and stoichiometry of 2 generates 1e7 C 2 combinations).
5. Implement input files to make simulations more dynamic.
6. Add a diagram of classes to explain better the relations of the components in the simulation.