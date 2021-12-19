#pragma once
#include "String.h"

using namespace std;

//Operation on one element
double Operand_for_one_elem(char operand, double numb_1) {

	double result = 0, exp = 2.7183, pi = 3.1416;
	//Unary minus
	if (operand == 126) { result = -1 * numb_1; }
	//Root of number
	if (operand == 1) { result = pow(numb_1, 0.5); }
	//Sin
	if (operand == 2) { result = sin(numb_1 * pi / 180); }
	//Cos
	if (operand == 3) { result = cos(numb_1 * pi / 180); }
	//Logarithm base 2
	if (operand == 4) { result = log2(numb_1); }
	//e^(arg)
	if (operand == 5) { result = pow(exp, numb_1); }
	//Ctg
	if (operand == 6) { result = (cos(numb_1 * pi / 180) / sin(numb_1 * pi / 180)); }
	//Tg
	if (operand == 7) { result = (sin(numb_1 * pi / 180) / cos(numb_1 * pi / 180)); }
	////Logarithm base e
	if (operand == 8) { result = log(numb_1);; }
	return result;
}

//Operation on two elements
double Operand_for_two_elem(char operand, double numb_1, double numb_2) {

	double result = 0;
	//Summation
	if (operand == 43) { result = numb_1 + numb_2; }
	//Difference
	if (operand == 44) { result = numb_1 - numb_2; }
	//Multiplication
	if (operand == 46) { result = numb_1 * numb_2; }
	//Division
	if (operand == 47) { result = numb_1 / numb_2; }
	//Expanding a number
	if (operand == 94) { result = pow(numb_1, numb_2); }
	return result;
}

//Counting and Converting an Expression
void Culculate(char operand, String& stack_for_num) {

	char space = ' ';

	while (stack_for_num.last_simv(stack_for_num) == space)
		stack_for_num.pop_last_simv();

	char* number_first = new char[50];
	char* number_second = new char[50];
	char* result = new char[50];
	int kol_simv_one = 0, kol_simv_two = 0, kol_simv_res = 0;
	double first_num = 0, second_num = 0;
	result[0] = '\0';
	number_second[0] = '\0';
	number_first[0] = '\0';

	//The operand interacts with two numbers
	if (((operand >= 42) && (operand <= 47)) || operand == 94) {

		//Allocating numbers to char arrays
		while (stack_for_num.last_simv(stack_for_num) != space) {
			number_second[kol_simv_two] = stack_for_num.last_simv(stack_for_num);
			number_second[kol_simv_two + 1] = '\0';
			kol_simv_two++;
			stack_for_num.pop_last_simv();
		}

		for (int i = 0; i < kol_simv_two / 2; i++) {
			char temp = number_second[i];
			number_second[i] = number_second[kol_simv_two - 1 - i];
			number_second[kol_simv_two - 1 - i] = temp;
		}
		stack_for_num.pop_last_simv();

		while (stack_for_num.last_simv(stack_for_num) != space) {

			if (stack_for_num.function_length() == 0)
				break;
			number_first[kol_simv_one] = stack_for_num.last_simv(stack_for_num);
			number_first[kol_simv_one + 1] = '\0';
			kol_simv_one++;
			stack_for_num.pop_last_simv();
		}

		for (int i = 0; i < kol_simv_one / 2; i++) {
			char temp = number_first[i];
			number_first[i] = number_first[kol_simv_one - 1 - i];
			number_first[kol_simv_one - 1 - i] = temp;
		}

		//Converting numbers to double
		second_num = atof(number_second);
		first_num = atof(number_first);
		//Performing an operation on them and writing them on the stack
		double temp = Operand_for_two_elem(operand, first_num, second_num);
		sprintf(result, "%f", temp);
	}

	//The operand interacts with one number
	if ((operand == 126) || (operand == 1) || (operand == 2) || (operand == 3) || (operand == 4) || (operand == 5) || (operand == 6) || (operand == 7) || (operand == 8)) {

		while (stack_for_num.last_simv(stack_for_num) != space) {
			if (stack_for_num.function_length() == 0)
				break;
			number_first[kol_simv_one] = stack_for_num.last_simv(stack_for_num);
			number_first[kol_simv_one + 1] = '\0';
			kol_simv_one++;
			stack_for_num.pop_last_simv();
		}
		for (int i = 0; i < kol_simv_one / 2; i++) {
			char temp = number_first[i];
			number_first[i] = number_first[kol_simv_one - 1 - i];
			number_first[kol_simv_one - 1 - i] = temp;
		}
		first_num = atof(number_first);
		double temp = Operand_for_one_elem(operand, first_num);
		sprintf(result, "%f", temp);
	}

	while (!(result[kol_simv_res] == '.')) {
		stack_for_num = stack_for_num + result[kol_simv_res];
		kol_simv_res++;
	}

	if ((result[kol_simv_res + 1] != '0') || (result[kol_simv_res + 2] != '0') || (result[kol_simv_res + 3] != '0') || (result[kol_simv_res + 4] != '0')) {
		while (!(result[kol_simv_res + 2] == '\0')) {
			stack_for_num = stack_for_num + result[kol_simv_res];
			kol_simv_res++;
		}
	}
	if (stack_for_num.last_simv(stack_for_num) != space)
		stack_for_num = stack_for_num + space;

	//Releasing the memory
	delete[] number_first;
	delete[] number_second;
	delete[] result;
}

//String translation to postfix notation
void Postfix_notation_and_Calculation(String& str) {

	//Creating a dynamic char array
	char* simv = new char[String::limit];
	int kol_simv = 0;
	cout << "Enter an expression: ";
	cin >> simv; cout << endl;

	while (simv[kol_simv] != '\0') {
		kol_simv++;
	}
	kol_simv++;

	char simv_last = '\0';
	String stack, stack_for_num;	//"stack" for operands
	char result = 0;
	String pi, e;
	pi = "3.1416"; e = "2.7183";
	char dot = '.', virgule = ',', multiplication = '*', minus = '-', space = ' ', exclamation = '!', s = 's', c = 'c', l = 'l', exp = 'e', t = 't';
	char q = 'q';
	bool check = true, correct = false;
	for (int i = 0; i < kol_simv; i++) {
		if (correct == false) {
			correct = true;

			//If the symbol is a number
			if ((simv[i] >= 48) && (simv[i] <= 57) || (simv_last == exclamation)) {
				if (((simv_last >= 48) && (simv_last <= 57)) || (simv_last == exclamation)) {
					str = str + simv[i];
					stack_for_num = stack_for_num + simv[i];
				}
				else {
					if (check == true)
						check = false;
					else str = str + space;
					str = str + simv[i];
					stack_for_num = stack_for_num + simv[i];
				}
				correct = false;
			}

			else {
				if ((simv[i] == '.') && ((simv[i + 1] >= 48) && (simv[i + 1] <= 57)) && ((simv_last >= 48) && (simv_last <= 57))) {
					stack_for_num = stack_for_num + simv[i];
					correct = false;
				}
				else {
					if (!((simv[i] == '(') || (simv[i] == ')') || (simv[i] == 'p') || (stack_for_num.last_simv(stack_for_num) == space) || (simv[i] == 'e') || (simv[i] == 's') || (simv[i] == 'c') || (simv[i] == 'l') || (simv[i] == 't'))) {
						stack_for_num = stack_for_num + space;
					}
					if ((simv_last == '\0') && (simv[i] == '-'))
						stack_for_num.pop_last_simv();

				}
			}

			//Condition for writing double
			if ((simv[i] == '.') && ((simv[i + 1] >= 48) && (simv[i + 1] <= 57)) && ((simv_last >= 48) && (simv_last <= 57))) {
				simv[i] = '!';
				str = str + simv[i];
				correct = false;
			}

			if ((simv[i] == 'p') && (simv[i + 1] == 'i') && (simv[i + 1] != '\0')) {
				if (check == true)
					check = false;
				else str = str + space; // Otherwise, add a space and add a character to the main line
				str = str + simv[i] + simv[i + 1];
				stack_for_num = stack_for_num + pi;
				i++;
				correct = false;
			}

			if ((simv[i] == 'e') && (simv[i + 1] != 'x')) {
				if (check == true)
					check = false;
				else str = str + space;
				str = str + simv[i];
				stack_for_num = stack_for_num + e;
				correct = false;
			}

			//functions sin,cos,tg,ctg,ln,log,sqrt,e^x
			if (((simv[i] == 's') && (simv[i + 1] == 'q') && (simv[i + 2] == 'r') && (simv[i + 3] == 't') && (simv[i + 3] != '\0'))) {
				char temp = 1;
				stack = stack + simv[i + 3] + simv[i + 2] + simv[i + 1] + temp;
				i = i + 3;
				correct = false;
			}

			if (((simv[i] == 's') && (simv[i + 1] == 'i') && (simv[i + 2] == 'n') && (simv[i + 2] != '\0'))) {
				char temp = 2;
				stack = stack + simv[i + 2] + simv[i + 1] + temp;
				i = i + 2;
				correct = false;
			}

			if (((simv[i] == 'c') && (simv[i + 1] == 'o') && (simv[i + 2] == 's') && (simv[i + 2] != '\0'))) {
				char temp = 3;
				stack = stack + simv[i + 2] + simv[i + 1] + temp;
				i = i + 2;
				correct = false;
			}

			if (((simv[i] == 'l') && (simv[i + 1] == 'o') && (simv[i + 2] == 'g') && (simv[i + 2] != '\0'))) {
				char temp = 4;
				stack = stack + simv[i + 2] + simv[i + 1] + temp;
				i = i + 2;
				correct = false;
			}

			if (((simv[i] == 'e') && (simv[i + 1] == 'x') && (simv[i + 2] == 'p') && (simv[i + 2] != '\0'))) {
				char temp = 5;
				stack = stack + simv[i + 2] + simv[i + 1] + temp;
				i = i + 2;
				correct = false;
			}

			if ((simv[i] == 'c') && (simv[i + 1] == 't') && (simv[i + 2] == 'g') && (simv[i + 2] != '\0')) {
				char temp = 6;
				stack = stack + simv[i + 2] + simv[i + 1] + temp;
				i = i + 2;
				correct = false;
			}

			if (((simv[i] == 't') && (simv[i + 1] == 'g') && (simv[i + 1] != '\0') && (simv[i - 1] != 'c'))) {
				char temp = 7;
				stack = stack + simv[i + 1] + temp;
				i++;
				correct = false;
			}

			if (((simv[i] == 'l') && (simv[i + 1] == 'n') && (simv[i + 1] != '\0'))) {
				char temp = 8;
				stack = stack + simv[i + 1] + temp;
				i++;
				correct = false;
			}

			if (((((simv[i] >= 42) && (simv[i] <= 47)) || (simv[i] == 94)) && ((((simv_last < 42) || (simv_last > 47))) && (simv_last != 94))) || ((simv[i] == '-') && (((((simv_last >= 42) && (simv_last <= 47)) || (simv_last == 94)) || (simv_last == '\0'))))) {
				if (simv[i] == '*') {
					simv[i] = '.';
				}
				if ((simv[i] == '-') && (((((simv_last >= 42) && (simv_last <= 47)) || (simv_last == 94)) || (simv_last == '\0')))) {
					simv[i] = '~';
				}
				if (simv[i] == '-') {
					simv[i] = ',';
				}
				if (stack.empty() == false) {
					stack = stack + simv[i];
				}

				else {
					//If the top element of the stack has a higher priority 
					if ((stack.last_simv(stack) >= simv[i]) || (stack.last_simv(stack) == simv[i] - 1) || (stack.last_simv(stack) == simv[i] + 1)) {
						while ((stack.last_simv(stack) >= simv[i]) || (stack.last_simv(stack) == simv[i] - 1) || (stack.last_simv(stack) == simv[i] + 1)) {
							Culculate(stack.last_simv(stack), stack_for_num);
							str = str + space;
							str = str + stack.last_simv(stack);
							stack.pop_last_simv();
						}
						stack = stack + simv[i];
					}
					else {
						stack = stack + simv[i];
					}
				}
				correct = false;
			}

			if (simv[i] == '(') {
				stack = stack + simv[i];
				correct = false;
			}

			if (simv[i] == ')') {
				if (((stack.last_simv(stack) >= 97) && (stack.last_simv(stack) <= 122)) || ((stack.last_simv(stack) >= 1) && (stack.last_simv(stack) <= 8))) {
					str = str + space;
					stack_for_num = stack_for_num + space;
					//Count
					Culculate(stack.last_simv(stack), stack_for_num);
					while (stack.last_simv(stack) != '(') {
						str = str + stack.last_simv(stack);
						stack.pop_last_simv();
					}
				}
				else {
					while (stack.last_simv(stack) != '(') {
						str = str + space;
						str = str + stack.last_simv(stack);
						//Count
						Culculate(stack.last_simv(stack), stack_for_num);
						stack.pop_last_simv();
					}
				}
				stack.pop_last_simv();
				correct = false;
			}
			if (simv[i] == '\0')
				correct = false;
			simv_last = simv[i];
		}
		else {
			cout << "Position " << i - 1;
			break;
		}
	}

	if (correct == true) {
		throw invalid_argument(" Invalid character entered");
	}

	else {

		//If there is anything left on the stack
		while (stack.empty() != false) {
			str = str + space;
			str = str + stack.last_simv(stack);
			Culculate(stack.last_simv(stack), stack_for_num);
			stack.pop_last_simv();
		}

		//Convert Ending String
		for (int i = 0; i < str.function_length(); i++) {
			
			if (str[i] == dot) str[i] = multiplication;
			if (str[i] == virgule) str[i] = minus;
			if (str[i] == exclamation) str[i] = dot;
			switch (str[i])
			{
			case 1: str[i] = s; break;
			case 2: str[i] = s; break;
			case 3: str[i] = c; break;
			case 4: str[i] = l; break;
			case 5: str[i] = exp; break;
			case 6: str[i] = c; break;
			case 7: str[i] = t; break;
			case 8: str[i] = l; break;
			default: break;
			}
		}
		cout << "The result of the expression: " << stack_for_num << endl;
		cout << "Expression in postfix form: " << str << endl << endl;
	}
}
