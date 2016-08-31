#include "board_state.h"
#include <iostream>

using std::cout;
using std::endl;

board_state::board_state(row_t board_size) {
    if (board_size < MIN_BOARD || board_size > MAX_BOARD) {
        cout << "Valid board sizes are " << MIN_BOARD <<
             " to " << MAX_BOARD << endl;
        exit(1);
    }
    this->board_size = board_size;
    FULL = (1 << board_size) - 1;
    right_half = (1 << (board_size / 2)) - 1;
}



void board_state::solve() {
    search(0, 0, 0, right_half, board_size % 2 ? right_half : 0);
    cout << "Board size " << board_size << ": "
         << 2 * solutions << " solutions found." << endl;
}

void board_state::search(board_t left_diag, board_t col,
                         board_t right_diag, board_t right_half,
                         board_t right_half2) {
    if (col == FULL) {
        ++solutions;
        return;
    }

    board_t empty_cols = ~(left_diag | right_diag | col | right_half) & FULL;
    while (empty_cols) {
        board_t empty_col = empty_cols & -empty_cols;
        empty_cols = empty_cols ^ empty_col;
        search((left_diag | empty_col) >> 1, col | empty_col,
               (right_diag | empty_col) << 1, right_half2, 0);
        right_half2 = 0;
    }
};
