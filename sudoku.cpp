#include <vector>
#include <cstdint>
#include <iostream>
#include <unordered_set>
#include <unordered_map>
#include <algorithm>
#include <chrono>

using namespace std;

struct Sudoku {
    vector<uint16_t> grid;
    unordered_map<size_t, vector<uint16_t>> possibilities; // all possible ints for each index
    void print_sudoku() {
        if (grid.size() != 81) return;
        cout << "_______________________________\n\n";
        for (size_t box_row = 0; box_row < 3; ++box_row) {
            for (size_t row = 0; row < 3; ++row) {
                for (size_t box_col = 0; box_col < 3; ++box_col) {
                    cout << "|";
                    for (size_t col = 0; col < 3; ++col) {
                        if (grid[(box_row*27) + (row*9) + ((box_col*3) + col)] > 9) {
                            cout << " _ ";
                        }
                        else {
                            cout << " " << grid[(box_row*27) + (row*9) + ((box_col*3) + col)] << " ";
                        }
                    }
                }
                cout << "|\n";
            }
            cout << "_______________________________\n\n";
        }
    }

    void player_view() {
        if (grid.size() != 81) return;
        cout << endl;
        cout << " | 0  1  2 | 3  4  5 | 6  7  8 |\n";
        cout << "_______________________________\n";
        cout << "_______________________________\n\n";
        for (size_t box_row = 0; box_row < 3; ++box_row) {
            for (size_t row = 0; row < 3; ++row) {
                cout << box_row*3 + row;
                for (size_t box_col = 0; box_col < 3; ++box_col) {
                    cout << "|";
                    for (size_t col = 0; col < 3; ++col) {
                        cout << " " << grid[(box_row*27) + (row*9) + ((box_col*3) + col)] << " ";
                    }
                }
                cout << "|\n";
            }
            cout << "_______________________________\n\n";
        }
    }

    // takes in row (not id)
    // returns true if val does not show up in the row
    bool check_row(size_t row, uint16_t val) {
        if (val > 10) return false;
        for (size_t i = (row*9); i < (row*9) + 9; ++i) {
            if (grid[i] > 10)  {
                cerr << "Error: value not in range\n";
                return false;
            }
            if (grid[i] == val) {
                return false;
            } 
        }
        return true;
    }

    // checks if row is valid
    bool check_row_validity(size_t row) {
        unordered_set<uint16_t> seen_vals;
        for (size_t i = (row*9); i < (row*9) + 9; ++i) {
            if (grid[i] > 10) {
                cerr << "Error: value not in range\n";
                return false;
            }
            if (seen_vals.count(grid[i])) return false;
            else if (grid[i] != 10) {
                seen_vals.insert(grid[i]);
            }
        }
        return true;
    }

    // takes in col (not id)
    // returns true if val does not show up in the col
    bool check_col(size_t col, uint16_t val) {
        if (val > 10) return false;
        for (size_t i = col; i <= col + 72; i+=9) {
            if (grid[i] > 10) {
                cerr << "Error: value not in range\n";
                return false;
            }
            if (grid[i] == val) return false;
        }
        return true;
    }

    // checks if col is valid
    bool check_col_validity(size_t col) {
        unordered_set<uint16_t> seen_vals;
        for (size_t i = col; i < col + 72; i+=9) {
            if (grid[i] > 10) {
                cerr << "Error: value not in range\n";
                return false;
            }
            if (seen_vals.count(grid[i])) return false;
            else if (grid[i] != 10) {
                seen_vals.insert(grid[i]);
            }
        }
        return true;
    }

    // takes in box (not id)
    // returns true if val does not show up in the box
    bool check_box(size_t box, uint16_t val) {
        if (val > 10) return false;
        for (size_t i = 0; i < 3; ++i) {
            for (size_t j = 0; j < 3; ++j) {
                if (grid[box+i+(j*9)] > 10) {
                    cerr << "Error: value not in range\n";
                    return false;
                }
                if (grid[box+i+(j*9)] == val) return false;
            }
        }
        return true;
    }

    // checks box validity
    bool check_box_validity(size_t box) {
        unordered_set<uint16_t> seen_vals;
        for (size_t i = 0; i < 3; ++i) {
            for (size_t j = 0; j < 3; ++j) {
                if (grid[box+i+(j*9)] > 10) {
                    cerr << "Error: value not in range\n";
                    return false;
                }
                else if (seen_vals.count(grid[box+i+(j*9)])) return false;
                else if (grid[box+i+(j*9)] != 10) {
                    seen_vals.insert(grid[box+i+(j*9)]);
                }
            }
        }
        return true;
    }

    // checks to see if whole puzzle is accurate
    bool check_puzzle() {
        for (size_t row = 0; row < 9; ++row) {
            if (!check_row_validity(row)) return false;
        }

        for (size_t col = 0; col < 9; ++col) {
            if (!check_col_validity(col)) return false;
        }


        for (size_t box = 0; box <= 6; box += 3) {
            if (!check_box_validity(box)) return false;
        }

        for (size_t box = 27; box <= 33; box += 3) {
            if (!check_box_validity(box)) return false;
        }

        for (size_t box = 54; box <= 60; box += 3) {
            if (!check_box_validity(box)) return false;
        }
        return true;
    }

    // must be in [0,8]
    size_t which_row(size_t id) {
        return id/9;
    }

    // must be in [0,8]
    size_t which_col(size_t id) {
        return id%9;
    }

    // returns top-leftmost index of box
    // must be in {0, 3, 6, 27, 30, 33, 54, 57, 60}
    size_t which_box(size_t id) {
        return ((which_row(id)/3)*27) + (which_col(id)/3)*3;
    }

    size_t find_id(size_t row, size_t col) {
        return row*9 + col;
    }

    // updates possibilities for index and returns number of possibilities
    size_t find_possibilities(size_t id) {
        vector<uint16_t> final_possibilities = {};
        for (uint16_t val = 1; val <= 9; ++val) {
            if (check_row(which_row(id), val) &&
                check_col(which_col(id), val) &&
                check_box(which_box(id), val)
                ) {
                if (id == 9) {
                }
                final_possibilities.push_back(val);
            }
        }
        possibilities[id] = final_possibilities;
        return final_possibilities.size();
    }

    bool completed_sudoku() {
        for (size_t i = 0; i < 81; ++i) {
            if (grid[i] == 10) return false;
        }
        return true;
    }

    void update_row_possibilities(size_t row) {
        for (size_t i = row*9; i < (row*9)+9; ++i) {
            find_possibilities(i);
        }
    }

    void update_col_possibilities(size_t col) {
        for (size_t i = col; i <= col + 72; i += 9) {
            find_possibilities(i);
        }
    }

    // void update_box_possibilities(size_t row) {
    //     for (size_t i = row*9; i < (row*9)+9; ++i) {
    //         find_possibilities(i);
    //     }
    // }

    // returns first guaranteed possible change
    uint16_t id_niche_possibilities(size_t id) {
        update_row_possibilities(which_row(id));
        unordered_set<uint16_t> vals;
        unordered_set<uint16_t> nope;
        for (size_t i = which_row(id)*9; i < (which_row(id)*9) + 9; ++i) {
            if (i == id) continue;
            for (size_t j = 0; j < possibilities[i].size(); ++j) {
                nope.insert(possibilities[i][j]);
            }
        }
        for (size_t i = 0; i < possibilities[id].size(); ++i) {
            if (!nope.count(possibilities[id][i])) vals.insert(possibilities[id][i]);
        }
        if (vals.size() == 1) {
            return *vals.begin();
        }

        update_col_possibilities(which_col(id));
        unordered_set<uint16_t> vals_c;
        unordered_set<uint16_t> nope_c;
        for (size_t i = which_col(id); i <= which_col(id) + 72; i += 9) {
            if (i == id) continue;
            for (size_t j = 0; j < possibilities[i].size(); ++j) {
                nope_c.insert(possibilities[i][j]);
            }
        }
        for (size_t i = 0; i < possibilities[id].size(); ++i) {
            if (!nope_c.count(possibilities[id][i])) vals_c.insert(possibilities[id][i]);
        }
        if (vals_c.size() == 1) {
            return *vals_c.begin();
        }
        return 10;
        }
        
        //25

        // update_col_possibilities(which_col(id));


    void play(bool print) {
        print_sudoku();
        bool change_occured = true;
        while (!completed_sudoku() && change_occured) {
            change_occured = false;
            for (size_t i = 0; i < 81; ++i) {
                if (grid[i] < 10) continue;
                if (find_possibilities(i) == 1) {
                    change_occured = true;
                    grid[i] = possibilities[i][0];
                    if (print) print_sudoku();
                }
                uint16_t niche = id_niche_possibilities(i);
                if (niche != 10) {
                    change_occured = true;
                    grid[i] = niche;
                    if (print) print_sudoku();
                }
            }
        }
        if (change_occured) {
            if (check_puzzle()) {
                cout << "Completed Sudoku:\n";
                print_sudoku();
            }
        }
        else {
            cout << "Could not complete sudoku\n";
        }
    }
};

/*

indexes:
_______________________________
|[0][1][2]|[3][4][5]|[6][7][8]|
|[9][10][11]|[12][13][14]|[15][16][17]|
|[18][19][20]|[21][22][23]|[24][25][26]|
_______________________________
|[27][28][29]|[30][31][32]|[33][34][35]|
|[36][37][38]|[39][40][41]|[42][43][44]|
|[45][46][47]|[48][49][50]|[51][52][53]|
______________________________
|[54][55][56]|[57][58][59]|[60][61][62]|
|[63][64][65]|[66][67][68]|[69][70][71]|
|[72][73][74]|[75][76][77]|[78][79][80]|
_______________________________


*/

int main() {
    Sudoku sudoku;

    vector<uint16_t> easy_sudoku = {
        10, 8, 9, 5, 10, 10, 3, 1, 10,
        1, 10, 10, 10, 3, 7, 10, 2, 8,
        3, 4, 10, 8, 10, 10, 10, 10, 10,
        6, 9, 8, 10, 10, 10, 10, 10, 7,
        10, 7, 10, 10, 10, 10, 2, 4, 3,
        10, 10, 10, 7, 1, 5, 10, 9, 10,
        9, 10, 3, 10, 10, 10, 5, 10, 2,
        8, 10, 7, 9, 10, 6, 10, 10, 10,
        10, 10, 5, 10, 2, 8, 10, 7, 9
    };

    sudoku.grid = easy_sudoku;

    auto start = chrono::high_resolution_clock::now();
    sudoku.play(true);
    auto end = chrono::high_resolution_clock::now();
    chrono::duration<double> seconds = end - start;
    std::cout << "Time taken: " << seconds.count() << " seconds\n";

    /*
        7 8 9 5 6 2 3 1 4
        1 5 6 4 3 7 9 2 8
        3 4 2 8 9 1 7 6 5
        6 9 8 2 4 3 1 5 7
        5 7 1 6 8 9 2 4 3
        2 3 4 7 1 5 8 9 6
        9 6 3 1 7 4 5 8 2
        8 2 7 9 5 6 4 3 1
        4 1 5 3 2 8 6 7 9
    */

    // vector<uint16_t> medium_sudoku = {
    //     9, 4, 10, 10, 5, 10, 10, 1, 10,
    //     10, 10, 10, 7, 10, 10, 3, 10, 10,
    //     7, 10, 10, 3, 1, 4, 10, 10, 10,
    //     10, 10, 4, 10, 10, 10, 9, 5, 8,
    //     10, 10, 10, 4, 10, 10, 6, 10, 10,
    //     10, 10, 10, 5, 9, 7, 10, 10, 4,
    //     3, 10, 10, 6, 10, 10, 10, 10, 10,
    //     10, 10, 8, 10, 10, 10, 10, 10, 6,
    //     6, 10, 1, 10, 10, 10, 10, 10, 10
    // };

    // sudoku.grid = medium_sudoku;

    // start = chrono::high_resolution_clock::now();
    // sudoku.play(true);
    // end = chrono::high_resolution_clock::now();
    // seconds = end - start;
    // std::cout << "Time taken: " << seconds.count() << " seconds\n";

    return 0;
}






    // vector<uint16_t> test_print = {};
    // for (uint16_t i = 0; i < 9; ++i) {
    //     for (uint16_t val = 1; val <= 9; ++val) {
    //         test_print.push_back(val);
    //     }
    // }
    // vector<uint16_t> indexes = {};
    // for (uint16_t i = 0; i < 81; ++i) {
    //     indexes.push_back(i);
    // }
    // vector<uint16_t> valid_sudoku = {
    //     4, 3, 5, 2, 6, 9, 7, 8, 1,
    //     6, 8, 2, 5, 7, 1, 4, 9, 3,
    //     1, 9, 7, 8, 3, 4, 5, 6, 2,
    //     8, 2, 6, 1, 9, 5, 3, 4, 7,
    //     3, 7, 4, 6, 8, 2, 9, 1, 5,
    //     9, 5, 1, 7, 4, 3, 6, 2, 8,
    //     5, 1, 9, 3, 2, 6, 8, 7, 4,
    //     2, 4, 8, 9, 5, 7, 1, 3, 6,
    //     7, 6, 3, 4, 1, 8, 2, 5, 9
    // };
    // vector<uint16_t> another_valid_sudoku = {
    //     9, 7, 4, 8, 2, 5, 3, 1, 6,
    //     6, 8, 5, 9, 3, 1, 4, 2, 7,
    //     2, 1, 3, 6, 4, 7, 8, 5, 9,
    //     5, 3, 7, 2, 8, 6, 1, 9, 4,
    //     4, 6, 8, 7, 1, 9, 2, 3, 5,
    //     1, 2, 9, 3, 5, 4, 6, 7, 8,
    //     3, 5, 2, 4, 7, 8, 9, 6, 1,
    //     7, 4, 6, 1, 9, 2, 5, 8, 3,
    //     8, 9, 1, 5, 6, 3, 7, 4, 2
    // };
    // sudoku.grid = valid_sudoku;
    // cout << sudoku.check_puzzle() << endl;

    // sudoku.grid = test_print;
    // cout << sudoku.check_puzzle() << endl;

    // sudoku.grid = indexes;
    // cout << sudoku.check_puzzle() << endl;

    // sudoku.grid = another_valid_sudoku;
    // cout << sudoku.check_puzzle() << endl;