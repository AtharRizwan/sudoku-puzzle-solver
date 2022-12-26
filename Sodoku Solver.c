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
        fill_possibilities();
        // Fill hidden singles
        hidden_singles();
        fill_possibilities();
        // Find naked pairs
        naked_pairs();
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
    } while (check_progress());
    
    // The puzzle is unsolvable if blank spaces still left
    if (check_progress())
    {
        display_sudoku();
        printf("There is no possible solution.\n\n");
        return 1;
    }
    printf("The solution is: ");
    display_sudoku();
    return 0;
}
