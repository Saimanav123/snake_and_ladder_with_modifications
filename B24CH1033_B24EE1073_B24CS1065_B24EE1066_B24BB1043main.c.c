#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "game.h"
#include "board.h"
#include "ai.h"
#include "display.h"
#include "trivia.h"
#include "stats.h"
#include "crazy_tiles.h"
#include "undo.h"

#define MAX_PLAYERS 4

int previous_position[MAX_PLAYERS];
int undo_done[MAX_PLAYERS];
void undo_move(int player);

int main() {
    int num_players, ai_player = -1;
    int positions[MAX_PLAYERS] = {0};
    Stats stats[MAX_PLAYERS] = {0};

    srand(time(NULL));
    print_welcome();
    char input;
    printf("Type 'H' for instructions or any other key to continue: ");

    getchar(); // to consume newline
    input = getchar();

    if (input == 'H' || input == 'h') {
        printf("\033[2J\033[H");
        printf("\a");
        printf("\n\033[1;4;36mINSTRUCTIONS:\033[0m\n");
        printf("\033[1;32m- Reach 100 to win.\n");
        printf("- Climb ladders, avoid snakes.\033[0m\n");
        printf("\033[5;33m- In CRAZY Mode:\033[0m\n");
        printf("  \033[1;31mReverse:\033[0m Go back 5\n");
        printf("  \033[1;35mSwap:\033[0m Swap with random player\n");
        printf("  \033[1;34mFast Forward:\033[0m Move ahead 10\n");
        printf("  \033[1;33mStun:\033[0m Skip next turn\n");
        printf("  \033[1;91mBomb:\033[0m Back to start\n");
        printf("\n\033[4;36mPress Enter to start the game...\033[0m");
        getchar(); getchar();
    }

    printf("Enter number of players (2-4): ");
    scanf("%d", &num_players);
    if (num_players < 2 || num_players > 4) num_players = 2;

    for (int i = 0; i < num_players; i++) {
        printf("Enter name for Player %d: ", i + 1);
        scanf("%s", stats[i].name);
        stats[i].dice_rolls = 0;
        stats[i].snakes = 0;
        stats[i].ladders = 0;
        stats[i].stunned = 0;
    }

    // Ask the player if they want to load previous stats
    char load_choice;
    printf("Do you want to load previous player stats? (Y/N): ");
    scanf(" %c", &load_choice);  // Space before %c to consume any leftover newline

    if (load_choice == 'Y' || load_choice == 'y') {
        load_stats(stats, num_players);  // Load stats from the file
        printf("Player stats loaded successfully.\n");
    } else {
        printf("Starting with new stats.\n");
    }

    printf("Do you want to add an AI player? (Enter player number to assign AI, or 0 for none): ");
    scanf("%d", &ai_player);
    if (ai_player < 1 || ai_player > num_players) ai_player = -1;

    int board_type;
    printf("Choose a board to start (1-5): ");
    scanf("%d", &board_type);
    if (board_type < 1 || board_type > 5) board_type = 1;

    GameSettings settings;
    printf("Select difficulty (1=Easy, 2=Medium, 3=Hard, 4=Crazy): ");
    scanf("%d", &settings.mode);
    if (settings.mode < 1 || settings.mode > 4) settings.mode = 2;
    settings.board_type = board_type;

    print_board(board_type);
    int winner = -1;
    int turn = 0;

    for (int i = 0; i < MAX_PLAYERS; i++) {
        previous_position[i] = 0;
        undo_done[i] = 0;
    }

    while (winner == -1) {
        int player = turn % num_players;
        printf("\nPlayer %d's Turn%s\n", player + 1, (player + 1 == ai_player) ? " (AI)" : "");

        if (player + 1 == ai_player) {
            positions[player] = ai_turn(positions[player], &stats[player], settings.board_type, settings.mode);
        } else {
            previous_position[player] = positions[player];
            undo_done[player] = 0;
            positions[player] = take_turn(player + 1, positions[player], &stats[player], &settings, positions, num_players);
        }

        if (undo_done[player] == 0) {
            char undo_choice;
            printf("Do you want to undo your last move? (Y/N): ");
            scanf(" %c", &undo_choice);

            if (undo_choice == 'Y' || undo_choice == 'y') {
                undo_move(player);
            }
        }

        if (positions[player] >= 100) {
            winner = player;
            break;
        }

        check_trivia_tile(player + 1, &positions[player]);

        if (positions[player] == 20 || positions[player] == 40 || positions[player] == 60 || positions[player] == 80) {
            board_type = (rand() % 5) + 1;
            printf("\nSwitching to Board %d!\n", board_type);
            print_board(board_type);
        }

        print_ascii_board(positions, num_players);
        turn++;
    }

    printf("\nPlayer %d Wins the Game!\n", winner + 1);
    show_stats(stats, num_players);

    // Automatically save stats at the end of the game
    save_stats(stats, num_players);
    printf("Player stats saved successfully.\n");

    return 0;
}
