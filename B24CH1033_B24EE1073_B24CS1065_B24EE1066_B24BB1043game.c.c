#include <stdio.h>
#include <stdlib.h>
#include "game.h"
#include "board.h"
#include "stats.h"
#include "crazy_tiles.h"
#include<windows.h>


#include <stdio.h>
#include <unistd.h> // for sleep (optional, Unix-based)

void print_welcome() {
    // Ring bell for dramatic effect
    printf("\a");

    // Flashing effect (bright yellow)
    printf("\033[5;33m");
    printf("===========================================\n");
    printf("\033[0m");

    // Frame Top
    printf("\033[1;32m");
    printf("   +==============================+\n");

    // Title with bold red, white, and blue, and underlined SNAKE
    printf("   | \033[1;31m*** \033[4mSNAKE\033[0m \033[1;37mAND \033[1;34mLADDER *** \033[1;32m|\n");

    // Frame Mid
    printf("   |------------------------------|\n");

    // ASCII effect lines with underlined text for key phrases
    printf("   | \033[1;36m\033[4mGet Ready\033[0m to Roll the Dice!     \033[1;32m|\n");
    printf("   | \033[1;35mWatch out for \033[4mSnakes\033[0m!           \033[1;32m|\n");
    printf("   | \033[1;33m\033[4mClimb the Ladders\033[0m to Win!       \033[1;32m|\n");

    // Frame Bottom
    printf("   +==============================+\n");

    // Wavy border below
    printf("\033[1;33m");
    printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");

    // Reset color
    printf("\033[0m");
}


#include <stdio.h>

void print_dice_face(int value) {
    const char *faces[] = {
        // Dice face 1 (bold red and underline)
        "\033[1;31m\n+-------+\n|       |\n|   o   |\n|       |\n+-------+\n\033[0m",
        
        // Dice face 2 (yellow and underlined)
        "\033[1;33m\n+-------+\n| o     |\n|       |\n|     o |\n+-------+\n\033[0m",
        
        // Dice face 3 (green and bold)
        "\033[1;32m\n+-------+\n| o     |\n|   o   |\n|     o |\n+-------+\n\033[0m",
        
        // Dice face 4 (blue)
        "\033[1;34m\n+-------+\n| o   o |\n|       |\n| o   o |\n+-------+\n\033[0m",
        
        // Dice face 5 (cyan and blinking)
        "\033[1;36m\033[5m\n+-------+\n| o   o |\n|   o   |\n| o   o |\n+-------+\n\033[0m",
        
        // Dice face 6 (magenta with bold)
        "\033[1;35m\n+-------+\n| o   o |\n| o   o |\n| o   o |\n+-------+\n\033[0m"
    };

    // Play a sound effect (bell) for dramatic roll
    printf("\a");

    // Print the selected dice face with color
    printf("%s", faces[value - 1]);
}

int roll_dice(int is_ai) {
    int final_roll = (rand() % 6) + 1;

    if (!is_ai) {
        printf("Rolling dice");
        for (int i = 0; i < 5; i++) {
            int temp = (rand() % 6) + 1;
            printf("\r");
            print_dice_face(temp);
            Sleep(200);
            system("cls"); // Clear screen for animation effect
        }
        print_dice_face(final_roll);
        printf("You rolled: %d\n", final_roll);
    }

    return final_roll;
}




int take_turn(int player, int position, Stats *s, GameSettings *gs, int *positions, int num_players) {
    if (s->stunned) 
    {
        printf(" Player %d is stunned! Skipping turn.\n", player);
        s->stunned = 0;
        return position;

    }

    printf("Press Enter to roll dice...");
    getchar(); getchar();
    int roll = roll_dice(0);
    s->dice_rolls++;

    if (position + roll > 100) 
    {
        printf("Can't move. Stay at %d\n", position);
        return position;

    }

    position += roll;
    int new_pos = check_snake_or_ladder(position, gs->board_type, gs->mode);
    
    if (new_pos > position)
     {
        
        printf(" Climbed a ladder to %d!\n", new_pos);
        s->ladders++;

    } 
    else if (new_pos < position) 
    {

        printf(" Bitten by a snake to %d!\n", new_pos);
        s->snakes++;
    }

    position = new_pos;

    if (gs->mode == 4) {

        position = check_special_tiles(player, position, positions, s, num_players);
        
    }

    return position;
}

