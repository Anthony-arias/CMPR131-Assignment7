// optionThree.h

#ifndef OPTION_THREE_LOCK
#define OPTION_THREE_LOCK

#include <iostream>
#include <vector>
#include <stack>
#include "input.h"

using namespace std;

void displayBoard(vector< vector <char>> v);
bool checkQueenCondition(vector< vector <char>>& v, int row, int col, int size);
bool checkEmptyBoard(vector< vector <char>>& v, int size);
bool checkWinningCondition(vector<vector <char>>& v, int size);
void inputQueen(stack<int>& s, vector< vector <char>>& v, int& row, int& col, int size, int& count);
void removeQueen(stack<int>& s, vector< vector <char>>& v, int& row, int& col, int size, int& count);
bool setQueenNextRow(stack<int>& s, vector< vector <char>>& v, int size, int& count);
bool moveQueenPreviousRow(stack<int>& s, vector< vector <char>>& v, int size, int& count);
void backTracking(stack<int>& s, vector< vector <char>>& v, int size, int& count);

// Precondition: valid nested char vector to display board game and the board's size
// Postcondition: input a queen from indicated position
void inputQueen(stack<int> &s, vector< vector <char>>& v, int& row, int& col, int size, int& count)
{

	v[row - 1][col - 1] = 'Q';
	s.push(col);
	count++;
}

// Precondition: valid nested char vector to display board game and the board's size
// Postcondition: remove a queen from indicated position
void removeQueen(stack<int>& s, vector< vector <char>>& v, int& row, int& col, int size, int& count)
{

	v[row - 1][col - 1] = '_';
	s.pop();
	count--;
}

// Precondition: valid nested char vector to display board game, valid row, valid column, the board's size
// Postcondition: return true if queens in table is not conflicted with each other, and false if it is not
bool checkQueenCondition(vector< vector <char>>& v, int row, int col, int size)
{
	// Check columns if there are queens on the same row
	for (int i = 0; i < size; i++)
	{
		if (v[row][i] == 'Q')
			return false;
	}
	// Check rows if there are queens on the same column
	for (int i = 0; i < size; i++)
		if (v[i][col] == 'Q')
			return false;

	// Check diagonal lines if there are queens on the same line
	for (int i = row, j = col; i >= 0 && j >= 0; i--, j--)
		if (v[i][j] == 'Q')
			return false;

	for (int i = row, j = col; i >= 0 && j < size; i--, j++)
		if (v[i][j] == 'Q')
			return false;

	for (int i = row, j = col; i < size && j >= 0; i++, j--)
		if (v[i][j] == 'Q')
			return false;

	for (int i = row, j = col; i < size && j < size; i++, j++)
		if (v[i][j] == 'Q')
			return false;

	return true;
}

// Precondition: valid nested char vector to display board game and the board's size
// Postcondition: return true if winning condition is valid and false if it is not
bool checkWinningCondition(vector<vector <char>>& v, int size)
{
	int findQueen = 0;
	for (int i = 0; i < size; i++)
		for (int j = 0; j < size; j++)
			if (v[i][j] == 'Q')
				findQueen++;

	if (findQueen == size)
		return true;
	return false;
}


// Precondition: valid nested char vector to display board game
// Postcondition: display the content in board game
void displayBoard(vector< vector <char>> v)
{
	cout << endl;
	int shapeSize = v.capacity() + 2;
	for (int row = 0; row < shapeSize; ++row)
	{
		cout << "\t";
		if (row == 0 || row == shapeSize - 1)
		{
			for (int column = 0; column < shapeSize; ++column)
			{
				if (row == 0)
				{
					if (column == 0)
						cout << char(201);
					else
					{
						if (column == shapeSize - 1)
							cout << char(205) << char(187);
						else
							cout << string(2, char(205));
					}
				}
				else
				{
					if (column == 0)
						cout << char(200);
					else
					{
						if (column == shapeSize - 1)
							cout << char(205) << char(188);
						else
							cout << string(2, char(205));
					}
				}
			}
		}

		else
		{
			for (int column = 0; column < shapeSize; ++column)
				if (column == 0)
					cout << char(186) << " ";
				else
				{
					if (column == shapeSize - 1)
						cout << " " << char(186);
					else
					{
						int i = row - 1;
						int j = column - 1;
						if (v[i][j] == '_' || v[i][j] == 'Q')
						{
							if (i == v.capacity() - 1 && v[i][j] == '_')
							{
								if (j < v.capacity() - 1)
									cout << ' ' << char(179);
								else
									cout << ' ';
							}
							else
							{
								if (j < v.capacity() - 1)
									cout << v[i][j] << char(179);
								else
									cout << v[i][j];
							}
						}
					}
				}
		}
		cout << endl;
	}
}

//Precondition: NA
//Postcondition: show the solution of n-Queens problem by using backtracking
void backTracking(stack<int>& s, vector< vector <char>>& v, int size, int& count)
{

	while (!checkWinningCondition(v, size))
	{
		bool newQueenSet = setQueenNextRow(s, v, size, count);

		while (!newQueenSet)
		{
			newQueenSet = moveQueenPreviousRow(s, v, size, count);
		}
	}
}

//Precondition: Game has not solved yet
//Postcondition: Set a queen on the next row at an non-conflicted position
bool setQueenNextRow(stack<int> &s, vector< vector <char>>& v, int size, int& count)
{
	int nextRow = s.size() + 1;
	for (int column = 1; column <= size; column++)
	{
		
		if (v[nextRow - 1][column - 1] != 'Q' && !checkQueenCondition(v, nextRow, column, size))
		{
			inputQueen(s, v, nextRow, column, size, count);
			++nextRow;
			return true;
		}
	}
	return false;
}

// Precondition: Previous row was existed in stack
// Postcondition: Moves the queen on the previous row to the next non-conflicted position
bool moveQueenPreviousRow(stack<int>& s, vector< vector <char>>& v, int size, int& count)
{
	int previousRow = s.size();
	int previousColumn = s.top();

	removeQueen(s, v, previousRow, previousColumn, size, count);
	for (int nextColumn = previousColumn + 1; nextColumn <= size; nextColumn++)
	{
		if (v[previousRow - 1][previousColumn - 1] != 'Q' && !checkQueenCondition(v, previousRow, nextColumn, size))
		{
			inputQueen(s, v, previousRow, nextColumn, size, count);
			return true;
		}
	}
	return false;
}

#endif
