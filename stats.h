

#ifndef STATS_H
#define STATS_H

// All-time & per-game player stats
typedef struct {
    int dice_rolls;
    int snakes;
    int ladders;
    int stunned;
    char name[50]; // Player name for tracking
} Stats;

// Game configuration struct (used in game.c etc.)
typedef struct {
    int board_type;
    int mode; // 1=Easy, 2=Medium, 3=Hard, 4=Crazy
} GameSettings;

// Function prototypes
void show_stats(Stats *s, int n);
void load_stats(Stats *s, int n);
void save_stats(Stats *s, int n);

#endif

