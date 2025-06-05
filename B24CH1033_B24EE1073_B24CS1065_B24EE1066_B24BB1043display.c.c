#include <stdio.h>
#include "display.h"

#include <stdio.h>

void print_ascii_board(int *positions, int num_players) {
    printf("\n\033[1;37mBoard State:\033[0m\n\n");  // Bold white heading

    for (int i = 100; i >= 1; i--) {
        int found = 0;

        for (int j = 0; j < num_players; j++) {
            if (positions[j] == i) {
                switch(j) {
                    case 0: printf("\033[1;31mP1 \033[0m"); break; // Red
                    case 1: printf("\033[1;32mP2 \033[0m"); break; // Green
                    case 2: printf("\033[1;34mP3 \033[0m"); break; // Blue
                    case 3: printf("\033[1;33mP4 \033[0m"); break; // Yellow
                }
                found = 1;
                break;
            }
        }

        if (!found) {
            // Color alternate cells for a checkerboard feel
            if ((i / 10) % 2 == 0) {
                printf("\033[0;36m__ \033[0m"); // Cyan
            } else {
                printf("\033[0;35m__ \033[0m"); // Magenta
            }
        }

        if (i % 10 == 1) printf("\n");
    }

    printf("\n");
}

