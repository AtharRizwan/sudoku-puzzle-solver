#include<stdio.h>
#include<stdbool.h>

int main(void)
{

    int sudoku[8][8][10];
    for(int row = 0; row < 8; row+=3)
    {
        for(int col = 0; col < 8; col+=3)
        {
            for(int identify_direction = 0; identify_direction < 2; identify_direction++)
            {
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
                for(int ad_row = 0; ad_row < 3; ad_row++)
                {
                    for(int ad_col = 0; ad_col < 2; ad_col++)
                    {
                        for(int first = 1; first < 10; first++)
                        {
                            for(int second = 2; second < 10; second++)
                            {
                                if(first == second)
                                {
                                    continue;
                                }
                                if(sudoku[row+ad_row][col+ad_col][first] == first)
                                {
                                    bool hidden_pair_termination = false;
                                    if(sudoku[row+ad_row][col+ad_col][second] == second)
                                    {
                                        if((sudoku[row+ad_row+k][col+ad_col+i][first] == first && sudoku[row+ad_row+k][col+ad_col+i][second] == second) ||
                                            (sudoku[row+ad_row+l][col+ad_col+j][first] == first && sudoku[row+ad_row+l][col+ad_col+j][second] == second))
                                        {
                                            if(i == 1)
                                            {    
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

        for(int ad_col = 0; ad_col < 3; ad_col++)
        {
            for(int ad_row = 0; ad_row < 2; ad_row++)
            {
                for(int first = 0; first < 10; first++)
                {
                    for(int second = 0; second < 10; second++)
                    {
                        if(first == second)
                        {
                            continue;
                        }
                        else
                        {

                        }
                    }
                }
            }
        }








    }
}