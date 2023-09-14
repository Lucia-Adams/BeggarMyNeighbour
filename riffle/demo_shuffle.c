#include "riffle.h"

int main(){
	/* Prints out the result of a riffle shuffle on arrays of integers and greek letters*/
	/* seed random once at beginning for use by riffle functions */
	srand(time(0));
        int num[] = {1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20};
        int len_n = sizeof(num)/sizeof(num[0]);

	char *greek[] = {"alpha", "beta", "gamma", "delta", "epsilon", "zeta", "eta", "theta", "iota", "kappa", "lambda", "mu"};
        int len_g = sizeof(greek)/sizeof(greek[0]);
	
	int i, valid;
	float av_quality;

	/*shuffle numbers */
	printf("Before (numbers): \n");
        for (i=0; i< len_n; i++){printf("%d ", num[i]);}
        printf("\nAfter (numbers): \n");

        riffle(num, len_n  ,sizeof(num[0]), 1);
	for (i=0; i< len_n; i++){printf("%d ", num[i]);}
	printf("\n");

	/*shuffle greek letters */
	printf("\nBefore (greek): \n");
        for (i=0; i< len_g; i++){printf("%s ", greek[i]);}
        printf("\nAfter (greek): \n");

        riffle(greek, len_g  ,sizeof(greek[0]), 1);
        for (i=0; i< len_g; i++){printf("%s ", greek[i]);}
        printf("\n");
	
	/* Return the validity of the shuffles */
	valid = check_shuffle(num, len_n  ,sizeof(num[0]), cmp_int);
	printf("\nCheck shuffle (integers) returns %d\n", valid);
	valid = check_shuffle(greek, len_g  ,sizeof(greek[0]), cmp_str);
        printf("Check shuffle (greek) returns %d\n", valid);

}

