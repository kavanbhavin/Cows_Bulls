#ifndef COWS_BULLS_MODEL_H_
#define COWS_BULLS_MODEL_H_
/* Struct to represent result*/
typedef struct result{
	int correct_digits;
	int digits_in_wrong_places;
	/* Bool that represents if the player has won or not*/
	int win;
} result_t;

/* Returns the number a result based on a guess */
result_t evaluate_guess(char guess[4]);

/* Represents a player's code*/
int code;

void set_code(int c){
	code = c;
}
#endif /*COWS_BULLS_MODEL_H_*/
