#include<stdio.h>

void update_possiblities(int row, int col, int num)
{
    int sudoku[9][9][10];
    //removes the possiblities of a recently placed number
    for(int i = 1; i < 10; i++)
    {
        sudoku[row][col][i] = 0;
    }

    for(int changing_row = 0; changing_row < 9; changing_row++)
    {
        sudoku[changing_row][col][num] = 0;
    }
    
    for(int changing_col = 0; changing_col < 9; changing_col++)
    {
        sudoku[row][changing_col][num] = 0;
    }

    for(int changing_row = row - row % 3; changing_row < (row-row%3)+3; changing_row++)
    {
        for(int changing_col = col - col % 3; changing_col < (col-col%3)+3;changing_col++)
        {
            sudoku[changing_row][changing_col][num] = 0;
        }
    }

}
