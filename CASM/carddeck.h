#include <time.h>
#include <stdlib.h>

#ifndef CARDDECK_H_
#define CARDDECK_H_

/* SUIT ID
 * 0 - Spades
 * 1 - Hearts
 * 2 - Diamons
 * 3 - Clubs
 */

/* CARD ID
 * 0 - 2
 * 1 - 3
 * 2 - 4
 * 3 - 5
 * 4 - 6
 * 5 - 7
 * 6 - 8
 * 7 - 9
 * 8 - Jack
 * 9 - Queen
 * 10 - King
 * 11 - Ace
 */

struct Card{
	int suit = 0;
	int card = 0;
};

struct Deck{
	int cardsLeft = 52;
	struct Card cards[52];
};

void initializeDeck(struct Deck *deck);
void printCard(struct Card card);
void cardToChars(int suit, int card, char *stringToReturn);
void shuffleDeck(struct Deck *deck);

//Helper functionality for shuffling
void swap(struct Card *card1, struct Card *card2);
void randomize(struct Deck *input);

#endif
