#ifndef BOARD_STATE_H_MZEYWVGT
#define BOARD_STATE_H_MZEYWVGT

#include <cstdint>

#define MIN_BOARD 4
#define MAX_BOARD 64
typedef uint64_t board_t;

class board_state {
public:
    board_state(int board_size);
    void solve();
private:
    int board_size;
    board_t ONE = 1;
    board_t valid_cols[MAX_BOARD];
    board_t solutions = 0;

    // pre calculate and store all the constraints
    void init_tables();
    void cover(int row, int col);
    void uncover(int row, int col);
    void search(int row);
};

#endif /* end of include guard: BOARD_STATE_H_MZEYWVGT */
