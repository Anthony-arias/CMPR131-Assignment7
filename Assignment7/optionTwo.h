// optionTwo.h

#ifndef OPTION_TWO_LOCK
#define OPTION_TWO_LOCK

#include <cctype> // Provides isdigit
#include <cstdlib> // Provides EXIT_SUCCESS
#include <cstring> // Provides strchr
#include <iostream> // Provides cout, cin, peek, ignore
#include <stack> // Provides the stack template class
#include <string>
#include "input.h"


using namespace std;

double read_and_evaluate(istream& ins);
void evaluate_stack_tops(stack<double>& numbers, stack<char>& operations);

void toPostfixNotation(istream& ins)
{
	const char DECIMAL = '.';
	const char RIGHT_PARENTHESIS = ')';
	const char LEFT_PARENTHESIS = '(';

	stack<double> numbers;
	stack<char> operations;
	double number;
	char symbol;
	// Loop continues while istream is not “bad” (tested by ins) and next character isn’t newline.
	while (ins && ins.peek() != '\n')
	{
		if (ins.peek() == LEFT_PARENTHESIS)
		{
			ins >> symbol;
			operations.push(symbol);
		}
		else if (isdigit(ins.peek()) || (ins.peek() == DECIMAL))
		{
			ins >> number;
			cout << number;
			numbers.push(number);
		}
		else if (strchr("+-*/^", ins.peek()) != NULL)
		{
			while (true)
			{
				if (operations.empty() || operations.top() == LEFT_PARENTHESIS) break;

				if (ins.peek() == RIGHT_PARENTHESIS 
					&& ( operations.top() == '^' || operations.top() == '*'
						|| operations.top() == '/' || operations.top() == '+'
						|| operations.top() == '-'))
				{
					break;
				}
				else if (ins.peek() == '^'
					&& (operations.top() == '*' || operations.top() == '/'
					|| operations.top() == '+'
					|| operations.top() == '-'))
				{
					break;
				}
				else if (ins.peek() == '*'
					&& (operations.top() == '/'
						|| operations.top() == '+'
						|| operations.top() == '-'))
				{
					break;
				}
				else if (ins.peek() == '/'
					&& (operations.top() == '+'
						|| operations.top() == '-'))
				{
					break;
				}
				else if (ins.peek() == '+'
					&& (operations.top() == '-'))
				{
					break;
				}
				cout << operations.top();
				operations.pop();
			}
			ins >> symbol;
			operations.push(symbol);
		}
		else
		{
			bool foundLeft = false;
			while (true)
			{
				if (operations.empty()) break;
				if (operations.top() == LEFT_PARENTHESIS)
				{
					foundLeft = true;
					operations.pop();
					break;
				}
				cout << operations.top();
				operations.pop();
			}
			if (!foundLeft)
			{
				cout << "unbalanced equation" << endl;
			}
			////cout << operations.top();
			////operations.pop();
			//while (true)
			//{
			//	if (operations.empty()) break;
			//	if (operations.top() == LEFT_PARENTHESIS)
			//	{
			//		operations.pop();
			//		break;
			//	}
			//	
			//	cout << operations.top();
			//	operations.pop();
			//}
			ins.ignore();
			////evaluate_stack_tops(numbers, operations);
		}
	}
	while (true)
	{
		if (operations.empty()) break;
		if (operations.top() == LEFT_PARENTHESIS || operations.top() == RIGHT_PARENTHESIS)
		{
			cout << "unbalanced equation" << endl;
			break;
		}
		cout << operations.top();
		operations.pop();
	}
	//return numbers.top();
}

void optionTwoCall(void)
{
	double answer;

	string input;
	cout << "Type a arithmetic expression:" << endl;

	toPostfixNotation(cin);
	//cout << "That evaluates to " << answer << endl;
	pause("");
}

//double read_and_evaluate(istream& ins)
//{
//	const char DECIMAL = '.';
//	const char RIGHT_PARENTHESIS = ')';
//
//	stack<double> numbers;
//	stack<char> operations;
//	double number;
//	char symbol;
//	// Loop continues while istream is not “bad” (tested by ins) and next character isn’t newline.
//	while (ins && ins.peek() != '\n')
//	{
//		if (isdigit(ins.peek()) || (ins.peek() == DECIMAL))
//		{
//			ins >> number;
//			cout << number;
//			numbers.push(number);
//		}
//		else if (strchr("+-*/", ins.peek()) != NULL)
//		{
//			ins >> symbol;
//			cout << symbol;
//			operations.push(symbol);
//		}
//		else if (ins.peek() == RIGHT_PARENTHESIS)
//		{
//			ins.ignore();
//			evaluate_stack_tops(numbers, operations);
//		}
//		else
//			ins.ignore();
//	}
//
//	return numbers.top();
//}

//void evaluate_stack_tops(stack<double>& numbers, stack<char>& operations)
//{
//	double operand1, operand2;
//	operand2 = numbers.top();
//	numbers.pop();
//	operand1 = numbers.top();
//	numbers.pop();
//	switch (operations.top())
//	{
//	case '+': numbers.push(operand1 + operand2);
//		break;
//	case '-': numbers.push(operand1 - operand2);
//		break;
//	case '*': numbers.push(operand1 * operand2);
//		break;
//	case '/': numbers.push(operand1 / operand2);
//		break;
//	}
//	operations.pop();
//}

#endif