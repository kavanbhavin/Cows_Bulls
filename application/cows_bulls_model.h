#ifndef COWS_BULLS_MODEL_H_
#define COWS_BULLS_MODEL_H_
/* Struct to represent result*/
typedef struct result{
	int correct_digits;
	int digits_in_wrong_places;
	/* Bool that represents if the player has won or not*/
	int win;
} result_t;

/* Returns the a result based on a guess */
result_t evaluate_guess(char guess[4]);

/* Represents a player's code*/
char our_code[4];

void set_code(char c[4]){
	int i;
	for(i=0; i<4; i++){
		our_code[i] = c[i];
	}
}

#endif /*COWS_BULLS_MODEL_H_*/
