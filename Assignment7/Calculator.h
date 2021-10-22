// Calculator.h

#ifndef CALCULATOR_LOCK
#define CALCULATOR_LOCK

#include <iostream>
#include <sstream>
#include <stack>
#include <string>
#include <stdexcept>
#include <cctype>
#include <cstdlib>
#include <cstring>
using namespace std;

class Calculator {
private:
	stack<char> bag;

	const char LEFT_PARENTHESES		= '(';
	const char RIGHT_PARENTHESES	= ')';
	const char DECIMAL				= '.';

	double evaluation;

	string myExpression;

private:
	// Precondition: 
	// Postcondition: Returns true if parentheses match throughout the expression
	bool isBalanced(const string& expression) {
		stack<char> store;
		string::size_type i;
		char next;
		bool failed = false;

		if (expression.at(0) != '(' || expression.at(expression.size() - 1) != ')')
			return false;

		for (i = 0; !failed && (i < expression.length()); i++) {
			next = expression[i];
			if (next == LEFT_PARENTHESES)
				store.push(next);
			else if ((next == RIGHT_PARENTHESES) && (!store.empty()))
				store.pop();
			else if ((next == RIGHT_PARENTHESES) && (store.empty()))
				failed = true;
		}

		return (store.empty() && !failed);
	}

	// Precondition: expression must be fully parenthesized
	// Postcondition: the expression is evaluated as an arithmetic expression and the value is returned
	double readAndEvaluate(istream& expression) {
		stack<double> numbers;
		stack<char> operations;
		double number;
		char symbol;

		while (expression && expression.peek() != '\n') {
			if (isdigit(expression.peek()) || (expression.peek() == DECIMAL)) {
				expression >> number;
				numbers.push(number);
			}
			else if (strchr("+-*/^", expression.peek()) != NULL) {
				expression >> symbol;
				operations.push(symbol);
			}
			else if (expression.peek() == RIGHT_PARENTHESES) {
				expression.ignore();
				evaluateStackTops(numbers, operations);
			}
			else expression.ignore();
		}

		return numbers.top();
	}

	// Precondition: top of stack contains +, 0, *, or /and the numbers stack contains at least 2 numbers
	// Postcondition: Top two numbers have been popped, top  operation has been popped, and the two numbers have been combined using the operation. Result is pushed back onto numbers stack
	void evaluateStackTops(stack<double>& numbers, stack<char>& operations) {
		double operand1, operand2;

		operand2 = numbers.top();
		numbers.pop();
		operand1 = numbers.top();
		numbers.pop();

		switch (operations.top()) {
		case '+': numbers.push(operand1 + operand2); break;
		case '-': numbers.push(operand1 - operand2); break;
		case '*': numbers.push(operand1 * operand2); break;
		case '/': numbers.push(operand1 / operand2); break;
		case '^': numbers.push(pow(operand1,operand2)); break;
		default: throw invalid_argument("\tERROR: Invalid arithmetic expression."); break;
		}
		
		operations.pop();
	}

public:
	Calculator() 
	{
		evaluation = 0;
	}

	Calculator(string expression) 
	{
		if (!isBalanced(expression))
			throw invalid_argument("\tERROR: Parentheses don't match.");
		
		istringstream istr(expression);
		evaluation = readAndEvaluate(istr);
	}

	void setExpression(string expression) 
	{
		if (!isBalanced(expression))
			throw invalid_argument("\tERROR: Parentheses don't match");

		istringstream istr(expression);
		evaluation = readAndEvaluate(istr);
	}
	
	double getEvaluaton() {
		return evaluation;
	}

};

#endif