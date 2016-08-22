#include "board_state.h"
#include <iostream>
using namespace std;

int main(int argc, char *argv[]) {
    cout << "N-queens solver by Bhavani Shankar (2016)" << endl;
    cout << "ebs@openmailbox.org" << endl << endl;

    if (argc != 2) {
        cout << "Usage: ./nq <board size>" << endl;
        exit(1);
    }

    board_state bs(atoi(argv[1]));
    bs.solve();
}
