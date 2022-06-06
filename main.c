#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <ctype.h>
#include <string.h>
#include "declarations.h"
#include "checking.h"
#include "stack.h"
#include "undo.h"
#include "generate.h"
#include "solver.h"
#include "replay.h"
#include "board.h"

int main()
{
    printf("\t\t\t  ___                           \n");
    printf("\t\t\t |             |      | /       \n");
    printf("\t\t\t |___        __|  __  |/        \n");
    printf("\t\t\t     | |  | |  | |  | |\\  |  | \n");
    printf("\t\t\t  ___| |__| |__| |__| | \\ |__| \n\n");
    printf("\n");

    int ans;
    if (menu() == 1)
    {
        printf("Would you like to save? (1 for yes) ");
        scanf("%d", &ans);
        if (ans == 1)
        {
            save();
        }

        return 0;
    }
}
// Function to display the rules
void rules()
{
    printf("\n\n\t\t\t\tRULES:\n\n");
    printf("1) Each row must contain the numbers from 1 to 9, without repetition.\n");
    printf("2) Each column must contain the numbers from 1 to 9, without repetition.\n");
    printf("3) Each 3x3 local block must contain the numbers from 1 to 9, without repetition.\n\n\n\n");
}
// Function that allows to progress inside the game
void game()
{
    while (1)
    {
        printf("\n");
        printf("\n");
        display(board);

        int choice = 0;
        printf("\nPick next move from 1(make a move), 2(surrender), 3(get a hint), 4(show the solution), 5(undo), 6(re-do), 7(show rules): ");
        scanf("%d", &choice);
        if (choice == 1)
        {
            makeMove(board);
            if (checkboard(board) == 1)
            {
                break;
            }
        }
        else if (choice == 2)
        {
            break;
        }
        else if (choice == 3)
        {
            hint();
        }
        else if (choice == 4)
        {
            display(solved);
        }
        else if (choice == 5)
        {
            undo();
        }
        else if (choice == 6)
        {
            redo();
        }
        else if (choice == 7)
        {
            rules();
        }
        else
        {
            printf("Invalid choice, try again\n");
        }
    }
}
// Menu displayed at the start of the program
int menu()
{
    int saving = 1;
    while (1)
    {
        int choice = 0;
        printf("\nWhat would you like to do? 1(new game), 2(load and watch), 3(load and resume), 4(quit): ");
        scanf("%d", &choice);
        if (choice == 1)
        {
            init_stack(&s, MAX);
            generate(board);
            difficulty(board);
            game();
            break;
        }
        else if (choice == 2)
        {
            load(2, board);
        }
        else if (choice == 3)
        {
            if (getNOfNBLines(saveFILE) != 0)
            {
                load(1, board);
                saving = 0;
                game();
                save();
                break;
            }
            else
            {
                printf("\nNo saved games were found...\n");
            }
        }
        else if (choice == 4)
        {
            return 0;
        }
        else
        {
            printf("Invalid choice, try again\n");
        }
    }
    // Check for game over
    if (checkboard(board) == 1)
    {
        printf("\n");
        printf("\n");
        printf("You Win\n\n");
        display(board);
    }
    else
    {
        printf("\nHere is your progress so far: \n\n");
        display(board);
    }
    return saving;
}