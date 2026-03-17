# Sudoku Solver

A C++ Sudoku solver that checks row, column, and box validity, tracks candidate values for open cells, and solves easy 9x9 boards through repeated elimination. Includes runtime measurement and board-state printing during solve steps.

Made with C++, STL, chrono

By Astrid Greene astridig@umich.edu

---

## Overview

This project is a C++ Sudoku solver for standard 9x9 boards. The puzzle is stored as an 81-cell grid, and missing values are filled by narrowing down valid candidates based on row, column, and 3x3 box constraints.

It focuses on elimination and constraint checking rather than full search, so it works well on easy puzzles such as New York Times Easy boards.

---

## Features

- 9x9 Sudoku board stored as an 81-cell vector  
- Row, column, and 3x3 box validation  
- Candidate tracking for open cells  
- Iterative solving through elimination  
- Helper functions for indexing and board navigation  
- Board printing during solve steps  
- Runtime measurement using chrono  

---

## How It Works

Each cell is mapped to its row, column, and box. For every empty position, the solver checks which values from 1 to 9 are still valid.

Those values are stored as candidates. If a cell has only one valid option, it gets filled. The solver also looks for values that are unique within a row or column and fills those when possible.

This process repeats until the board is complete or no further progress can be made.

---

## Tech Stack

- C++  
- STL (vector, unordered_set, unordered_map)  
- chrono  
- iostream  

---

## File Structure

- sudoku_solver.cpp — main solver and test puzzle  

---

## How to Run

1. Make sure you have a C++ compiler installed  
2. Compile: g++ -std=c++17 sudoku_solver.cpp -o sudoku_solver  
3. Run: ./sudoku_solver  

---

## Notes

This solver is built around constraint checking and elimination. It handles easy boards well but does not attempt deeper search when multiple possibilities remain.

The implementation prioritizes clarity over optimization. Candidate tracking is done with maps and vectors, which keeps the logic readable but could be improved for efficiency.

---

## Future Improvements

- Add recursive backtracking for harder puzzles  
- Expand elimination logic to better handle 3x3 box constraints  
- Support reading puzzles from file input instead of hardcoding  
- Separate solver logic from printing/debug output  
- Improve performance by reducing repeated candidate recomputation  

---

## Contact

Astrid Greene  
astridig@umich.edu
