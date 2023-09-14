#include "riffle.h"

/* Performs riffle shuffle on array L with len elements each of size bytes
 * Takes in a workspace array (to optimise multiple calls of riffle_once)
 *
 * Params:
 * 	void *L - array to shuffle
 * 	int len - length of array
 * 	int size - size of elements in bytes
 * 	void *work - array to use as workspace
 * Returns:
 * 	void
 */
void riffle_once(void *L, int len, int size, void *work){
	
	int r_num;
	int half = len /2;

	/* have cursors to where we are in pack a and b and workspace */
	void *cur_a = L;
        /* pointer arithmetic not allowed on void as adds bytes depending on type */
        /* cast pointer to char (= 1 byte) so we can add on size and dont need cast back as void accepts anything */
	/* pointer to halfway along array */
	void *cur_b = ((char *) cur_a) + (size*half);
	void *cur_w = work;
	
	int a_index = 0, b_index = 0;
	
	while (a_index<half || b_index < (len-half)){
		/* we seed rand outside of this function - get 1 or 0 to choose which half to pick from*/
		r_num = rand() % 2;
		
		/* ie if (r_num not 0 and got things in a) or gone through pack b*/
		if ((r_num && a_index <half) || b_index == (len-half)){
			/* pick from pack a */
			/*copy value at cursor of a to working list and increment cursors */
		        /*memcpy takes void pointers dest, source, num bytes */
                	memcpy(cur_w, cur_a, size);
			cur_a = ((char *) cur_a) + size;
			cur_w = ((char *) cur_w) + size;

			a_index++;

		} else {
			/*pick from pack b */
			memcpy(cur_w, cur_b, size);
                        cur_b = ((char *) cur_b) + size;
                        cur_w = ((char *) cur_w) + size;
			
			b_index++;
		}
	}

	/* copy all of workspace back over to list */
	memcpy(L, work, (len*size));

}

/* Performs N successive riffle shuffles on array L 
 *
 * Params:
 * 	void *L - array to shuffle
 * 	int len - length of array
 * 	int size - size of elements in bytes
 * 	int N - number of times to perfom riffle shuffle
 * Returns:
 *      void
 *
 */
void riffle(void *L, int len, int size, int N){
	/*malloc workspace array of same size as L */
	void *workspace = malloc(len*size);

	int i;
	for (i=0; i<N; i++){
		riffle_once(L, len, size, workspace);
	}

	free(workspace);

}

/* Checks shuffle by ensuring everything in suffled array is in orginal and vice versa
 * Returns 1 if it does and 0 if it does not
 *
 * Params:
 * 	void *L - array to shuffle
 * 	int len - length of array
 * 	int size - size of elements in bytes
 *	int (*cmp)(void *, void *) - function to compare elements (returns 0 if equal)
 * Returns:
 * 	int - 1 if valid shuffle and 0 if not 
 *
 */
int check_shuffle(void *L, int len, int size, int (*cmp)(void *, void *)){

	int i, j, valid1, valid2;
	void *result = malloc(len*size);
	/* as riffle changes original array get copy so have original and new*/
	memcpy(result, L, (size*len));
	riffle(result, len, size, 1);

	/* check everything in original is in shuffled list  */
	valid1 = check_existence(L, result, len, size, cmp);
	/* check everything in shuffled list is in original*/
	valid2 = check_existence(result,L, len, size, cmp);
	free(result);

	return (valid1&&valid2);
	
}

/* Compares two integers 
 * return -1, 0 or +1 if the first argument is greater than, equal to, or less than the second argument respectively
 *
 * Params:
 * 	void *p1 - pointer to first integer
 * 	void *p1 - pointer to second integer
 * Returns:
 * 	int - result of comparison as above
 *
 */
int cmp_int(void *p1, void *p2){
	/* -1, 0 or +1 if greater, equal or less than respectively*/
	int num1 = *((int *) p1);
	int num2 = *((int *) p2);

	if (num1 == num2){ 
		return 0;
	} else if (num1 > num2){
		return -1;
	} else {
		return 1;
	} 
}

/* Compares two strings
 * return -1, 0 or +1 if the first argument is greater than, equal to, or less than the second argument respectively
 *
 * Params:
 * 	void *p1 - pointer to first string
 * 	void *p2 - pointer to second string
 * Returns:
 * 	int - result of comparison as above
 *
 */
int cmp_str(void *p1, void *p2){
	/* cast to pointer to string and then get the string start*/
        char *str1 = *((char **) p1);
        char *str2 = *((char **) p2);
	/* strcmp takes char pointer*/
	/* returns >0 if str1 has bigger ascii (later in alphabet) */
        int comp =  strcmp(str1, str2);
	if (comp == 0){
                return 0;
        } else if (comp > 0){
                return -1;
        } else if (comp < 0){
                return 1;
        }
}

/* Checks all elements in array a are in b (not vice versa one way)
 *
 * Params:
 * 	void *arr_a - array a
 * 	void *arr_b - array b
 *	int len - length of array
 *	int size - size of elements in bytes
 *	int (*cmp)(void *, void *) - function to compare elements (returns 0 if equal) 
 * Returns:
 * 	int - 1 if valid and 0 if not valid
 *
 */
int check_existence(void *arr_a, void *arr_b, int len, int size, int (*cmp)(void *, void *)){

	int i, j, valid;
	void *cur_a = arr_a;
	void *cur_b = arr_b;

	for (i=0; i<len; i++){
                valid = 1;
                /* reset where we are in a to loop through it again */
                cur_b = arr_b;

                /* goes through and checks valid set to 0 ie one matches*/
                for (j=0; j<len; j++){
                        valid = cmp(cur_a, cur_b);
                        if (valid == 0){break;}
                        cur_b = ((char *) cur_b) + size;
                }

                /* if valid wasnt set to 0 and exits as 1 then not found pair */
                if (valid !=0){printf("Element index %d in a not found in b",i); return 0;}
                /*go through original list */
                cur_a = ((char *) cur_a) + size;
        }
	return 1;
}

/* Takes array of integers and returns its quality
 * Based on number of number of entries still in order within the array
 *
 * Params:
 * 	int *numbers - array to check
 * 	int len - length of array
 * Returns:
 * 	float - calculated quality
 *
 */
float quality(int *numbers, int len){

	int i, cmp;
	float total= 0.0;

	/*loops through array and adds comparison between consecutive entries to total */
	for (i=0; i<len-1; i++){
		cmp = cmp_int((numbers+i),(numbers+i+1));
		if (cmp ==1){total++;}
	}	

	/* average is the total divided by number of comparisons */
	return total/(len-1);

}

/* Calculates average quality of riffle shuffle over trials 
 *
 * Params:
 * 	int N - array length
 * 	int shuffles - number of riffle shuffles to perform
 * 	int trials - trials to base average over
 * Returns:
 * 	float - average quality
 *
 */
float average_quality(int N, int shuffles, int trials){

	int i,j;
	int arr[N];
	float average = 0.0;

	/* generate array */
	for (i=0; i<N; i++){ arr[i] = i;}

	for (j=0; j<trials; j++){
	
		/* reset the array */
		for (i=0; i<N; i++){ arr[i] = i;}

		riffle(arr, N, sizeof(int), shuffles);
		average += quality(arr,N);

	}
	average /= trials;
	return average;
}
