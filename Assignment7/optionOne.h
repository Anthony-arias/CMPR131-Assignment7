// optionOne.h

#ifndef OPTION_ONE_LOCK
#define OPTION_ONE_LOCK

#include <math.h>
#include <sstream>
#include <cctype> 
#include <cstdlib> 
#include <cstring> 
#include <iostream> 
#include <stack> 
#include <string>
#include "input.h"
#include "optionTwo.h"

using namespace std;

double evaluatePostFix(string expression);
void evaluate_stack_tops(stack<double>& numbers, stack<char>& operations);

void calculate(void)
{
	cout << "Type a fully parenthesized arithmetic expression:" << endl;
	string postfix = infixToPostfix(cin);
	cout << "That evaluates to " << evaluatePostFix(postfix) << endl;
	pause("");
}

double evaluatePostFix(string expression)
{
	istringstream  ins(expression);
	const char RIGHT_PARENTHESIS = ')';
	const char LEFT_PARENTHESIS = '(';
	const char DECIMAL = '.';

	stack<double> numbers;
	stack<char> operations;
	double number;
	char symbol;

	while (ins && ins.peek() != '\n')
	{
		if (isdigit(ins.peek()) || (ins.peek() == DECIMAL))
		{
			ins >> number;
			numbers.push(number);
		}
		else if (strchr("+-*/^", ins.peek()) != NULL)
		{
			ins >> symbol;
			operations.push(symbol);
			evaluate_stack_tops(numbers, operations);
		}
		else if (ins.peek() == RIGHT_PARENTHESIS)
		{
			ins.ignore();
		}
		else
			ins.ignore();
	}

	return numbers.top();
}

void evaluate_stack_tops(stack<double>& numbers, stack<char>& operations)
{
	double operand1, operand2;
	operand2 = numbers.top();
	numbers.pop();
	operand1 = numbers.top();
	numbers.pop();
	switch (operations.top())
	{
	case '+': numbers.push(operand1 + operand2);
		break;
	case '-': numbers.push(operand1 - operand2);
		break;
	case '*': numbers.push(operand1 * operand2);
		break;
	case '/': numbers.push(operand1 / operand2);
		break;
	case '^': numbers.push(pow(operand1,operand2));
		break;
	}
	operations.pop();
}

#endif