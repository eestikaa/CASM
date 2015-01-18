#include "main.h"

int main()
{

    int answer;

    printf("\nHow many games would you like to simulate?\n");

    scanf("%d", &answer);

    //We generate a random seed and XOR it with the time to generate a third seed.
    int random = arand(0);

    printf("Generated random in assembly function :  %d\n", random);
    srand(time(NULL)^random);
    int total_turns = 0;
    for(int j = 0; j<answer; j++){
        initialize_deck(&deck);
    	shuffle(&deck);
        total_turns +=play_round(deck);
    }
    int avg = total_turns/answer;
    printf("The average game took %d turns!\n Press enter to exit.", avg);
    getchar();
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

	//The game part.
	int count = 0;

	while(player_one_cards!=CARDCOUNT && player_two_cards!=CARDCOUNT){
		count++;
		if((player_one[0]%13==-1) && (player_two[0]%13==-1)){
			if(player_one_cards>player_two_cards){
				printf("Player one wins the war!\n");
				return count;
			} else {
				printf("Player one wins the war!\n");
				return count;
			}
		}
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
			int firstrun = 1;
			int n = 0;
			int n_player = 0;

			while( (cards[n]%13) == (cards[n+1]%13) || (firstrun==1) ){
				memcpy(&cards[n], &player_one[n_player], sizeof(int));
				memcpy(&cards[n+1], &player_two[n_player], sizeof(int));
				shift_hand(player_one); shift_hand(player_two);
				player_one_cards--;
				player_one_cards--;
				n+=2;
				n_player++;
				firstrun = 0;
			}
			if((cards[n-2]%13) > (cards[n-1]%13)){
				add_war_victory(player_one, cards, player_one_cards, n);
				player_one_cards+=n;
			} else if((cards[n-2]%13) < (cards[n-1]%13)) {
				add_war_victory(player_two, cards, player_two_cards, n);
				player_two_cards+=n;
			}
		}
	}
	if(player_one_cards==CARDCOUNT){
		printf("Player one wins the war!\n");
			return count;
		} else {
			printf("Player one wins the war!\n");
			return count;
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

