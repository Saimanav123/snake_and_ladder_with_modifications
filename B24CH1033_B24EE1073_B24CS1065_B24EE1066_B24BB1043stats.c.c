#include <stdio.h>
#include <string.h>
#include "stats.h"
#define MAX_PLAYERS 4
FILE * fp;
void mainstat();
void show_stats(Stats *s, int n) {
    printf("\nFinal Stats:\n");
    for (int i = 0; i < n; i++) {
        printf("Player %d (%s):  Rolls=%d | Snakes=%d |  Ladders=%d\n",
               i + 1, s[i].name, s[i].dice_rolls, s[i].snakes, s[i].ladders);
    }
}

void save_stats(Stats stats[], int num_players) {
    FILE *file = fopen("player_stats.dat", "w");
    if (file == NULL) {
        printf("Error saving stats.\n");
        return;
    }

    for (int i = 0; i < num_players; i++) {
        fprintf(file, "%s %d %d %d %d\n", 
                stats[i].name, 
                stats[i].dice_rolls, 
                stats[i].snakes, 
                stats[i].ladders, 
                stats[i].stunned);
    }

    fclose(file);
    printf("Player stats saved successfully.\n");
}


void load_stats(Stats stats[], int num_players) {
    FILE *file = fopen("player_stats.dat", "r");
    if (file == NULL) {
        printf("No previous stats found.\n");
        return;
    }

    for (int i = 0; i < num_players; i++) {
        fscanf(file, "%s %d %d %d %d", 
               stats[i].name, 
               &stats[i].dice_rolls, 
               &stats[i].snakes, 
               &stats[i].ladders, 
               &stats[i].stunned);
    }

    fclose(file);
}



void display_stats(Stats stats[], int num_players) {
    for (int i = 0; i < num_players; i++) {
        printf("\nStats for Player %d: %s\n", i + 1, stats[i].name);
        printf("Dice Rolls: %d\n", stats[i].dice_rolls);
        printf("Snakes: %d\n", stats[i].snakes);
        printf("Ladders: %d\n", stats[i].ladders);
        printf("Stunned: %d\n", stats[i].stunned);
    }
}

void mainstat() {
    Stats stats[MAX_PLAYERS];
    int num_players = 2;  // Example: Assuming 2 players

    // Load previous stats if available
    char load_choice;
    printf("Do you want to load previous player stats? (Y/N): ");

    getchar();  // To consume leftover newline
    load_choice = getchar();  // Actual input

    if (load_choice == 'Y' || load_choice == 'y') {
        load_stats(stats, num_players);  // Load from file
        printf("Player stats loaded successfully.\n");

        // Display the loaded stats
        display_stats(stats, num_players);

    } else {
        printf("Starting with new stats.\n");

        // ✅ TEST DATA — TEMPORARY
        strcpy(stats[0].name, "Madhav");
        stats[0].dice_rolls = 12;
        stats[0].snakes = 3;
        stats[0].ladders = 4;
        stats[0].stunned = 1;

        strcpy(stats[1].name, "Alok");
        stats[1].dice_rolls = 15;
        stats[1].snakes = 2;
        stats[1].ladders = 6;
        stats[1].stunned = 0;

        save_stats(stats, num_players);
        printf("Test player stats saved.\n");
    }
}



    

