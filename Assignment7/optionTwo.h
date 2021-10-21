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
	cout << "\t";
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
					&& (operations.top() == '^' || operations.top() == '*'
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

int precedence(char ch)
{
	if (ch == '+' || ch == '-')
		return 1;
	if (ch == '/' || ch == '*')
		return 2;
	if (ch == '^')
		return 3;
	return 0;
}

void infixToPostfix(istream& ins)
{
	const char RIGHT_PARENTHESIS = ')';
	const char LEFT_PARENTHESIS = '(';
	stack<char> operations;
	string expression = "";
	char operand;
	char symbol;
	// Loop continues while istream is not “bad” (tested by ins) and next character isn’t newline.

	while (ins && ins.peek() != '\n')
	{
		if (ins.peek() == LEFT_PARENTHESIS)
		{
			ins >> symbol;
			operations.push(symbol);
		}
		else if (isdigit(ins.peek()) || isalpha(ins.peek()))
		{
			ins >> operand;
			expression += operand;
		}
		else if (strchr("+-*/^", ins.peek()) != NULL)
		{
			while (!operations.empty() && operations.top() != LEFT_PARENTHESIS && precedence(operations.top()) > precedence(ins.peek()))
			{
				expression += operations.top();
				operations.pop();

			} 
			ins >> symbol;
			operations.push(symbol);
		}
		else 
		{
			ins.ignore();
			while (!operations.empty() && operations.top() != LEFT_PARENTHESIS) 
			{
				expression += operations.top();
				operations.pop();
			}
			if (!operations.empty() && operations.top() == LEFT_PARENTHESIS)
			{
				operations.pop();
			}
			else
			{
				expression = "ERROR: inbalanced parentheses.";
				break;
			}
		}
	} 

	while (!operations.empty())
	{
		if (operations.top() == LEFT_PARENTHESIS)
		{
			expression = "ERROR: inbalanced parentheses.";
			break;
		}
		else
		{
			expression += operations.top();
			operations.pop();
		}
	}
	cout << "\tPostfix expression: " << expression << endl;
}
void optionTwoCall(void)
{
	do
	{
		double answer;

		string input;
		cout << "\tType an arithmetic expression: ";
		infixToPostfix(cin);
		cout << endl;

	} while (isRepeat("\n\tContinue (Y-yes or N-no)? "));
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