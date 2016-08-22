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
    // column used, diag occupied, anti-diag occupied
    unsigned __int128 constraints = 0;
    unsigned long solutions = 0;
};

#endif /* end of include guard: BOARD_STATE_H_MZEYWVGT */
