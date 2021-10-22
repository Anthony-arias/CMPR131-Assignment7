// optionTwo.h

#ifndef OPTION_TWO_LOCK
#define OPTION_TWO_LOCK

#include <sstream>
#include <iostream> 
#include <stack> 
#include <string>
#include "input.h"

using namespace std;

//PreCondition: input is type char
//PostCondition: returns type int precedence ranking of arithmetic operation
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

//PreCondition: input is istream reference
//PostCondition: returns conversion of infix expression to postfix
string infixToPostfix(istream& ins)
{
	const char RIGHT_PARENTHESIS = ')';
	const char LEFT_PARENTHESIS = '(';
	const char DECIMAL = '.';
	stack<char> operations;
	string expression = "";

	double number;
	char operand;
	char symbol;

	while (ins && ins.peek() != '\n')
	{
		if (ins.peek() == LEFT_PARENTHESIS)
		{
			ins >> symbol;
			operations.push(symbol);
		}
		else if (isdigit(ins.peek()) || isalpha(ins.peek()) || (ins.peek() == DECIMAL))
		{
			if (isalpha(ins.peek()))
			{
				ins >> operand;
				expression += operand;
				expression += " ";
			}
			else
			{
				ins >> number;
				string temp = to_string(number);
				temp.erase(temp.find_last_not_of('0') + 1, std::string::npos);
				temp.erase(temp.find_last_not_of('.') + 1, std::string::npos);
				expression += temp + " ";
			}
			
		}
		else if (strchr("+-*/^", ins.peek()) != NULL)
		{
			while (!operations.empty() && operations.top() != LEFT_PARENTHESIS && precedence(operations.top()) >= precedence(ins.peek()))
			{
				expression += operations.top();
				expression += " ";
				operations.pop();

			} 
			ins >> symbol;
			operations.push(symbol);
		}
		else 
		{

			if (ins.peek() == RIGHT_PARENTHESIS)
			{
				ins.ignore();
				while (!operations.empty() && operations.top() != LEFT_PARENTHESIS)
				{
					expression += operations.top();
					expression += " ";
					operations.pop();
				}
				if (!operations.empty() && operations.top() == LEFT_PARENTHESIS)
				{
					operations.pop();
				}
				else
				{
					expression = "ERROR: unbalanced parentheses.";
					break;
				}
			}
			else
			{
				expression = "ERROR: invalid expression.";
				cin.ignore(999, '\n');
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
			expression += " ";
			operations.pop();
		}
	}

	
	return expression;
	//cout << "\tPostfix expression: " << expression << endl;
}

//PreCondition: NA
//PostCondition: ask user for expression input and calls function to convert expression
void convert(void)
{
	do
	{
		cout << endl;
		cout << "\tType an arithmetic expression: ";
		cout << "\tPostfix expression: " << infixToPostfix(cin) << endl;
		//cout << infixToPostfix(cin);
		cout << endl;
	} while (isRepeat("\n\tContinue (Y-yes or N-no)? "));
}

#endif
