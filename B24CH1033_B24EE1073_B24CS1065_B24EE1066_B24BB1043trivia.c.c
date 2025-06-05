#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "trivia.h"


void check_trivia_tile(int player, int *position) {
    if (*position % 13 == 0) {
        printf("\n Player %d triggered a TRIVIA tile!\n", player);
        char answer[100];
        printf("Q: On which national highway ,IIT Jodhpur located(type only number)\n");
        printf("Your Answer: ");
        scanf("%s", answer);

        if (strcmp(answer, "62") == 0 )     {
            printf(" Correct! You get a boost of 3!\n");
            *position += 3;
        } else {
            printf(" Wrong! You fall back by 3.\n");
            *position -= 3;
            if (*position < 0) *position = 0;
        }
    }
    if (*position % 29 == 0) {
        printf("\n Player %d triggered a TRIVIA tile!\n", player);
        char answer[100];
        printf("Q: Which popular indian batsman took a hattrick in 2009 ipl?\n");
        printf("Your Answer: ");
        scanf("%s", answer);

        if (strcmp(answer, "rohit sharma") == 0 || strcmp(answer, "Rohit sharma") == 0 || strcmp(answer, "Rohit Sharma") == 0 || strcmp(answer, "ROHIT SHARMA") == 0) {
            printf(" Correct! You get a boost of 3!\n");
            *position += 3;
        } else {
            printf(" Wrong! You fall back by 3.\n");
            *position -= 3;
            if (*position < 0) *position = 0;
        }
    }
}
