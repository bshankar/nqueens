#ifndef BOARD_STATE_H_MZEYWVGT
#define BOARD_STATE_H_MZEYWVGT

#include <vector>

class board_state {
public:
    board_state(int board_size);
    void solve();
    void search(int row);
private:
    int board_size;
    std::vector<int> cols;
    std::vector<bool> col_occ,
        diag_occ,
        antidiag_occ;
    unsigned long solutions = 0;
};

#endif /* end of include guard: BOARD_STATE_H_MZEYWVGT */
