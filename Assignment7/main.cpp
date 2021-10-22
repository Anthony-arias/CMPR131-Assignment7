// main.cpp

// Team: Anthony, An, Van, Vincent, Nhan
// Chapter 7:
// 10/14/2021


#include <iostream>
#include <string>
#include "optionOne.h"
#include "optionTwo.h"
#include "optionThree.h"
#include "input.h"

void displayMainMenu(void);
void mainMenu(void);
void programOne(void);
void programTwo(void);
void programThree(void);

using namespace std;

int main(void)
{
    mainMenu();
    return 0;
}

//PreCondition: NA
//PostCondition: redirects user to different menus based on their choice
void mainMenu(void)
{
    do
    {
        clearScreen();

        displayMainMenu();

        int userInput = inputInteger("\t\tOption: ", 0, 3);
        switch (userInput)
        {
        case 0: return;
        case 1: programOne(); break;
        case 2: programTwo(); break;
        case 3: programThree(); break;
        default: cout << "\t\tERROR-3A: Invalid input. Must be from 0..3." << endl;
        }

    } while (true);
}

//PreCondition: NA
//PostCondition: 
void programOne(void)
{
    clearScreen();
    cout << "\t1> Simple Calculator" << endl;
    cout << "\t" + string(100, char(196)) << endl;

    calculate();

    pause("\tdelete function");
    /*function(s) here*/
}


//PreCondition: NA
//PostCondition: 
void programTwo(void)
{
    clearScreen();
    cout << "\t2> Translation of Arithmetic Expression" << endl;
    cout << "\t" + string(100, char(196)) << endl;
    
    convert();
}

//PreCondition: NA
//PostCondition: 
void programThree(void)
{
    clearScreen();
    cout << "\t3 > n - Queens Problem" << endl;
    cout << "\t" + string(100, char(196)) << endl;
    
    stack<int> s;
    int queenCount = 0; // count the number of queen exist in game
    int row = 1; // initial position of row for backtracking
    int n = inputInteger("\n\tEnter a number(1..100) of queens: ", 1, 100);
    int inputColumn = inputInteger("\n\tPosition a queen in the column (1.." + to_string(n) + "): ", 1, n);
    vector<vector<char>> board(n, vector<char>(n, '_'));
    if (n == 2 || n == 3)
    {
        displayBoard(board);
        cout << "\tNo solution.\n";
        system("PAUSE");
    }
       
    else
    {
        vector<vector<char>> board(n, vector<char>(n, '_'));
        displayBoard(board);

        cout << "\n\t" << n << "-Queen(s) solution: \n";
        inputQueen(s, board, row, inputColumn, n, queenCount);
        backTracking(s, board, n, queenCount);
        displayBoard(board);
        system("PAUSE");
    }
}

//PreCondition: NA
//PostCondition: displays main menu options
void displayMainMenu(void)
{
    cout << "\n\tCMPR131 Chapter 7: Applications using Stacks by Anthony, An, Van, Vincent, Nhan (10/21/21)" << endl;
    cout << "\t" + string(100, char(205)) << endl;
    cout << "\t\t1> Simple Calculator (problem 9, pg 391)" << endl;
    cout << "\t\t2> Translation of arithmetic expression (problem 10, pg 391)" << endl;
    cout << "\t\t3> n-Queens Problem (problem 11, pg 391-292)" << endl;
    cout << "\t" + string(100, char(196)) << endl;
    cout << "\t\t0> exit" << endl;
    cout << "\t" + string(100, char(205)) << endl;
}
