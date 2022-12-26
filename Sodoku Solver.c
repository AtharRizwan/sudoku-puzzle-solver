#include "functions.c"

int main(void)
{
    // Welcome the user
    printf("\t\t********************************************************\n");
    printf("\t\t*                                                      *\n");
    printf("\t\t*                Sudoku Puzzle Solver                  *\n");
    printf("\t\t*                                                      *\n");
    printf("\t\t********************************************************\n");
    start:
    // Call function to get sudoku from user
    get_sudoku();
    // Show user the sudoku entered
    printf("The sudoku you entered is: ");
    display_sudoku();
    // Call function to check validity of puzzle
    if (!valid_puzzle())
    {
        printf("The sudoku you entered is invalid.\n\n");
        goto start;
    }

    // Call function to fill possibilities
    fill_possibilities();
    do
    {
        int initial_check = check_progress();
        // Fill naked singles
        naked_singles();
        // Fill hidden singles
        hidden_singles();
        int final_check = check_progress();
        // If no progress is made then break the loop
        if (final_check == initial_check)
        {
            break;
        }
        // End the loop when no blank spaces left
    } while (check_progress());
    
    // Solve the rest of the puzzle using backtracking and display it
    if (solve_sudoku())
    {
        printf("The solution is: \n");
        display_sudoku();
    }
    // If puzzle can not be solved
    else
    {
        printf("There is no possible solution\n\n");
        return 1;
    }
    return 0;
}
