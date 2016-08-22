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
    cols.resize(board_size);
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

    for (auto col = 0; col < board_size; ++col)
        if (!col_occ[col]) {
            cols[row] = col;
            int diag = row - col + board_size - 1,
                anti_diag = row + col;
            if (!(diag_occ[diag] || antidiag_occ[anti_diag])) {
                col_occ[col] = true;
                diag_occ[diag] = true;
                antidiag_occ[anti_diag] = true;
                search(row + 1);
                col_occ[col] = false;
                diag_occ[diag] = false;
                antidiag_occ[anti_diag] = false;
            }
        }
}
