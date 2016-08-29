#include "board_state.h"
#include <iostream>

using std::cout;
using std::endl;

board_state::board_state(int board_size) {
    if (board_size < MIN_BOARD || board_size > MAX_BOARD) {
        cout << "Valid board sizes are " << MIN_BOARD <<
             " to " << MAX_BOARD << endl;
        exit(1);
    }
    this->board_size = board_size;
    init_tables();
}

void board_state::init_tables() {
    for (auto col = 0; col < board_size; ++col)
        valid_cols[col] = 0xffffffffffffffff >> (MAX_BOARD - board_size);
}

void board_state::solve() {
    search(0);
    cout << "Board size " << board_size << ": "
         << solutions << " solutions found." << endl;
}

void board_state::search(int row) {
    if (row == board_size) {
        ++solutions;
        return;
    }

    // critical loop
    // Ideas to optimze this loop:
    // 1. Search only for primitive solutions >= 2x
    // 2. Use openmp for parallel search: jx
    // 3. Denser encoding of constraints preferably with 64bit arithmetic >= 2x
    // 4. Intelligently select a column for a row that has no violations
    for (;;) {
        int col = __builtin_ffsl(valid_cols[row]);
        cover(row, col);
        search(row + 1);
        uncover(row, col);
    }
}

void board_state::cover(int row, int col) {
    // mask all conflicting rows, columns, diagonals
}

void board_state::uncover(int row, int col) {
    // unmask all conflicting rows, columns, diagonals
    // mask col which was already searched
}
