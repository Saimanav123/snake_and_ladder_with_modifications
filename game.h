#ifndef GAME_H
#define GAME_H

#include "stats.h"

void print_welcome();
int roll_dice(int is_ai);

int take_turn(int player, int position, Stats *s, GameSettings *gs, int *positions, int num_players);


#endif
