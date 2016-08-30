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
    FULL = (~FULL) >> (MAX_BOARD - board_size);
    for (auto col = 0; col < board_size; ++col) {
        valid_cols[col] = FULL;
        exclude[col] = FULL ^ (ONE << col);
    }

    for (auto dist = 0; dist < board_size - 1; ++dist)
        for (auto col = 0; col < board_size; ++col) {
            masks[MAX_BOARD * dist + col] = ONE << 2 * (dist + 1) |
                                            ONE << (dist + 1) |
                                            ONE;

            // shift the masks properly
            if (dist + 1 > col)
                masks[MAX_BOARD * dist + col] >>= dist + 1 - col;
            else if (dist + 1 < col)
                masks[MAX_BOARD * dist + col] <<= col - dist - 1;

            // take the complement
            masks[MAX_BOARD * dist + col] = ~masks[MAX_BOARD * dist + col];
            // remove overflows
            masks[MAX_BOARD * dist + col] &= FULL;
        }
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
    while (valid_cols[row]) {
        int col = __builtin_ffsl(valid_cols[row]) - 1;
        // exclude this column
        valid_cols[row] &= exclude[col];
        board_t tmp[board_size];
        for (auto dist = 0; dist < board_size - row - 1; ++dist) {
            // back up old values
            tmp[row + dist + 1] = valid_cols[row + dist + 1];
            // mask all conflicting columns
            valid_cols[row + dist + 1] &= masks[MAX_BOARD * dist + col];
        }

        search(row + 1);
        // restore backed up values
        for (auto dist = 0; dist < board_size - row - 1; ++dist)
            valid_cols[row + dist + 1] = tmp[row + dist + 1];
    }
}
