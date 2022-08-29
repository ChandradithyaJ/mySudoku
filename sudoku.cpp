/*
* Author: Chandradithya.J
*/

#include <iostream>
#include <cstring>
using namespace std;

bool checkRow (int sudoku[9][9], int num, int row); // checks if any number in the row is the same as the inserted number
bool checkColumn (int sudoku[9][9], int num, int column); // checks if any number in the column is the same as the inserted number
bool checkBox (int sudoku[9][9], int num, int row, int column); // checks if any number in the box is the same as the inserted number
void displayBoard (int sudoku[9][9]); // displays the current sudoku board
bool validity (int sudoku[9][9], int num, int row, int column); // checks if the number can be entered in the selected box
bool findEmptyBoxes (int sudoku[9][9]); // check if the game is over or not
bool sudokuSolver (int sudoku[9][9]); // computer solves the sudoku board

int main()
{
    cout << "\n\n\n\t\t\tSUDOKU\n\n\n";
    int sudoku[9][9] = {
                       { 0, 0, 0, 0, 0, 0, 7, 0, 0 },
                       { 3, 9, 0, 7, 0, 8, 5, 4, 0 },
                       { 8, 6, 0, 0, 5, 4, 0, 0, 0 },
                       { 9, 0, 6, 0, 4, 7, 0, 0, 0 },
                       { 1, 3, 4, 2, 0, 0, 0, 9, 0 },
                       { 0, 5, 8, 1, 0, 9, 0, 0, 4 },
                       { 5, 4, 0, 9, 2, 3, 0, 0, 8 },
                       { 0, 0, 0, 0, 7, 0, 9, 0, 5 },
                       { 0, 0, 0, 0, 0, 1, 0, 3, 0 }
                       };

    displayBoard(sudoku);
    int row, column, num; // user enters a row, column and number
    int play = 1, playGame; // continue playing or skipping to the end

    cout << "Press 1 if you would like to continue, and 0 if you would like the computer to solve it: ";
    cin >> playGame;

    if (!playGame)
    {
        if (sudokuSolver(sudoku))
            displayBoard(sudoku);
        else cout << "No solution exists.";

        return 0;
    } // the game is over

    cout << "\nRows are numbered 1 to 9, starting from the left and the columns are numbered from the top.";

    while (findEmptyBoxes(sudoku))
    {
        if (play) // continue the game
        {
            cout << "\nRow: ";
            cin >> row;
            while (row < 1 || row > 9)
            {
                cout << "The rows are numbered 1 to 9.\nRow: ";
                cin >> row;
            }

            cout << "Column: ";
            cin >> column;
            while (column < 1 || column > 9)
            {
                cout << "The columns are numbered 1 to 9.\nColumn: ";
                cin >> column;
            }

            cout << "Number: ";
            cin >> num;
            while (num < 1 || num > 9)
            {
                cout << "All numbers in sudoku must be between 1 and 9.\nNumber: ";
                cin >> num;
            }

            if (validity(sudoku, num, row, column))
                sudoku[row-1][column-1] = num; // appropriate indices
            else cout << "Invalid. Please try again.\n";

            displayBoard(sudoku);

            cout << "\nIf you wish to continue playing, press 1. If you wish to skip to the answer, press 0: ";
            cin >> play;
            }

            else if (play == 0) // reveal the answer
                break;
    }

    if (play)
        cout << "\n\n\tCongratulations! You have solved it!\n\n";
    else
    {
        // reset to start the solver
        int sudoku[9][9] = {
                       { 0, 0, 0, 0, 0, 0, 7, 0, 0 },
                       { 3, 9, 0, 7, 0, 8, 5, 4, 0 },
                       { 8, 6, 0, 0, 5, 4, 0, 0, 0 },
                       { 9, 0, 6, 0, 4, 7, 0, 0, 0 },
                       { 1, 3, 4, 2, 0, 0, 0, 9, 0 },
                       { 0, 5, 8, 1, 0, 9, 0, 0, 4 },
                       { 5, 4, 0, 9, 2, 3, 0, 0, 8 },
                       { 0, 0, 0, 0, 7, 0, 9, 0, 5 },
                       { 0, 0, 0, 0, 0, 1, 0, 3, 0 }
                       };

        if (sudokuSolver(sudoku))
            displayBoard(sudoku);
        else cout << "No solution exists.";
    }

    return 0;
}

bool checkRow (int sudoku[9][9], int num, int row)
{
    for (int i = 0; i <= 8; i++)
        if (sudoku[row - 1][i] == num) // user enters the number of the row, not the index
            return true;

    return false;
}

bool checkColumn (int sudoku[9][9], int num, int column)
{
    for (int i = 0; i <= 8; i++)
        if(sudoku[i][column - 1] == num)
            return true;

    return false;
}

  /* The boxes are numbered 1 to 9 starting from the top left corner and ending at the bottom right corner.
     THe count goes from left to right, restarting at the far left box of the next column */

bool checkBox (int sudoku[9][9], int num, int row, int column)
{
    // the indices of the first row and column of the box to be checked
    // if the first row of the box is 7, the boxStartRow will be 6 - the index
    // in the array
    int boxStartRow = (row-1) - (row-1)%3;
    int boxStartColumn = (column-1) - (column-1)%3;

    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            if (sudoku[boxStartRow+i][boxStartColumn+j] == num)
                return true;
        }
    }

    return false;
}

void displayBoard(int sudoku[9][9])
{

    cout << "\t";
    for (int i = 1; i <= 9; i++)
    {
        cout << " ___";
    }
    cout << endl;

    for(int i = 0; i < 9; i++) // nine rows
    {
        cout << "\t";
        for (int j = 1; j <= 10; j++)
        {
            cout << "|   ";
        }
        cout << endl << "\t| ";
        for (int k = 0; k < 9; k++)
        {
            if (sudoku[i][k] == 0)
                cout << " "; // blank space if it is zero
            else cout << sudoku[i][k];

            cout << " | ";
        }
        cout << endl << "\t";
        for (int l = 1; l <= 9; l++)
        {
            cout << "|___";
        }
        cout << "|" << endl;
    }
}

bool validity (int sudoku[9][9], int num, int row, int column)
{
    if (checkBox(sudoku, num, row, column) == 0 && checkColumn(sudoku, num, column) == 0 && checkRow(sudoku, num, row) == 0)
        return true;
    return false;
}

bool findEmptyBoxes (int sudoku[9][9]) // returns true if any box is empty
{
    for (int row = 1; row <= 9; row++)
    {
        for (int column = 1; column <= 9; column++)
        {
            if (sudoku[row-1][column-1] == 0)
                return true;
        }
    }

    return false;
}

/* We'll be using backtracking by using a partially filled grid and placing a
*  number at an unassigned grid and check if it has been solved using recursion
*  and the number reverts to zero if it cannot be placed there
*/

bool sudokuSolver (int sudoku[9][9])
{
    bool emptyBoxes = 0; // helps us retain the value of row and column if empty boxes are present

    int row, column;

    if (!findEmptyBoxes(sudoku)) // checking for empty boxes
        return true;
    else
    {
        for (row = 1; row <= 9; row++)
        {
            for (column = 1; column <= 9; column++)
            {
                if (sudoku[row-1][column-1] == 0)
                {
                    emptyBoxes = 1;
                    break;
                }
            }
            if (emptyBoxes)
                break;
        }
    }

    for (int num = 1; num <= 9; num++) // considering all possible digits
    {
        if (validity(sudoku, num, row, column))
        {
            sudoku[row-1][column-1] = num;

            if (sudokuSolver(sudoku)) // call for recursion
                return true;

            sudoku[row-1][column-1] = 0; // backtrack
        }
    }

    return false;
}
