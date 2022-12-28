#include "functions.c"

int main(void)
{
    // Welcome the user
    printf("\t********************************************************\n");
    printf("\t*                                                      *\n");
    printf("\t*                Sudoku Puzzle Solver                  *\n");
    printf("\t*                                                      *\n");
    printf("\t********************************************************\n");

    while (1)
    {
        // Keep taking input until the user enters a valid puzzle
        while (1)
        {
            // Call function to get sudoku from user
            get_sudoku();
            // Show user the sudoku entered
            printf("The sudoku you entered is: ");
            display_sudoku();
            // Call function to check validity of puzzle
            if (valid_puzzle())
            {
                break;
            }
            printf("The sudoku you entered is invalid.\n\n");
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
        }
        // Thank the user
        printf("\t_____________________________________________\n\n");
        printf("\tThank you for using the Sudoku Puzzle Solver!\n");
        printf("\t_____________________________________________\n\n");
        // Ask user if he wants to continue or exit
        printf("Would you like to solve a different puzzle?\n");
        printf("Enter Y/y to continue, enter any other key to exit: ");
        int choice;
        scanf(" %c", &choice);
        if (choice != 'y' && choice != 'Y')
        {
            break;
        }
        printf("\n\n");
    }
    return 0;
}
