#include "cows_bulls_model.h"

char our_code[4];

result_t evaluate_guess(char guess[4]){
	int opp_idx, own_idx, idx;
	char temp_code[4];
	char temp_guess[4];
	result_t result;
	for(idx=0; idx<4; idx++){
		temp_guess[i] = guess[i];
	}
	result.correct_digits = 0;
	result.digits_in_wrong_places = 0;
	result.win = 0;
	for(idx=0; idx<4; idx++){
		temp_code[idx] = our_code[idx];
	}

	for(opp_idx=0; opp_idx<4; opp_idx++){
		if(temp_guess[opp_idx] == temp_code[opp_idx]){
			result.correct_digits++;
			temp_guess[opp_idx] = 1;
			temp_code[opp_idx] = 2;
		} 
	}
	for(opp_idx=0; opp_idx<4; opp_idx++){
		for(own_idx=0; own_idx<4; own_idx++){
			if(temp_guess[opp_idx] == temp_code[own_idx]){
				result.digits_in_wrong_places++;
				temp_guess[opp_idx] = 1;			
				temp_code[own_idx] = 2;
			}
		}
	}
	if(result.correct_digits == 4) result.win = 1;
	return result;
}

void set_code(char c[4]){
	int i;
	for(i=0; i<4; i++){
		our_code[i] = c[i];
	}
}
