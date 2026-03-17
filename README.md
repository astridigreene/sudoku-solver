# Tic-Tac-Toe

A keyboard-controlled Tic-Tac-Toe game built in Python with turtle graphics. Supports two-player gameplay, win and tie detection, scoreboard tracking, reset controls, and replay flow.

Made with Python, turtle

By Astrid Greene astridig@umich.edu

---

## Overview

This project is a two-player Tic-Tac-Toe game built using Python’s turtle graphics library. Players use the keyboard to place moves, and the game draws the board and pieces directly on screen while tracking the full game state.

It was built to connect input handling, graphics, and game logic in a single program.

---

## Features

- Two-player local gameplay  
- Keyboard controls for both players  
- Turtle-based board and piece rendering  
- Win detection across rows, columns, and diagonals  
- Tie detection  
- Scoreboard tracking across multiple rounds  
- Reset and replay controls  
- Basic error checking for invalid states  

---

## Controls

### Player 1
Uses keys 1 through 9 to place Xs

### Player 2
Uses keys a through i to place Os

### Other Controls
- space resets the board  
- z quits and shows final results  
- 0 starts a new game  

---

## How It Works

The program draws the grid using turtle graphics and maps each key press to a specific board position.

Each move updates counters tied to rows, columns, and diagonals. After every move, the game checks whether a player has completed a winning line or if the board is full.

A scoreboard keeps track of wins and ties across rounds. The game can reset and continue without restarting the program.

---

## Tech Stack

- Python  
- turtle  

---

## File Structure

- tic_tac_toe.py — main game file  

---

## How to Run

1. Make sure Python is installed  
2. Run: python tic_tac_toe.py  
   or: python3 tic_tac_toe.py  

---

## Notes

This was an early project focused on combining graphics, input handling, and game logic in one place. The state is tracked using global variables and counters, which keeps things straightforward but makes the code harder to extend.

The game works reliably, but the structure could be cleaner if rebuilt with a more formal board representation.

---

## Future Improvements

- Refactor game state into a structured board (2D array or class-based model)  
- Prevent invalid moves before they are processed  
- Separate rendering, input handling, and game logic  
- Add single-player mode  
- Improve layout and text rendering  

---

## Contact

Astrid Greene  
astridig@umich.edu
