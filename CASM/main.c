#include "main.h"

int main()
{

    int answer;

    printf("\nHow many games would you like to simulate?\n");

    scanf("%d", &answer);

    printf("You made it here\n");
    srand(time(NULL));
    initialize_deck(&deck);
    printf("You made it here too, deck initialized!\n");
    shuffle(&deck);
    printf("Deck shuffled!\n");
    play_round(deck);

    return 0;
}

void swap (int *a, int *b)
{
    int temp = *a;
    *a = *b;
    *b = temp;
}

void shuffle(int deck[]){
	//TODO : New seeding algorithm

    for (int i = CARDCOUNT-1; i > 0; i--)
    {
        int j = rand() % (i+1);
        swap(&deck[i], &deck[j]);
    }
}

void initialize_deck(int *deck[])
{
	int i;
	for (i=0; i<CARDCOUNT; i++)
    {
        deck[i] = i;
    }
}


void printcard(int card)
{
	if(card!=-1){
		char suit[4] = {'S','D','H','C'};
		char face[13] = {'2','3','4','5','6','7','8','9','X','J','Q','K','A'};
		printf ("%c%c", face[card%13], suit[card/13]);
	}
	else if(card==-1){
		printf ("ER");
	}

}

void printhand(int hand[], int handsize){
	for(int i = 0; i<handsize; i++){
		printcard(hand[i]);
		printf(" ");
	}
	printf("\n");
}

int play_round(int deck[]){
	int player_one_cards = 0;
	int player_two_cards = 0;
	int player_one[CARDCOUNT];
	int player_two[CARDCOUNT];

	//Deal the cards to players, initialize the rest of the deck with nullcards (-1)
	int i;
	for(i = 0; i<26; i++){
		player_one[i] = deck[i];
		player_one_cards++;
	}
	for(int x = 26; x < 52; x++){
		player_one[x] = -1;
	}

	for(int j = 0; j < 26; j++, i++){
		player_two[j] = deck[i];
		player_two_cards++;
	}
	for(int x = 26; x < 52; x++){
			player_two[x] = -1;
	}

	printf("Cards dealt to players, beginning round!\n");

	getchar();
	getchar();
	//The game part.
	int count = 0;

	while(player_one_cards!=CARDCOUNT && player_two_cards!=CARDCOUNT){
		count++;

		if((player_one[0]%13)<(player_two[0]%13)){

			int card1, card2;

			memcpy(&card1, &player_one[0], sizeof(int));
			memcpy(&card2, &player_two[0], sizeof(int));
			shift_hand(player_one); shift_hand(player_two);

			player_one_cards--; player_two_cards--;
			add_minor_victory(player_two, card1, card2, player_two_cards);
			player_two_cards+=2;

		} else if((player_one[0]%13)>(player_two[0]%13)){

			int card1, card2;
			memcpy(&card1, &player_one[0], sizeof(int));
			memcpy(&card2, &player_two[0], sizeof(int));

			shift_hand(player_one); shift_hand(player_two);
			player_one_cards--; player_two_cards--;
			add_minor_victory(player_one, card1, card2, player_one_cards);

			player_one_cards+=2;

		} else {

			int cards[52];
			memcpy(&cards[0], &player_one[0], sizeof(int));
			memcpy(&cards[1], &player_two[0], sizeof(int));
			memcpy(&cards[2], &player_one[1], sizeof(int));
			memcpy(&cards[3], &player_two[1], sizeof(int));
			memcpy(&cards[4], &player_one[2], sizeof(int));
			memcpy(&cards[5], &player_two[2], sizeof(int));
			for(int i=0; 3>i; i++){
				shift_hand(player_one); shift_hand(player_two);
				player_one_cards--;
				player_two_cards--;
			}

			if((cards[4]%13) > (cards[5]%13)){
				add_war_victory(player_one, cards, player_one_cards, 6);
				player_one_cards+=6;
			} else if((cards[5]%13) > (cards[4]%13)) {
				add_war_victory(player_two, cards, player_two_cards, 6);
				player_two_cards+=6;
			} else {
				int firstrun = 1;
				int n = 6;
				int n_player = 3;

				while( (cards[n]%13) == (cards[n+1]%13) || (firstrun==1)){
					shift_hand(player_one); shift_hand(player_two);
					player_one_cards--;
					player_one_cards--;

					memcpy(&cards[n], &player_one[n_player], sizeof(int));
					memcpy(&cards[n+1], &player_two[n_player], sizeof(int));
					n+=2;
					n_player++;
					firstrun = 0;
				}
				if((cards[n-2]%13) > (cards[n-1]%13)){
					add_war_victory(player_one, cards, player_one_cards, n);
					player_one_cards+=n;
				} else if((cards[n-2]%13) > (cards[n-1]%13)) {
					player_two_cards+=n;
					add_war_victory(player_two, cards, player_two_cards, n);
					player_one_cards+=n;
				}
			}
		}
	}
	printf("IT TOOK ONLY %d TURNS\n", count);
	if(player_one_cards==CARDCOUNT){
		printf("PLAYER ONE WINS THE WAR!");
		return 1;
	} else {
		printf("PLAYER TWO WINS THE WAR!");
		return 2;
	}
}

void shift_hand(int hand[]){
	for(int i=0; i<CARDCOUNT-1; i++){
		memcpy(&hand[i], &hand[i+1], sizeof(int));
	}
	hand[CARDCOUNT-1] = -1;
}

void add_minor_victory(int hand[], int card1, int card2, int handsize){
	hand[handsize-1] = card1;
	hand[handsize] = card2;
}
void add_war_victory(int hand[], int cards_won[], int handsize, int woncards){
	for(int i=0; i<woncards; i++){
		hand[(handsize-1)+i] = cards_won[i];
	}
}

