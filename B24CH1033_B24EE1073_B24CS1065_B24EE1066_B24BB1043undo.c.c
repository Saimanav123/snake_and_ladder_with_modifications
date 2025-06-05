#include <stdio.h>
#include "undo.h"
#define MAX_PLAYERS 4

void mains();

int current_position[MAX_PLAYERS];
int previous_position[MAX_PLAYERS];
int undo_done[MAX_PLAYERS];

void reset_positions() {
    int i = 0;
    while (i < MAX_PLAYERS) {
        current_position[i] = 0;
        i = i + 1;
    }

    i = 0;
    while (i < MAX_PLAYERS) {
        previous_position[i] = 0;
        i = i + 1;
    }

    i = 0;
    while (i < MAX_PLAYERS) {
        undo_done[i] = 0;
        i = i + 1;
    }

    printf("Game reset done. All players are now at position 0.\n");
}

void move_player(int player_id, int dice_value) {
    if (player_id >= 0 && player_id < MAX_PLAYERS) {
        previous_position[player_id] = current_position[player_id];
        int new_position = current_position[player_id] + dice_value;
        current_position[player_id] = new_position;

        printf("Player %d rolled a %d.\n", player_id + 1, dice_value);
        printf("Player %d moved from position %d to position %d.\n",
               player_id + 1,
               previous_position[player_id],
               current_position[player_id]);
    } else {
        printf("Invalid player ID!\n");
    }   
}

void backtrack_step_by_step(int player_id, int current, int target) {
    // Ensure we don't go beyond the target position.
    if (current <= target) {
        current_position[player_id] = target;  // Set position to the target
        printf("Player %d is now at position %d (undo complete).\n", player_id + 1, target);
        return;
    }

    // Move the player back one step.
    current_position[player_id] = current - 1;

    printf("Undo step... Player e%d moved back to %d.\n", player_id + 1, current_position[player_id]);
 
    // Continue with the next recursive call.
    backtrack_step_by_step(player_id, current_position[player_id], target);
}

void undo_move(int player_id) {
    if (player_id >= 0 && player_id < MAX_PLAYERS) {
        if (undo_done[player_id] == 1) {
            printf("Player %d has already used their undo move.\n", player_id + 1);
        } else {
            printf("Undoing last move for Player %d...\n", player_id + 1);
            backtrack_step_by_step(player_id, current_position[player_id], previous_position[player_id]);
            undo_done[player_id] = 1;  // Mark undo as done
        }
    } else {
        printf("Invalid player ID!\n");
    }
}


void mains() {
    reset_positions();

    move_player(0, 4);
    move_player(1, 6);
    move_player(2, 3);
    move_player(3, 2);

    printf("\n");

    undo_move(0);
    undo_move(1);
    undo_move(1); 
    undo_move(2);
    undo_move(3);

    
}
