// Function that checks the input "num" for validity according to sudoku rules, ("row" and "column" are coordinates of a given "board"), returns 1 if successful
int checkInput(int row, int column, int num, int board[Ro][Co])
{
    int r, c;
    // check column
    for (r = 0; r < 9; r++)
    {
        if (board[r][column] == num)
        {
            return 0;
        }
    }
    // check row
    for (c = 0; c < 9; c++)
    {
        if (board[row][c] == num)
        {
            return 0;
        }
    }
    // check 3x3 local grid
    r = row - row % 3;
    c = column - column % 3;

    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            if (board[i + r][j + c] == num)
            {
                return 0;
            }
        }
    }
    return 1;
}
// Function that returns 1 if all vallues of "board" are non-zero
int checkboard(int board[Ro][Co])
{
    int r, c;
    for (r = 0; r < 9; r++)
    {
        for (c = 0; c < 9; c++)
        {
            if (board[r][c] == 0)
            {
                return 0;
            }
        }
    }
    return 1;
}