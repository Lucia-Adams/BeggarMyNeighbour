#include "beggar.h"
#include "shuffle.h"

/* define structure to store game results */
struct game{
	int shortest;
	int longest;
	int average;
};

typedef struct game GAME;

GAME statistics(int Nplayers, int games);

/* Params:
 * 	int - max number of players (default 10)
 * 	int - number of trials (default 250)
 *
 * Must supply with both params else uses default values
 */
int main(int argc, char **argv){

	GAME stats;
	int max_player, trials;
	int i=0;

	/* gets command line args */
	if (argc ==3 && atoi(argv[1]) && atoi(argv[2])){
		max_player = atoi(argv[1]);
		trials = atoi(argv[2]); 
	}else{
		max_player=10;
		trials = 250;
	}

	/*Calculates statistics for given arguments */
	printf("Players |  shortest , longest , average (over %d trials)\n", trials);
	for (i=2; i <=max_player; i++){
		stats = statistics(i, trials);		
		printf("%d | %d , %d, %d\n", i, stats.shortest, stats.longest, stats.average);
	}


}

/* Find the shortest, average and longest of games games with Nplayers
 *
 * Params:
 * 	int Nplayers - number of players
 * 	int games - number of games to trial over
 * Returns:
 * 	GAME results - GAME struct of statistics
 */
GAME statistics(int Nplayers, int games){
	
	int g,i,j;
	int shortest=0, longest=0, turns=0, total=0;

	GAME results;

	int pack[52];
	int seed = -1; 

	/* generate pack of cards */
	for (i=0; i<=39; i+=13){
        	for (j=0; j<=12; j++){pack[i+j] = j+2;}
        }
        shuffle(pack, 52, seed);

	for (g=0; g<games; g++){
		/*Play game of beggar your neighbour and shuffles deck for next game */
		turns = beggar(Nplayers, pack, 0);
		shuffle(pack, 52, seed);

		/* tracks shortest and longest games */
		total += turns;
		if (!shortest || turns < shortest){ shortest = turns;}
		if (!longest || turns > longest){ longest = turns;}
	}

	results.shortest = shortest;
	results.longest = longest;
	results.average = total/games;

	return results;

}
