#include "beggar.h"
#include "shuffle.h"

/* Plays a single game
 *
 * Params:
 * 	int number of players 
 */
int main(int argc, char **argv){

        int i,j;
        int pack[52];
        int seed = -1; /* to seed with time */

	if (argc ==2 && atoi(argv[1])){
        	/* generate pack of cards */
        	for (i=0; i<=39; i+=13){
                	for (j=0; j<=12; j++){pack[i+j] = j+2;}
        	}	
		/*Shuffles cards */
        	shuffle(pack, 52, seed);
        	beggar(atoi(argv[1]), pack, 1);

	}else{
		printf("Expects one argument : number of players\n");
	}
}

