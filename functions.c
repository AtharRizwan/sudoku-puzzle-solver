#include <stdio.h>
#include <stdbool.h>
int sudoku[9][9][10];

// Function to take a sudoku puzzle from user
void get_sudoku(void)
{
    printf("Enter a sudoku puzzle row wise(0 for blank space).\n");
    printf("A stream of numbers should be entered from 0 to 9.\n");
    printf("Any number entered that is ouside this limit will not be registered.\n");
    // Take inputs in the sudoku global array
    for (int i = 0; i < 9; i++)
    {
        // Tell user the row number
        printf("Enter row %d: ", i + 1);
        for (int j = 0; j < 9; j++)
        {
            // Keep taking input until it is between 0 and 9 inclusive
            do
            {
                scanf("%1d", &sudoku[i][j][0]);
            } while (sudoku[i][j][0] < 0 || sudoku[i][j][0] > 9);
        }
    }
}

void display_sudoku(void)
{
    printf("\n\n");
    // For rows 1 to 3
    for (int i = 0; i < 3; i++)
    {
        printf("\t\t");
        for (int j = 0; j < 3; j++)
        {
            // Print - if number is 0
            sudoku[i][j][0] ? printf("%d ", sudoku[i][j][0]) : printf("- ");
        }
        printf("|");
        for (int j = 3; j < 6; j++)
        {
            sudoku[i][j][0] ? printf("%d ", sudoku[i][j][0]) : printf("- ");
        }
        printf("|");
        for (int j = 6; j < 9; j++)
        {
            sudoku[i][j][0] ? printf("%d ", sudoku[i][j][0]) : printf("- ");
        }
        printf("\n");
    }
    printf("\t\t------|------|------\n");
    // For rows 4 to 6
    for (int i = 3; i < 6; i++)
    {
        printf("\t\t");
        for (int j = 0; j < 3; j++)
        {
            sudoku[i][j][0] ? printf("%d ", sudoku[i][j][0]) : printf("- ");
        }
        printf("|");
        for (int j = 3; j < 6; j++)
        {
            sudoku[i][j][0] ? printf("%d ", sudoku[i][j][0]) : printf("- ");
        }
        printf("|");
        for (int j = 6; j < 9; j++)
        {
            sudoku[i][j][0] ? printf("%d ", sudoku[i][j][0]) : printf("- ");
        }
        printf("\n");
    }
    printf("\t\t------|------|------\n");
    // For rows 7 to 9
    for (int i = 6; i < 9; i++)
    {
        printf("\t\t");
        for (int j = 0; j < 3; j++)
        {
            sudoku[i][j][0] ? printf("%d ", sudoku[i][j][0]) : printf("- ");
        }
        printf("|");
        for (int j = 3; j < 6; j++)
        {
            sudoku[i][j][0] ? printf("%d ", sudoku[i][j][0]) : printf("- ");
        }
        printf("|");
        for (int j = 6; j < 9; j++)
        {
            sudoku[i][j][0] ? printf("%d ", sudoku[i][j][0]) : printf("- ");
        }
        printf("\n");
    }
    printf("\n\n");
}

// Function that returns true if same number not found in row, column, or block
bool valid_num(int num, int r, int c)
{
    // Check for same number in column
    int count = 0;
    for (int i = 0; i < 9; i++)
    {

        if (num == sudoku[i][c][0])
        {
            count++;
        }
    }
    if (count > 1)
    {
        return false;
    }
    // Check for same number in row
    count = 0;
    for (int i = 0; i < 9; i++)
    {

        if (num == sudoku[r][i][0])
        {
            count++;
        }
    }
    if (count > 1)
    {
        return false;
    }
    // Check for same number in block
    count = 0;
    // Loop through block
    for (int i = r - r % 3, end1 = (r - r % 3) + 3; i < end1; i++)
    {
        for (int j = c - c % 3, end2 = (c - c % 3) + 3; j < end2; j++)
        {
            if (num == sudoku[i][j][0])
            {
                count++;
            }
        }
    }
    if (count > 1)
    {
        return false;
    }
    return true;
}

// Function to check validity of sudoku puzzle
bool valid_puzzle(void)
{
    // Loop through the puzzle
    for (int i = 0; i < 9; i++)
    {
        for (int j = 0; j < 9; j++)
        {
            // Skip zeroes
            if (sudoku[i][j][0] == 0)
            {
                continue;
            }
            // Check if all numbers are at valid positions
            if (!valid_num(sudoku[i][j][0], i, j))
            {
                return false;
            }
        }
    }
    return true;
}

// Function to fill or update possibilities in all spaces
void fill_possibilities(void)
{
    // Loop through the grid
    for (int i = 0; i < 9; i++)
    {
        for (int j = 0; j < 9; j++)
        {
            // Skip spaces that are already filled
            if (sudoku[i][j][0] != 0)
            {
                continue;
            }
            // Clear existing possibilities
            for (int k = 1; k < 10; k++)
            {
                sudoku[i][j][k] = 0;
            }
            // Analyze and fill the possibilities in the 3rd dimension
            // Keep track of possibilities
            bool possibilities[9] = {true, true, true, true, true, true, true, true, true};
            // Check for a number in column
            for (int k = 0; k < 9; k++)
            {
                // Skip zeros
                if (sudoku[k][j][0] == 0)
                {
                    continue;
                }
                // Any number found in same row, column or block should become false
                // in the possibilities array
                possibilities[sudoku[k][j][0] - 1] = false;
            }
            // Check for a number in row
            for (int k = 0; k < 9; k++)
            {
                // Skip zeros
                if (sudoku[i][k][0] == 0)
                {
                    continue;
                }
                possibilities[sudoku[i][k][0] - 1] = false;
            }
            // Check for number in block
            // Loop through block
            for (int k = i - i % 3, end1 = (i - i % 3) + 3; k < end1; k++)
            {
                for (int l = j - j % 3, end2 = (j - j % 3) + 3; l < end2; l++)
                {
                    // Skip zeros
                    if (sudoku[k][l] == 0)
                    {
                        continue;
                    }
                    possibilities[sudoku[k][l][0] - 1] = false;
                }
            }
            // Fill possibilities for that space
            for (int k = 1; k < 10; k++)
            {
                // Fill the number if it is true
                if (possibilities[k - 1])
                {
                    sudoku[i][j][k] = k;
                }
            }
        }
    }
}
// Function that returns the number of blank spaces left
int check_progress(void)
{
    int count = 0;
    // Loop through puzzle
    for (int i = 0; i < 9; i++)
    {
        for (int j = 0; j < 9; j++)
        {
            if (sudoku[i][j][0] == 0)
            {
                count++;
            }
        }
    }
    return count;
}

// Fill all naked singles
void naked_singles(void)
{
    // Loop through puzzle
    for (int i = 0; i < 9; i++)
    {
        for (int j = 0; j < 9; j++)
        {
            int count = 0, num = 0;
            // Count possibilities
            for (int k = 1; k <= 9; k++)
            {
                if (sudoku[i][j][k] != 0)
                {
                    num = sudoku[i][j][k];
                    count++;
                }
            }
            if (count == 1)
            {
                sudoku[i][j][0] = num;
            }
        }
    }
}

// Fill all hidden singles
void hidden_singles(void)
{
    // Check all rows
    for (int i = 0; i < 9; i++)
    {
        for (int k = 1; k <= 9; k++)
        {
            int count = 0, check_r = 0, check_c = 0, num = 0;
            // Check for single existence of each possibility in a given row
            for (int j = 0; j < 9; j++)
            {
                // Skip spaces already filled
                if (sudoku[i][j][0] != 0)
                {
                    continue;
                }
                // Save the last instance of where the probability occurs
                if (sudoku[i][j][k] == k)
                {
                    check_r = i;
                    check_c = j;
                    num = k;
                    count++;
                }
            }
            // If that possibility occurs only a single time in any row, then place it
            if (count == 1)
            {
                sudoku[check_r][check_c][0] = num;
            }
        }
    }
    // Check all columns
    for (int j = 0; j < 9; j++)
    {
        for (int k = 1; k <= 9; k++)
        {
            int count = 0, check_r = 0, check_c = 0, num = 0;
            // Check for single existence of each possibility in each column
            for (int i = 0; i < 9; i++)
            {
                // Skip spaces already filled
                if (sudoku[i][j][0] != 0)
                {
                    continue;
                }
                // Save the last instance of where the probability occurs
                if (sudoku[i][j][k] == k)
                {
                    check_r = i;
                    check_c = j;
                    num = k;
                    count++;
                }
            }
            // If that possibility occurs only a single time in any column, then place it
            if (count == 1)
            {
                sudoku[check_r][check_c][0] = num;
            }
        }
    }
    // Check all 9 blocks
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            for (int m = 1; m <= 9; m++)
            {
                int count = 0, check_r = 0, check_c = 0, num = 0;
                for (int k = (i * 3); k < ((i * 3) + 3); k++)
                {
                    for (int l = (j * 3); l < ((j * 3) + 3); l++)
                    {
                        // Skip spaces already filled
                        if (sudoku[k][l][0] != 0)
                        {
                            continue;
                        }
                        // Check for single existence of each possibility in each block
                        // Save the last instance of where the possibility occurs
                        if (sudoku[k][l][m] == m)
                        {
                            check_r = k;
                            check_c = l;
                            num = m;
                            count++;
                        }
                    }
                }
                // If that possibility occurs only a single time in any block, then place it
                if (count == 1)
                {
                    sudoku[check_r][check_c][0] = num;
                }
            }
        }
    }
}

// Function that looks for naked pairs
void naked_pairs(void)
{
    // Loop through puzzle
    for (int i = 0; i < 9; i++)
    {
        for (int j = 0; j < 9; j++)
        {
            // Look for spaces with a pair
            int count = 0;
            for (int k = 1; k <= 9; k++)
            {
                if (sudoku[i][j][k] == k)
                {
                    count++;
                }
            }
            // If a pair is found
            if (count == 2)
            {
                // Look for another space having same pair in same row, column or block
                // Check row
                for (int l = 0; l < 9; l++)
                {
                    count = 0;
                    for (int k = 1; k <= 9; k++)
                    {
                        if (sudoku[i][l][k] == k && (l != j))
                        {
                            count++;
                        }
                    }
                    // Another pair found in same row
                    if (count == 2)
                    {
                        count = 0;
                        // Check if possibilities are the same
                        for (int k = 1; k <= 9; k++)
                        {
                            if (sudoku[i][j][k] == sudoku[i][l][k] && (sudoku[i][j][k] != 0))
                            {
                                count++;
                            }
                        }
                        // If another pair found
                        if (count == 2)
                        {
                            // Remove all such possibilities from row
                            for (int k = 1; k <= 9; k++)
                            {
                                if ((sudoku[i][j][k] == k))
                                {
                                    for (int m = 0; m < 9; m++)
                                    {
                                        if (m != j && m != l)
                                        {
                                            sudoku[i][m][k] = 0;
                                        }
                                    }
                                }
                            }
                            break;
                        }
                    }
                }
                // Check column
                for (int l = 0; l < 9; l++)
                {
                    count = 0;
                    for (int k = 1; k <= 9; k++)
                    {
                        if (sudoku[l][j][k] == k && (i != l))
                        {
                            count++;
                        }
                    }
                    // Another pair found in same column
                    if (count == 2)
                    {
                        count = 0;
                        // Check if possibilities are the same
                        for (int k = 1; k <= 9; k++)
                        {
                            if (sudoku[i][j][k] == sudoku[l][j][k] && (sudoku[i][j][k] != 0))
                            {
                                count++;
                            }
                        }
                        // If another pair found
                        if (count == 2)
                        {
                            // Remove all such possibilities from column
                            for (int k = 1; k <= 9; k++)
                            {
                                if ((sudoku[i][j][k] == k))
                                {
                                    for (int m = 0; m < 9; m++)
                                    {
                                        if (m != i && m != l)
                                        {
                                            sudoku[m][j][k] = 0;
                                        }
                                    }
                                }
                            }
                            break;
                        }
                    }
                }
                // Check block
                for (int row = i - i % 3; row < (i - i % 3) + 3; row++)
                {
                    for (int col = j - j % 3; col < (j - j % 3) + 3; col++)
                    {
                        count = 0;
                        for (int k = 1; k <= 9; k++)
                        {
                            if (sudoku[row][col][k] == k && (row != i || col != j))
                            {
                                count++;
                            }
                        }
                        // Another pair found in same block
                        if (count == 2)
                        {
                            count = 0;
                            // Check if possibilities are the same
                            for (int k = 1; k <= 9; k++)
                            {
                                if (sudoku[i][j][k] == sudoku[row][col][k] && (sudoku[i][j][k] != 0))
                                {
                                    count++;
                                }
                            }
                            if (count == 2)
                            {
                                // Remove all such possibilities from block
                                for (int k = 1; k <= 9; k++)
                                {
                                    if (sudoku[i][j][k] == k)
                                    {
                                        for (int m = i - i % 3; m < (i - i % 3) + 3; m++)
                                        {
                                            for (int n = j - j % 3; n < (j - j % 3) + 3; n++)
                                            {
                                                if (m != i && n != j && m != row && n != col)
                                                {
                                                    sudoku[m][n][k] = 0;
                                                }
                                            }
                                        }
                                    }
                                }
                            }
                            break;
                        }
                    }
                }
            }
        }
    }
}


/***********************************************************************
// Function that looks for naked pairs
void naked_pairs(void)
{
    // Check all 9 blocks
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            for (int k = (i * 3); k < ((i * 3) + 3); k++)
            {
                for (int l = (j * 3); l < ((j * 3) + 3); l++)
                {
                    // Skip spaces already filled
                    if (sudoku[k][l][0] != 0)
                    {
                        continue;
                    }
                    int count = 0, check_r = 0, check_c = 0;
                    int pair[2] = {0};
                    // Look for space with two possibilities
                    for (int m = 1; m <= 9; m++)
                    {
                        // Skip possibility that doesn't exist
                        if (sudoku[k][l][m] == 0)
                        {
                            continue;
                        }
                        // Check for two possibilities and save them
                        if (sudoku[k][l][m] == m)
                        {
                            if (count < 2)
                            {
                                pair[count] = m;
                            }
                            count++;
                        }
                    }
                    // If pair found, look for another blank space having same pair
                    if (count == 2)
                    {
                        int check = 0;
                        // Save position
                        check_r = k, check_c = l;
                        // Check the remaining spaces
                        for (k++; k < (i + 3); k++)
                        {
                            for (l++; l < (j + 3); l++)
                            {
                                count = 0;
                                for (int m = 1; m <= 9; m++)
                                {
                                    // Skip possibility that doesn't exist
                                    if (sudoku[k][l][m] == 0)
                                    {
                                        continue;
                                    }
                                    // Look for same pair
                                    if (sudoku[k][l][m] == m && (m == pair[0] || m == pair[1]))
                                    {
                                        count++;
                                    }
                                }
                            }
                        }
                        // If pair found
                        if (count == 2)
                        {
                            // If pair in same row
                            if (check_r == k)
                            {
                                for (int m = 0; m < 9; m++)
                                {
                                    for (int n = 1; n <= 9; n++)
                                    {
                                        if (sudoku[k][m][n] == pair[0] || sudoku[k][m][n] == pair[1])
                                        {
                                            sudoku[k][m][n] = 0;
                                        }
                                    }
                                }
                            }
                            // If pair in same column
                            if (check_c == l)
                            {
                                for (int m = 0; m < 9; m++)
                                {
                                    for (int n = 1; n <= 9; n++)
                                    {
                                        if (sudoku[m][l][n] == pair[0] || sudoku[m][l][n] == pair[1])
                                        {
                                            sudoku[m][l][n] = 0;
                                        }
                                    }
                                }
                            }
                            // Remove these possibilities from all other spaces in block
                            for (int k = i; k < (i + 3); k++)
                            {
                                for (int l = j; l < (j + 3); l++)
                                {
                                    for (int m = 1; m <= 9; m++)
                                    {
                                        if (sudoku[k][l][m] == pair[0] || sudoku[k][l][m] == pair[1])
                                        {
                                            sudoku[k][l][m] = 0;
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
    }
}
*************************************************************/
