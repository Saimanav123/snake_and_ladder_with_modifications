#ifndef UNDO_H
#define UNDO_H

#define MAX_PLAYERS 4

extern int current_position[MAX_PLAYERS];
extern int previous_position[MAX_PLAYERS];
extern int undo_done[MAX_PLAYERS];

void move_player(int player_id, int dice_value);
void undo_recursive(int player_id, int current, int target);
void undo_move(int player_id);
void reset_game();

#endif
