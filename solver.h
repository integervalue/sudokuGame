// Function to copy the contents of one board to another
void copy(int copyFrom[Ro][Co], int copyTo[Ro][Co])
{
    for (int c = 0; c < 9; c++)
    {
        for (int r = 0; r < 9; r++)
        {
            copyTo[r][c] = copyFrom[r][c];
        }
    }
}
// Sudoku solver that uses a backtracking algorithm
void solvesudoku(int row, int column, int board[Ro][Co])
{
    if ((row > 8) && (checkboard(board) == 1)) // If the row number is greater than 8 and the board has only non-zero values than we have solved the board
    {
        init(solved);
        copy(board, solved);
        return;
    }
    if (board[row][column] != 0) // If the value filled at a cell is not zero than it is filled with some value from 1 to 9 hence we move further
    {
        if (column < 8)
        {
            solvesudoku(row, column + 1, board);
        }
        else
        {
            solvesudoku(row + 1, 0, board);
        }
    }
    else
    {
        int ctr; // This is a counter to check numbers from 1 to 9 whether the number can be filled in the cell or not
        for (ctr = 1; ctr <= 9; ctr++)
        { // We check row,column and the board
            if (checkInput(row, column, ctr, board) == 1)
            {
                board[row][column] = ctr;
                if (column < 8)
                {
                    solvesudoku(row, column + 1, board);
                }
                else
                {
                    solvesudoku(row + 1, 0, board);
                }
            }
        }
        board[row][column] = 0; // No valid number was found so we clean up and return to the caller.
    }
}