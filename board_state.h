#ifndef BOARD_STATE_H_MZEYWVGT
#define BOARD_STATE_H_MZEYWVGT

#include <cstdint>

#define MIN_BOARD 4
#define MAX_BOARD 64
typedef uint64_t board_t;
typedef uint16_t row_t;

class board_state {
public:
    board_state(row_t board_size);
    void solve();
private:
    row_t board_size;
    board_t ONE  = 1,
            FULL = 0, // correct its value later
            right_half,
            solutions = 0;

    void search(board_t left_diag,
                board_t col, board_t right_diag,
                board_t right_half, board_t right_half2);
};

#endif /* end of include guard: BOARD_STATE_H_MZEYWVGT */
