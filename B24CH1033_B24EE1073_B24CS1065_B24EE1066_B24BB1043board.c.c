#include <stdio.h>
#include "board.h"
    
int check_snake_or_ladder(int pos, int type, int mode) {
    switch (type) {
        case 1:
            switch (pos) {
                // Easy mode (more ladders, few snakes)
                case 4:
                case 9:
                case 28:
                case 40:
                    if (mode == 1) return 14;
                    break;

                case 17:
                case 62:
                    if (mode >= 1) return 7;
                    break;

                // Medium mode (less ladders, more snakes)
                case 11:
                case 20:
                    if (mode == 2) return 26;
                    break;

                case 43:
                case 64:
                    if (mode >= 2) return 24;
                    break;

                // Hard mode (almost no ladders, full snakes)
                case 5:
                    if (mode >= 3) return 35;
                    break;

                case 87:
                case 99:
                    if (mode >= 3) return 78;
                    break;
            }
            break;

        case 2:
            switch (pos) {
                case 3:
                case 11:
                case 50:
                    if (mode == 1) return 22;
                    break;

                case 25:
                case 43:
                    if (mode >= 1) return 5;
                    break;

                case 19:
                case 33:
                    if (mode == 2) return 59;
                    break;

                case 57:
                case 94:
                    if (mode >= 2) return 73;
                    break;

                case 6:
                    if (mode >= 3) return 44;
                    break;

                case 88:
                    if (mode >= 3) return 34;
                    break;
            }
            break;

        // Add more for other board types similarly...
        default:
            break;
    }

    return pos;
}
  


void print_board(int board_type) {
    printf("Board %d loaded with unique snakes and ladders.\n", board_type);

    
}
