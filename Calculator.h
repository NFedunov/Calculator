#pragma once
#include <iostream>
#include <stack>
#include <queue>
#include <map>
#include <vector>

using namespace std;


//SYMBOL for operations like sin, cos...
enum elemType { SYMBOL, OPERATION, NUMBER, UNKNOWN };

class Calculator
{
	// key - operation, [priority, number of args]
	map<string, vector<int>> operations{
		{"*", { 1, 2}},
		{"/", { 1, 2}},
		{"+", { 0, 2}},
		{"-", { 0, 2}},
		{"(", {-1, 0}},
		{")", {-1, 0}}
	};
	
	string rawString;
	queue<string> output;
	stack<string> operationsStack;

	//using for bracket check. If "(" => +1, else -1. If value < 0 then wrong brackets.
	//In end of handling rawString value must be 0.
	int bracketCounter = 0;
	
	//return next element of raw string
	string getNextElement(unsigned int& pointer);
	// priority of operation1 less than operation2?
	bool lessPriority(string operation1, string operation2);
	//check if elem is number
	bool isNumber(string elem);
	elemType getElemType(const char &ch);
	vector<double>* handleOutput();
	int applyOperation(vector<double>&, const string &operation);
public:
	Calculator();
	int handleRawString(const string &rawString);
	virtual ~Calculator();
};

