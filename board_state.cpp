#include "board_state.h"
#include <iostream>

using std::cout;
using std::endl;

board_state::board_state(int board_size) {
    if (board_size < 2 || board_size > 26) {
        cout << "Valid board sizes are 2 to 26" << endl;
        exit(1);
    }
    this->board_size = board_size;
    calculate_constraints();
}

void board_state::calculate_constraints() {
    for (auto row = 0; row < board_size; ++row)
        for (auto col = 0; col < board_size; ++col)
            all_constraints[row][col] =
                (ONE << (col + 4 * board_size - 2))
                | (ONE << (row - col + 3 * board_size - 2))
                | (ONE << (row + col));
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
    // 1. Don't search for mirror solutions:  2x
    // 2. Use openmp for parallel search: jx
    // 3. Denser encoding of constraints preferably with 64bit arithmetic >= 2x
    // 4. Intelligently select a column for a row that has no violations
    for (auto col = 0; col < board_size; ++col) {
        board_t mask = all_constraints[row][col];
        if (constraints & mask)
            continue;

        constraints |= mask;
        search(row + 1);
        constraints = constraints & (~mask);
    }
}
