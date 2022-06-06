// Function to undo a move that was saved on the stack
void undo()
{
    if (moves == 0)
    {
        printf("\nNo moves to undo...\n");
        return;
    }
    if (UNDOs < 0)
    {
        printf("\nNo moves to undo...\n");
        UNDOs = 0;
        return;
    }

    board[s.array[s.top - UNDOs].row][s.array[s.top - UNDOs].column] = s.array[s.top - UNDOs].ov;

    printf("\nUndone: %d, %d, %d\n", s.array[s.top].row, s.array[s.top].column, s.array[s.top].nv);

    UNDOs++;
    moves--;
    pop(&s);
}

// Function to re-do a move that has been un-done
void redo()
{
    if (UNDOs == 0)
    {
        printf("\nNo moves to re-do...\n");
        return;
    }
    UNDOs--;
    moves++;
    s.top++;

    board[s.array[s.top - UNDOs].row][s.array[s.top - UNDOs].column] = s.array[s.top - UNDOs].nv;

    printf("\nRe-done: %d, %d, %d\n", s.array[s.top].row, s.array[s.top].column, s.array[s.top].nv);
}