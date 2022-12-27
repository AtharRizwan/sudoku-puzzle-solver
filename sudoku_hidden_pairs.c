#include<stdio.h>
#include<stdbool.h>

int main(void)
{



    int sudoku[9][9][10];     
    // the first two for loops help to get to the first cell of each 3x3 grid
    for(int row = 0; row < 9; row+=3)   
    {
        for(int col = 0; col < 9; col+=3)
        {
            // this loop identifies whether the direction is in column or row
            // if identify_function = 0  then direction is in row direction or rightward
            // otherwise direction is in col direction or downward
            for(int identify_direction = 0; identify_direction < 2; identify_direction++)
            {
                // variables to set direction
                int i, j, k, l;
                if(identify_direction == 0)
                {
                    i = 1;
                    j = 2;
                    k = 0;
                    l = 0;
                }
                if(identify_direction == 1)
                {
                    k = 1;
                    l = 2;
                    i = 0;
                    j = 0;
                }
                // goes throug every row in the 3x3 grid
                // Y  N  N
                // Y  N  N
                // Y  N  N
                for(int ad_row = 0; ad_row < 3; ad_row++)
                {
                    // goes through the first two column of the 3x3 grid
                    // Y  Y  N
                    // Y  Y  N
                    // Y  Y  N
                    for(int ad_col = 0; ad_col < 2; ad_col++)
                    {
                        // goes through to pick up the first element for naked pair
                        for(int first = 1; first < 10; first++)
                        {
                            // goes through the second possibility after the first for naked pair
                            // the makes up an x and y combination of possiblities where x is one possibility and y is the other
                            for(int second = first+1; second < 10; second++)
                            {
                                // both possibilities cannot be the same
                                if(first == second)
                                {
                                    // to go to the loop once again and look for another y possibility not matching x
                                    continue;
                                }
                                // to check whether first is a possibility or not a possiblity
                                if(sudoku[row+ad_row][col+ad_col][first] == first)
                                {
                                    bool hidden_pair_termination = false;
                                    // to check whether y is a possiblity
                                    if(sudoku[row+ad_row][col+ad_col][second] == second)
                                    {
                                        // checks whether one of the two other blocks in the 3x3 grid's row or col contain that same pair
                                        if((sudoku[row+ad_row+k][col+ad_col+i][first] == first && sudoku[row+ad_row+k][col+ad_col+i][second] == second) ||
                                            (sudoku[row+ad_row+l][col+ad_col+j][first] == first && sudoku[row+ad_row+l][col+ad_col+j][second] == second))
                                        {
                                            // if yes then make sure that the other rows or columns do not contain those possibilites
                                            if(i == 1)
                                            {    
                                                // so the code below makes sure that the same possiblities are not in the other rows or column in that same 3x3 grid
                                                for(int again_row = 0; again_row < 3; again_row++)
                                                {
                                                    if(ad_row == again_row)
                                                    {
                                                        continue;
                                                    }
                                                    else
                                                    {
                                                        for(int again_col; again_col < 3; again_col++)
                                                        {
                                                            if(sudoku[row+again_row][col+again_col][first] == first || sudoku[row+again_row][col+again_col][second] == second)
                                                            {
                                                                hidden_pair_termination = true;
                                                                break;
                                                            }
                                                        }
                                                        if(hidden_pair_termination == true)
                                                        {
                                                            break;
                                                        }
                                                        else
                                                        {
                                                            // Here, the code has gone through every step 
                                                            // Now, the code would eliminate all the other possiblities that are deemed unnecessary 
                                                            // by the naked pair algorithm
                                                            for(int refining_col = 0; refining_col < 8; refining_col++)
                                                            {
                                                                if(refining_col >= col && refining_col < col + 3)
                                                                {
                                                                    sudoku[row+ad_row][refining_col][first] = 0;
                                                                    sudoku[row+ad_row][refining_col][second] = 0;
                                                                }
                                                                else
                                                                    continue;
                                                            }
                                                        }
                                                    }
                                                }
                                            }
                                            if(k == 1)
                                            {
                                                // this code checks everything for the columns 
                                                for(int again_col = 0; again_col < 3; again_col++)
                                                {
                                                    if(again_col == ad_col)
                                                    {
                                                        continue;
                                                    }
                                                    else
                                                    {
                                                        for(int again_row; again_row < 3; again_row++)
                                                        {
                                                            if(sudoku[row+again_row][col+again_col][first] == first || sudoku[row+again_row][col+again_col][second] == second)
                                                            {
                                                                hidden_pair_termination = true;
                                                                break;
                                                            }
                                                        }
                                                        if(hidden_pair_termination == true)
                                                        {
                                                            break;
                                                        }
                                                        else
                                                        {
                                                            for(int refining_row = 0; refining_row < 9; refining_row++)
                                                            {
                                                                if(refining_row >= col && refining_row < col + 3)
                                                                {
                                                                    sudoku[refining_row][col+ad_col][first] = 0;
                                                                    sudoku[refining_row][col+ad_col][second] = 0;
                                                                }
                                                                else
                                                                    continue;
                                                            }
                                                        }
                                                    }
                                                }
                                            }
                                            if(hidden_pair_termination == true)
                                            {
                                                // this specific segment is used to advance to the next step as previous operation has failed
                                                continue;
                                            }
                                        }
                                    }
                                    else
                                        continue;
                                }
                                else
                                    break;
                            }
                        }

                    }
                }
            }
        }
    }
}
