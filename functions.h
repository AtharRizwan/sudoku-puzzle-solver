#include <stdio.h>
#include <stdbool.h>
#define GRID_SIZE 9
int sudoku[GRID_SIZE][GRID_SIZE][10] = { 0 };

/***********************************************************************************************
 * get_sudoku : Allows the user to enter a sudoku puzzle row wise.                             *
 *              The user will have to enter a stream of number without spaces.                 *
 *              The user should press enter after each row.                                    *
 *              0s will be considered as blank spaces.                                         *
 ***********************************************************************************************/
void get_sudoku(void)
{
    printf("Enter a sudoku puzzle row wise(0 for blank space).\n");
    printf("A stream of numbers (without spaces) should be entered.\n");
    printf("Any characters or extra numbers will be ignored.\n");
    // Take inputs in the sudoku global array
    for (int i = 0; i < GRID_SIZE; i++)
    {
        // Tell user the row number
        printf("Enter row %d: ", i + 1);
        for (int j = 0; j < GRID_SIZE; j++)
        {
            // Take input correctly
            char input;
            do 
            {
                input = getchar();
            } while (input < '0' || input > '9');
            // Store input
            sudoku[i][j][0] = input - '0';
        }
        // Ignore any extra numbers
        while ((getchar()) != '\n');
    }
}

/***********************************************************************************************
 * display_sudoku : Displays the sudoku grid in a suitable way.                                *
 *                  It will display hyphen(-) for blank spaces.                                *
 ***********************************************************************************************/
void display_sudoku(void)
{
    printf("\n\n");
    // For rows 1 to 3
    for (int i = 0; i < 3; i++)
    {
        printf("\t\t");
        for (int j = 0; j < 3; j++)
        {
            // Print hyphen(-) if number is 0
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

/******************************************************************************************
 * valid_num : Checks whether a specific number(num) at row(r) and column(c) is valid.    *
 *             It will return true if number is valid, else false.                        *
 *             For a number to be valid, it must occur only once in a specific            *
 *             row, column or block.                                                      *
 ******************************************************************************************/
bool valid_num(int num, int r, int c)
{
    // Check for same number in column
    int count = 0;
    for (int i = 0; i < GRID_SIZE; i++)
    {

        if (num == sudoku[i][c][0])
        {
            count++;
        }
    }
    // If number occurs more than once, return false
    if (count > 1)
    {
        return false;
    }
    // Check for same number in row
    count = 0;
    for (int i = 0; i < GRID_SIZE; i++)
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

/**************************************************************************************
 * valid_puzzle : Checks whether each number of the puzzle is valid.                  *
 *                If even a single number is invalid, it will return false,           *
 *                else true.                                                          *
 **************************************************************************************/
// Function to check validity of sudoku puzzle
bool valid_puzzle(void)
{
    // Loop through the puzzle
    for (int i = 0; i < GRID_SIZE; i++)
    {
        for (int j = 0; j < GRID_SIZE; j++)
        {
            // Skip zeroes
            if (sudoku[i][j][0] == 0)
            {
                continue;
            }
            // Check if all numbers are at valid positions
            // Even a single number should not be invalid
            if (!valid_num(sudoku[i][j][0], i, j))
            {
                return false;
            }
        }
    }
    // Return true if all numbers are valid
    return true;
}

/***********************************************************************************************
 * fill_possibilities : Fills all the possibilities for each cell in the 3rd dimension.        *
 *                      e.g. if a cell at [i][j] has the possibilities of 1 and 5, then        *
 *                      sudoku[i][j][1] == 1, and sudoku[i][j][5] == 5.                        *
 *                      A number that is not present in the same row, column or block          *
 *                      will be considered as a possibility of that cell.                      *
 ***********************************************************************************************/
void fill_possibilities(void)
{
    // Loop through the grid
    for (int i = 0; i < GRID_SIZE; i++)
    {
        for (int j = 0; j < GRID_SIZE; j++)
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
            for (int k = 0; k < GRID_SIZE; k++)
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
            for (int k = 0; k < GRID_SIZE; k++)
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
                    if (sudoku[k][l][0] == 0)
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

/********************************************************************************************
 * update_possibilities : This function remove all possibilities of cell at row and col     *
 *                        and removes all possibilities equal to num from the same          *
 *                        row, column and block.                                            *
 *                        This should be called whenever a number is placed.                *
 ********************************************************************************************/
void update_possiblities(int row, int col, int num)
{
    // removes the possiblities of a recently placed number
    for (int i = 1; i < 10; i++)
    {
        sudoku[row][col][i] = 0;
    }

    // removes possibilities equal to num from row
    for (int changing_row = 0; changing_row < 9; changing_row++)
    {
        sudoku[changing_row][col][num] = 0;
    }

    // removes possibilities equal to num from column
    for (int changing_col = 0; changing_col < 9; changing_col++)
    {
        sudoku[row][changing_col][num] = 0;
    }

    // removes possibilities equal to num from block
    for (int changing_row = row - row % 3; changing_row < (row - row % 3) + 3; changing_row++)
    {
        for (int changing_col = col - col % 3; changing_col < (col - col % 3) + 3; changing_col++)
        {
            sudoku[changing_row][changing_col][num] = 0;
        }
    }
}

/***********************************************************************************
 * check_progress : Returns the number of blank spaces left in the puzzle.         *
 *                  A blank space is indicated by 0.                               *
 *                  If no blank space left, then the puzzle is solved.             *
 ***********************************************************************************/
int check_progress(void)
{
    int count = 0;
    // Loop through puzzle
    for (int i = 0; i < GRID_SIZE; i++)
    {
        for (int j = 0; j < GRID_SIZE; j++)
        {
            // Count the number of blanks
            if (sudoku[i][j][0] == 0)
            {
                count++;
            }
        }
    }
    return count;
}

/*******************************************************************************
 * apparent_singles : Fills all the apparent singles in the puzzle.                  *
 *                 A cell has a apparent single if it has only                    *
 *                 a single possibility.                                       *
 *******************************************************************************/
void apparent_singles(void)
{
    // Loop through puzzle
    for (int i = 0; i < GRID_SIZE; i++)
    {
        for (int j = 0; j < GRID_SIZE; j++)
        {
            int count = 0, num = 0;
            // Count possibilities
            for (int k = 1; k <= 9; k++)
            {
                if (sudoku[i][j][k] != 0)
                {
                    // Keep track of possibilities
                    num = sudoku[i][j][k];
                    count++;
                }
            }
            // If there is only one, possibility, then fill it
            if (count == 1)
            {
                sudoku[i][j][0] = num;
                // Update possibilities
                update_possiblities(i, j, num);
            }
        }
    }
}

/*************************************************************************************************
 * hidden_singles : Fills all the hidden singles.                                                *
 *                  A cell is said to have a hidden single if only that cell has                 *
 *                  a certain possibility in a given row, column or block.                       *
 *************************************************************************************************/
void hidden_singles(void)
{
    // Check all rows
    for (int i = 0; i < GRID_SIZE; i++)
    {
        for (int k = 1; k <= GRID_SIZE; k++)
        {
            int count = 0, check_r = 0, check_c = 0, num = 0;
            // Check for single existence of each possibility in a given row
            for (int j = 0; j < GRID_SIZE; j++)
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
                update_possiblities(check_r, check_c, num);
            }
        }
    }
    // Check all columns
    for (int j = 0; j < GRID_SIZE; j++)
    {
        for (int k = 1; k <= 9; k++)
        {
            int count = 0, check_r = 0, check_c = 0, num = 0;
            // Check for single existence of each possibility in each column
            for (int i = 0; i < GRID_SIZE; i++)
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
                update_possiblities(check_r, check_c, num);
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
                    // Update possibilities
                    update_possiblities(check_r, check_c, num);
                }
            }
        }
    }
}

/*************************************************************************************************
 * Naked Pairs : This function looks for two cells having the same two possibilities             *
 *               in a given block, row, or column and removes those possibilities from           *
 *               all others cells in the same row, block or column.                              *
 *************************************************************************************************/
// Function that looks for apparent pairs
void apparent_pairs(void)
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

/****************************************************************************
 * in_row : Checks if a number is already present in a particular row.      *
 ****************************************************************************/
bool in_row(int row, int num)
{
    // Got through the given row, checking for the number
    for (int col = 0; col < GRID_SIZE; col++)
    {
        if (sudoku[row][col][0] == num)
        {
            // Return true if number is already present
            return true;
        }
    }
    // Return false if number is not present
    return false;
}

/****************************************************************************
 * in_col : Checks if a number is already present in a particular column    *
 ****************************************************************************/
bool in_col(int col, int num)
{
    // Got through the given column, checking for the number
    for (int row = 0; row < GRID_SIZE; row++)
    {
        if (sudoku[row][col][0] == num)
        {
            return true;
        }
    }
    return false;
}

/****************************************************************************
 * in_block : Checks if a number is already present in a particular block   *
 ****************************************************************************/
bool in_block(int start_row, int start_col, int num)
{
    // Got through the given block, checking for the number
    for (int row = 0; row < 3; row++)
    {
        for (int col = 0; col < 3; col++)
        {
            if (sudoku[row + start_row][col + start_col][0] == num)
            {
                return true;
            }
        }
    }
    return false;
}

/****************************************************************************
 * is_safe : Checks if a number is safe to place at a particular blank      *
 *           A number will only be safe to place if it is not already       *
 *           present in corresponding row, block or column.                 *
 ****************************************************************************/
bool is_safe(int row, int col, int num)
{
    // Check if the number is already present in the current row
    if (in_row(row, num))
        return false;

    // Check if the number is already present in the current column
    if (in_col(col, num))
        return false;

    // Check if the number is already present in the current 3x3 box
    if (in_block(row - row % 3, col - col % 3, num))
        return false;

    // The number is not present in the current row, column, or box,
    // so it is safe to place it at (row, col)
    return true;
}

/***********************************************************************************
 * find_blank : Finds a blank space.                                               *
 *              Returns true if a blank space if found, else returns false.        *
 *              It takes the memory addresses of row and col, and modifies the     *
 *              values present in those memory addresses.                          *
 ***********************************************************************************/
bool find_blank(int *row, int *col)
{
    for (*row = 0; *row < GRID_SIZE; (*row)++)
    {
        for (*col = 0; *col < GRID_SIZE; (*col)++)
        {
            if (sudoku[*row][*col][0] == 0)
            {
                return true;
            }
        }
    }
    return false;
}

/*********************************************************************************************
 * solve_sudoku : It is a recursive function.                                                *
 *                If a puzzle is unsolvable by applied conventional methods,                 *
 *                this function will try and solve it using backtracking.                    *
 *                It will take the first blank space and place 1 there. Then                 *
 *                it will try solving the rest of the puzzle using this assumption.          *
 *                If this assumption leads to a contradiction, it will backtrack             *
 *                and remove the number that it previously placed.                           *
 *                Like this, it will try all numbers from 1 to 9 for each blank space.       *
 *                It will return true, if no blank space is left.                            *
 *                If it is unable to solve the puzzle using any number, it will              *
 *                return false.                                                              *
 *********************************************************************************************/
bool solve_sudoku(void)
{
    int row, col;
    // If there are no unassigned locations, the puzzle is solved
    if (!find_blank(&row, &col))
    {
        return true;
    }

    // Try all numbers from 1 to 9
    for (int num = 1; num <= 9; num++)
    {
        // Check if it's safe to place the number at (row, col)
        if (is_safe(row, col, num))
        {
            // Place the number at (row, col)
            sudoku[row][col][0] = num;

            // Solve the rest of the puzzle
            if (solve_sudoku())
            {
                return true;
            }
            // If the puzzle cannot be solved, remove the number from (row, col)
            // and try the next number
            sudoku[row][col][0] = 0;
        }
    }
    // If no number from 1 to 9 can be placed at (row, col) and the puzzle
    // cannot be solved, return false
    return false;
}
