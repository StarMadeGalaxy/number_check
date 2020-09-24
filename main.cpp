#include <iostream>
#include <string>

using namespace std;

double input_check()
{
	/*	Convert entered string into double and check if its number in every possible console input way in c++
	*	gotta include <string> and <iostream> (not mandatory) for output incorrect-input message
	*	@return converted number
	*/
	string user_input;

	while (true)
	{
		bool mixed_negation = false;	// for example +-12 or -+12
		int digit_counter = 0;	// 0123456789
		int plus_counter = 0;	// (+) - for example:: 12e+23
		int dash_counter = 0;	// (-) - for negative number
		int dot_counter = 0;	// (.) - for floating point numbers 
		int e_counter = 0;		// (e) - for scientific input

		getline(cin, user_input);	// got the string

		// Must consider every case in string that could be a number.
		// In scientific input power could be with floating point
		// so we'll consider this case with dash_counter <= 2
		// for instance: -1.2e-14, -1.2e+14 or -1.2e14
		
		// we gotta check cases like + -12 or -+12 are what should be - 12 cause + 12 * -12 = -12
		if (user_input.length() >= 2) {
			if (((user_input[0] == '-') && (user_input[1] == '+')) || ((user_input[1] == '-') && (user_input[0] == '+'))) {
				mixed_negation = true;
			}
		}

		for (int i = 0; user_input[i] != '\n'; i++) {	
			// first element could be +, for example +12 
/*1*/		if (user_input[i] == '+' && plus_counter == 0 && digit_counter == 0 && dot_counter == 0 && e_counter == 0 && dash_counter < 2 && i < 2) {		
				//cout << "TEST 1" << endl;
				plus_counter++;
			// negative number
/*2*/       } else if (user_input[i] == '-' && plus_counter < 2 && digit_counter == 0 && dot_counter == 0 && e_counter == 0 && dash_counter == 0 && i < 2) {
				//cout << "TEST 2" << endl;
				dash_counter++;
/*3*/		} else if (user_input[i] >= '0' && user_input[i] <= '9') {
				//cout << "TEST 3" << endl;
				digit_counter++;
			}
			// -123.3e+123
/*4*/		else if (user_input[i] == '.' && digit_counter > 0 && e_counter == 0 && dot_counter < 2 && plus_counter < 2 && dash_counter < 2) {
				//cout << "TEST 4" << endl;
				dot_counter++;
			}
			// the second - could only be after e
/*5*/		else if (user_input[i] == '-' && e_counter == 1 && plus_counter < 2 && digit_counter > 0 && dot_counter < 2 && dash_counter < 2) {
				//cout << "TEST 5" << endl;
				dash_counter++;
			}
			// +12e+12 - second plus could only be after e
/*6*/		else if (user_input[i] == '+' && plus_counter < 2 && e_counter == 1 && dot_counter < 2 && dash_counter < 2 && digit_counter > 0) {
				//cout << "TEST 6" << endl;
				plus_counter++;
/*7*/		} else if (user_input[i] == 'e' && e_counter < 1 && digit_counter > 0 && plus_counter < 2 && dash_counter < 2 && dot_counter < 2) {
	            //cout << "TEST 7" << endl;
				e_counter++;
/*8*/		} else {
				//cout << "TEST 8" << endl;
				user_input.clear();
				cout << "Incorrect input! Try again." << endl;
				break;
			}

			int overall = digit_counter + plus_counter + e_counter + dot_counter + dash_counter;
			int len_str = user_input.length();

			// cout << "Check is completed. TEST" << endl;
			// cout << "Length is: " << user_input.length() << endl;
			// cout << "Overall is: " << overall << endl;
			// cout << "Last element: " << user_input[len_str - 1] << endl;

			// check the last element
			if (overall == len_str) {
				if (((user_input[len_str - 1] >= '0' && user_input[len_str - 1] <= '9') || user_input[len_str - 1] == '.') && mixed_negation == false) {
					return stod(user_input);
				}
				// c++ can calculate +-12 as -12, but stod("-+12") cannot convert it to -12, so if we detect form as +-xxx... , 
				// we cut first two symbols and then multiply it by -1
				else if ((((user_input[len_str - 1] >= '0' && user_input[len_str - 1] <= '9') || user_input[len_str - 1] == '.') && mixed_negation == true)) {
					user_input.erase(0, 2);
					//cout << "mulpiply" << endl;
					return stod(user_input) * -1;
				}
			// consider case if the string length is equal 1 separately
			// case in return block we cannot go through if-statement with string length = 1
			} else if (user_input.length() == 1) {
				if (user_input[0] >= '0' && user_input[0] <= '9') {
					return stod(user_input);
				}
			}
		}
	}
}
