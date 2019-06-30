#include "Calculator.h"

Calculator::Calculator()
{
}

Calculator::~Calculator()
{
}

//страшный ужас
elemType Calculator::getElemType(const char& ch)
{
	if (ch >= 'a' && ch <= 'Z')
		return elemType::SYMBOL;
	else if (ch == '*' || ch == '+' || ch == '/' || ch == '-' || ch == '^')
		return elemType::OPERATION;
	else if ((ch >= '0' && ch <= '9') || ch == '.')
		return elemType::NUMBER;
	else
		return UNKNOWN;
}

string Calculator::getNextElement(unsigned int& pointer)
{
	int counter = 0;
	elemType elemType = getElemType(rawString[pointer]);
	while (pointer + counter < rawString.length() && elemType == getElemType(rawString[pointer + counter]))
	{
		counter++;
	}
	pointer += counter;
	return rawString.substr(pointer - counter, counter);
}

// priority of operation1 < operation2?
bool Calculator::higherPriority(string op1, string op2)
{
	if (op1 == "(")
		return true;
	return operations[op1][0] > operations[op2][0];
}

bool Calculator::isNumber(string elem)
{
	for (int i = 0; i < elem.length(); ++i)
	{
		if ((elem[i] < '0' || elem[i] > '9') && elem[i] != '.')
			return false;
	}
	return true;
}

int Calculator::handleRawString(const string &userRawInput)
{
	rawString = userRawInput;
	unsigned int i = 0;
	string elem = getNextElement(i);
	while (!elem.empty())
	{
		//if elem is operation
		if (operations.find(elem) != operations.end())
		{
			while (!operationsStack.empty() && !higherPriority(elem, operationsStack.top()))
			{
				auto* stackTop = &operationsStack.top();
				if (*stackTop != "(")
					output.push(*stackTop);
				operationsStack.pop();
			}
			if (elem != ")")
				operationsStack.push(elem);
		}
		else if(isNumber(elem))
		{
			output.push(elem);
		}
		else
		{
			cerr << "Error: unknown element " << elem << endl;
			return -1;
		}
		elem = getNextElement(i);
	}
	while (!operationsStack.empty())
	{
		output.push(operationsStack.top());
		operationsStack.pop();
	}
	vector<double> solution = *handleOutput();
	if (solution.size() != 1)
	{
		cerr << "Error: ALALALA!" << endl;
	}
	cout << "Result: " << solution[0] << endl;
}

//страшненький ужасик
int Calculator::applyOperation(vector<double>& solution, const string& operation)
{
	const int* numOfArgs = &operations[operation][1];
	if (solution.size() < *numOfArgs)
		return -1;
	double tmp = 0;
	if (operation == "*")
	{
		tmp = *(solution.end() - 2) * *(solution.end() - 1);
	}
	else if (operation == "/")
	{
		tmp = *(solution.end() - 2) / *(solution.end() - 1);
	}
	else if (operation == "+")
	{
		tmp = *(solution.end() - 2) + *(solution.end() - 1);
	}
	else if (operation == "-")
	{
		tmp = *(solution.end() - 2) - *(solution.end() - 1);
	}

	for (int i = 0; i < *numOfArgs; ++i)
		solution.pop_back();

	solution.push_back(tmp);
	return 0;
}

vector<double>* Calculator::handleOutput()
{
	char* end;
	vector<double> *solution = new vector<double>();
	while (!output.empty())
	{
		if (isNumber(output.front()))
			solution->push_back(strtod(output.front().c_str(), &end));
		else
			applyOperation(*solution, output.front());
		output.pop();
	}
	return solution;
}