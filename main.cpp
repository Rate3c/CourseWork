#include "String.h"
#include "Calculator.h"

using namespace std;

int main() {
	int action = 1;
	String expression;
	while (action == 1)
	{
		try {
			Postfix_notation_and_Calculation(expression);
		}
		catch (const invalid_argument error) {
			cout << " Invalid sybmol entered";
		}

		cout << "What would you like to do next?"
			<< endl << "1. continue\n2. exit" << endl;
		cin >> action;
	}

	cout << "\n Exiting programm..." << endl;
	return 0;
}