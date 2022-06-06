// Function that initializes a "board"
void init(int board[Ro][Co])
{
    for (int r = 0; r < 9; r++)
    {
        for (int c = 0; c < 9; c++)
        {
            board[r][c] = 0;
        }
    }
}
// Function that fills a "board" with valid values according to sudoku rules (doesn't guarantee solvability)
void fill(int board[Ro][Co])
{
    srand(time(0));
    int i;
    for (i = 0; i < 23; i++)
    {
        int co = (rand() % 9);
        int ro = (rand() % 9);
        int num = ((rand() % 9) + 1);

        if ((board[ro][co] == 0) && (checkInput(ro, co, num, board) == 1))
        {
            board[ro][co] = num;
        }
        else
        {
            i--;
        }
    }
}