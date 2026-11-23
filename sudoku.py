from collections import defaultdict
from colorama import Fore, init

init(autoreset=True)

board = [['.' for _ in range(9)] for _ in range(9)]

# (row, col) depending on whether that is a mistake
# similar to NYTimes, it only marks as a mistake if theres a conflict in
# the row, col, or box, not if it is wrong beyond that
not_valid = {}

def print_sudoku():
    # this took too long
    print("+-------+-------+-------+")
    for i, row in enumerate(board):
        print("|", end="")
        for j, col in enumerate(row):
            if ''.join(str(x) for x in (i, j)) in not_valid:
                print(Fore.RED + f" {not_valid[''.join(str(x) for x in (i, j))]}", end="")
                not_valid.pop(''.join(str(x) for x in (i, j)))
            else:
                print(f" {col}", end="")
            if (j-2) % 3 == 0:
                print(" |", end="")
        print()
        if (i-2) % 3 == 0:
            print("+-------+-------+-------+")

print_sudoku()

rows = defaultdict(set)
cols = defaultdict(set)
boxes = defaultdict(set)
for i in range(len(board)):
    for j in range(len(board[i])):
        if board[i][j] == '.':
            continue
        rows[i].add(board[i][j])
        cols[j].add(board[i][j])
        boxes[(i//3, j//3)].add(board[i][j])

def check_sudoku():
    # my leetcode submission :) valid sudoku vibes
    for i in range(len(board)):
        for j in range(len(board[i])):
            if board[i][j] == '.':
                continue
            if board[i][j] in rows[i]:
                return False 
            if board[i][j] in cols[j]:
                return False
            if board[i][j] in boxes[(i//3, j//3)]:
                return False
    return True

def check_val(row, col, val):
    return not (val in rows[row] or val in cols[col] or val in boxes[(row//3, col//3)])

def add_val(row, col, val):
    if not check_val(row, col, val):
        not_valid[(''.join(str(x) for x in (row, col)))] = val
        return False
    if board[row][col] != val and board[row][col] != '.':
        rows[row].remove(board[row][col])
        cols[col].remove(board[row][col])
        boxes[(row//3, col//3)].remove(board[row][col])
    rows[row].add(val)
    cols[col].add
    boxes[(row//3, col//3)].add(val)
    board[row][col] = val
    return True

def remove_val(row, col, val):
    rows[row].remove(val)
    cols[col].remove(val)
    boxes[(row//3, col//3)].remove(val)
    board[row][col] = '.'

while True:
    print("Please choose an option below by typing in 1 or 2.")
    print("1. Add/update a number from cell")
    print("2. Remove a number from a cell")
    response = int(input())
    while response != 1 and response != 2:
        print("Try again.")
        print()
        print("Please choose an option below by typing in 1 or 2.")
        print("1. Add/update a number from cell")
        print("2. Remove a number from a cell")
        response = int(input())
    print("Please enter the row you are choosing. Enter a number 1-9.")
    row = int(input())
    while row < 1 or row > 9:
        print("Try again.")
        print()
        print("Please enter the row you are choosing. Enter a number 1-9.")
        row = int(input())
    row -= 1
    print("Please enter the column you are choosing. Enter a number 1-9.")
    col = int(input())
    while col < 1 or col > 9:
        print("Try again.")
        print()
        print("Please enter the row you are choosing. Enter a number 1-9.")
        col = int(input())
    col -= 1
    if response == 1:
        print(f"Please enter the number you would like to add/update to {row}, {col}. Enter a number 1-9.")
        val = int(input())
        while val < 1 or val > 9:
            print("Try again.")
            print()
            print(f"Please enter the number you would like to add/update to {row}, {col}. Enter a number 1-9.")
            val = int(input())
        while not add_val(row, col, val):
            print("That is invalid. Try again")
            print_sudoku()
            print(f"Please enter the number you would like to add/update to ({row}, {col}). Enter a number 1-9.")
            val = int(input())
            while val < 1 or val > 9:
                print(f"Please enter the number you would like to add/update to {row}, {col}. Enter a number 1-9.")
                val = int(input())
        print_sudoku()
    else:
        remove_val(row, col, val)
        print_sudoku()