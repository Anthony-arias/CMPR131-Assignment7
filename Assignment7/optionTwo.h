// optionTwo.h

#ifndef OPTION_TWO_LOCK
#define OPTION_TWO_LOCK

#include <iostream> 
#include <stack> 
#include <string>
#include "input.h"

using namespace std;

int precedence(char ch)
{
	if (ch == '+' || ch == '-')
		return 1;
	if (ch == '/' || ch == '*')
		return 2;
	if (ch == '^')
		return 3;
	return 4;
}

void infixToPostfix(istream& ins)
{
	const char RIGHT_PARENTHESIS = ')';
	const char LEFT_PARENTHESIS = '(';
	stack<char> operations;
	string expression = "";
	char operand;
	char symbol;

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
			while (!operations.empty() && operations.top() != LEFT_PARENTHESIS && precedence(operations.top()) >= precedence(ins.peek()))
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

void convert(void)
{
	do
	{
		string input;
		cout << "\tType an arithmetic expression: ";
		infixToPostfix(cin);
		cout << endl;
	} while (isRepeat("\n\tContinue (Y-yes or N-no)? "));
}

#endif