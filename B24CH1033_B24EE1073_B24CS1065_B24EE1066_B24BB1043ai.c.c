#include <stdio.h>
#include <stdlib.h>
#include "ai.h"
#include "game.h"
#include "board.h"
#include "stats.h"


int ai_turn(int position, Stats *s, int board_type, int mode)
 {

    int roll = roll_dice(1); // ai
printf("AI rolled: %d\n", roll);

    s->dice_rolls++;

    if (position + roll > 100) {
        printf("AI stays at %d\n", position);
        return position;
    }

    position += roll;
    int new_pos = check_snake_or_ladder(position, board_type, mode); // or board_type if mode stored separately


    if (new_pos > position) s->ladders++;
    else if (new_pos < position) s->snakes++;


    
    return new_pos; 


}
