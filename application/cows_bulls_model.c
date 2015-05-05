#include "cows_bulls_model.h"

result_t evaluate_guess(char guess[4]){
	int ours, theirs;
	result_t result;
	result.correct_digits = 0;
	result.digits_in_wrong_places = 0;
	result.win =0;
	for(theirs=0; theirs<4; theirs++){
		for(ours=0; ours<4; ours++){
			if(guess[theirs] == our_code[ours]){
				if(ours==theirs) result.correct_digits++;
				else result.digits_in_wrong_places++;
			}
		}
	}
	if(result.correct_digits == 4) result.win = 1;
	return result;
}
