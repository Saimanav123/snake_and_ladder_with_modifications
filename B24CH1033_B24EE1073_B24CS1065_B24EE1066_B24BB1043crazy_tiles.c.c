

#include <stdio.h>
#include <stdlib.h>
#include "stats.h"

int check_special_tiles(int player, int pos, int *positions, Stats *stats, int num_players) {


    switch (pos) {

        case 11:  // Reverse
            printf("Reverse Tile! Move back 5.\n");
            pos -= 5;
            break;


        case 22:  //  Swap
            {
                int other = rand() % num_players;
                if (other != player - 1) {
                    printf("Swap Tile! Swapping with Player %d.\n", other + 1);
                    int temp = positions[other];
                    positions[other] = pos;
                    pos = temp;
                }
            }
            break;


        case 33:  //  Fast Forward
            printf(" Fast Forward! Move ahead 10.\n");
            pos += 10;
            break;


        case 44:  // 🛑 Stun
            printf("Stun Tile! You’ll miss your next turn.\n");
            stats->stunned = 1;
            break;


        case 66:  // 💣 Bomb
            printf(" Bomb Tile! Back to start.\n");
            pos = 0;
            break;
    }
    
    return pos;
}
