#include <time.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#include "randlib.h"

#ifndef MAIN_H_
#define MAIN_H_
#define CARDCOUNT 52

int deck[52];

void initialize_deck(int *deck[]);
void shuffle(int deck[]);
void swap(int *a, int *b);

void shift_hand(int hand[]);
void add_minor_victory(int hand[], int card1, int card2, int handsize);
void add_war_victory(int hand[], int cards_won[], int handsize, int woncards);

void printcard(int);
void printhand(int hand[], int handsize);

//Returns the number of turns that the game took.
int play_round(int deck[]);


#endif /* MAIN_H_ */
