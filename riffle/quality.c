#include "riffle.h"
#define N_TRIALS 30

int main(){
	/* Outputs average quality of a riffle shuffle of an array of length 50 - trials up to 15 shuffles*/

	int i;
	float quality=0.0;
	/* seed once in program for use by riffle functions */
	srand(time(0));

	printf("The average quality of shuffles:\nNumber of shuffles (over %d trials) | average quality \n", N_TRIALS);
	for (i=1; i<16; i++){	
		quality = average_quality(50, i, N_TRIALS); 
		printf("%d | %f\n", i, quality);
	}
	printf("\n");
}
