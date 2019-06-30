#include <iostream>
#include "Calculator.h";

using namespace std;

string getUserInput()
{
	cout << ">>>";
	string userInput;
	cin >> userInput;
	return userInput;
}

void main(int argc, char** argv)
{
	string rawInput;
	if (argc > 1)
	{
		for(int i = 1; i < argc; ++i)
			rawInput += argv[i];
	}
	else
	{
		rawInput = getUserInput();
	}
	Calculator calc;
	calc.handleRawString(rawInput);
}