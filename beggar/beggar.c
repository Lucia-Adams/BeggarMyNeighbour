#include "beggar.h"

/* Plays a single game of beggar your neighbour 
 *
 * Params:
 * 	int Nplayers - number of players
 * 	int *deck - shuffled deck of standard cards 
 * 	int talkative - if non zero will narrate game
 * Returns:
 * 	int turn - number of turns to finish the game
 */
int beggar(int Nplayers, int *deck, int talkative){

	int i;
	int player;
	QUEUE *hands[Nplayers];
	for (i=0; i<Nplayers; i++){hands[i]=NULL;}
	QUEUE *centre = NULL;
	
	for (i=0; i<52; i++){
		/* deals the cards */
		player = i % Nplayers;
		/* note we cant use a local variable for hands[player] as the address of that is not the address */
		/* of hands[player] despite holding same value*/
		/* note hands+player is same as &(hands[player]) */
		enqueue(deck[i], (hands+player));
	} 	
	
	if (talkative){
		printf("Starting decks: \n");
		for (i=0; i<Nplayers; i++){printf("%d: ",i); print_queue(hands[i]);}
	}

	QUEUE *reward = NULL;

	int turn=1;
	int p_player = Nplayers -1;
	int c_player = 0;
	int end = 0;

	while (!end){ 
		
		if (talkative){	printf("\nTurn %d  |  player %d turn: \n", turn, c_player);}
		reward = take_turn(hands+c_player, &centre);

		if (reward!=NULL && talkative){printf("Player %d picks up centre\n", p_player);}
		pick_up_pile(hands+p_player, &reward);

		if (talkative){
			printf("Centre : ");
			print_queue(centre);
			for (i=0; i<Nplayers; i++){printf("%d: ",i); print_queue(hands[i]);}
		}	

		/* find whos turn it is next */
		if (hands[c_player] != NULL){
			/* current player didnt go to null so is new prev player - otherwsie would keep prev player the same */
			p_player = c_player; 
		}
		c_player = (c_player+1) % Nplayers;
		while (hands[c_player] == NULL){
			/*next player has no cards so skip their go */
			c_player = (c_player+1) % Nplayers;
		}	

		end = finished(hands, Nplayers);
		turn++;
	
	}

	if (talkative){printf("\n---- Player %d won ---- \n", (c_player+1));}

	/* empty at end */
	empty_queue(&centre);
	empty_queue(&reward);
	for (i=0; i<Nplayers; i++){empty_queue(hands+i);}

	return turn--;

}

/* Picks up one queue and gives to the other
 *
 * Params:
 * 	QUEUE **hand - address of hand to add to
 * 	QUEUE **centre - address of queue to pick up
 * Returns:
 * 	int 0
 */
int pick_up_pile(QUEUE **hand, QUEUE **centre){
	int val;
	val = dequeue(centre);

	while (val != 0){
		enqueue(val, hand);
		val = dequeue(centre);
	}
	return 0;
}

/* Takes a single turn - updates players cards and returns reward
 *
 * Params:
 * 	QUEUE **player - player queue whose turn it is
 * 	QUEUE **centre - centre queue
 * Returns:
 * 	QUEUE *reward - queue of reward cards to be picked up by previous player
 *
 */
QUEUE *take_turn(QUEUE **player, QUEUE **centre){

	QUEUE *reward = NULL;
	/* if top card not penalty player lays one card */
	int top = get_top_card(*centre);
	int card;
	int i;

	if (!(top ==11 || top == 12 || top == 13 || top ==14)){
		/* player lays one card  -  should never be empty */
		card = dequeue(player);
		enqueue(card, centre);
		return reward;

	} else{
		for (i=0; i< (top-10); i++){
			card = dequeue(player);

			/*check if player out of cards*/
			if (card ==0){break;}
                	enqueue(card, centre);

			if (card == 11 || card == 12 || card == 13 || card == 14){
				/* returns nothing as didnt make it through turn wihout playing penalty */
				return reward;	
			}
		}

		/* made it through without playing penalty card */
		pick_up_pile(&reward, centre);
		return reward;
	}
}

/* Finds top card of a pile
 * 
 * Params:
 * 	QUEUE *pile - queue of cards to get top of
 * Returns:
 * 	int value - value of card at top of pile
 *
 */
int get_top_card(QUEUE *pile){

	if (pile ==NULL){
                return 0;
        }

        QUEUE *current = pile;
        while (current->nextNode != NULL){
                current = current->nextNode;
        }
        /* now currents nextNode is NULL so thats the end of the queue*/
        return current->value;

}

/* Finds if a player has all the cards (ie other players have none)
 *
 * Params:
 * 	QUEUE **players - array of players hands (queues)
 * 	int Nplayers - number of players
 * Returns:
 * 	true (non-zero) if other players have no cards
 *
 */
int finished(QUEUE **players, int Nplayers){

	int i=0;
	int finish = 0;
	int n_finished = 0;
	for (i=0; i<Nplayers; i++){
		/* goes through players and adds up number that has finished */
		if ( *(players+i) == NULL){
			n_finished++;
		}
	}

	/* if eveyone but one has finished set finish to true */
	if (n_finished == (Nplayers-1)){
		finish = 1;
	}
	return finish;
}
