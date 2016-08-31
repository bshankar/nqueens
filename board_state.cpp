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
}


void board_state::solve() {
    search(0, 0, 0);
    cout << "Board size " << board_size << ": "
         << solutions << " solutions found." << endl;
}

void board_state::search(board_t left_diag, board_t col,
                         board_t right_diag) {
    if (col == FULL) {
        ++solutions;
        return;
    }

    board_t empty_slots = ~(col | left_diag | right_diag);
    while (empty_slots & FULL) {
        board_t empty_slot = empty_slots & -empty_slots;
        empty_slots -= empty_slot;
        search((left_diag | empty_slot) >> 1, col | empty_slot,
               (right_diag | empty_slot) << 1);
    }
}
