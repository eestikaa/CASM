#include "carddeck.h"

void initializeDeck(struct Deck *deck){
	int cardCounter = 0;
	for(int i=0; i<4; i++){
		for(int j=0; j<12; j++){
			deck->cards[cardCounter].suit = i;
			deck->cards[cardCounter].card = j;
			cardCounter++;
		}
	}
}

void randomize(struct Deck *input){
	int n = 52;
    srand ( time(NULL) );
    for (int i = n-1; i > 0; i--)
    {
        int j = rand() % (i+1);
        swap(&input->cards[i], &input->cards[j]);
    }
}
