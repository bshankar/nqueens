#ifndef BOARD_STATE_H_MZEYWVGT
#define BOARD_STATE_H_MZEYWVGT

typedef unsigned __int128 board_t;

class board_state {
public:
    board_state(int board_size);
    void solve();
    void search(int row);
private:
    int board_size;
    // column used, diag occupied, anti-diag occupied
    board_t constraints = 0, ONE = 1;
    board_t all_constraints[26][26] = {};
    unsigned long solutions = 0;

    // pre calculate and store all the constraints
    void calculate_constraints();
};

#endif /* end of include guard: BOARD_STATE_H_MZEYWVGT */
