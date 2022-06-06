// Function to display a "board"
void display(int board[Ro][Co])
{
    printf("\n");
    for (int row = 0; row < 9; row++)
    {
        if (row % 3 == 0 && row != 0)
        {
            printf("---------------------\n");
        }
        for (int column = 0; column < 9; column++)
        {
            if (column % 3 == 0 && column != 0)
            {
                printf("| ");
            }
            printf("%d ", board[row][column]);
            // print row number next to each row
            if (column == 8)
            {
                printf(" %d", row);
            }
        }
        printf("\n");
    }
    printf("\n");
    // print column number at the bottom of each column
    for (int i = 0; i < 9; i++)
    {
        if (i % 3 == 0 && i != 0)
        {
            printf("| ");
        }
        printf("%d ", i);
    }
    printf("\n");
    printf("\n");
    printf("---------------------\n");
    printf("---------------------\n");
    printf("\n");
}
// Reduce the number of clues on a complete board to "num" (used to create various difficulty levels)
void reduce(int board[Ro][Co], int num)
{
    copy(solved, board);
    srand(time(0));
    int r;
    for (r = 101; r <= (181 - num); r++)
    {
        int row = (rand() % 9);
        int col = (rand() % 9);
        if (board[row][col] != 0)
        {
            board[row][col] = 0;
        }
        else
        {
            r--;
        }
    }
}
// Function that will not terminate until a solved board is produced
void generate(int board[Ro][Co])
{
    while (checkboard(solved) != 1)
    {
        init(board);
        fill(board);
        solvesudoku(0, 0, board);
    }
}
// Function used to ask the player the difficulty level wanted
void difficulty(int board[Ro][Co])
{
    while (1)
    {
        int choice = 0;
        printf("\nPick difficulty level from 1(easy), 2(medium), 3(hard), 4(demonstration): ");
        scanf("%d", &choice);
        if (choice == 1)
        {//There will be 50 clues on the puzzle
            reduce(board, 50);
            init(initialBoard);
            copy(board, initialBoard);
            break;
        }
        else if (choice == 2)
        {//There will be 35 clues on the puzzle
            reduce(board, 35);
            init(initialBoard);
            copy(board, initialBoard);
            break;
        }
        else if (choice == 3)
        {//There will be 25 clues on the puzzle
            reduce(board, 25);
            init(initialBoard);
            copy(board, initialBoard);
            break;
        }
        else if (choice == 4)
        {//Demonstration has 80 clues and only 1 missing
            reduce(board, 80);
            init(initialBoard);
            copy(board, initialBoard);
            break;
        }
        else
        {
            printf("Invalid choice, try again\n");
        }
    }
}
// Function used to make a move in the game, returns 1 if successful (success determined by validity of input provided by the player)
int makeMove(int board[Ro][Co])
{
    int r, c, v;
    while (1)
    {
        int choice = 0;
        printf("Give row coordinate: ");
        scanf("%d", &choice);
        if (choice < 0 || choice > 8)
        {
            printf("Invalid coordinate, try again\n");
        }
        else
        {
            r = choice;
            break;
        }
    }
    while (1)
    {
        int choice = 0;
        printf("Give column coordinate: ");
        scanf("%d", &choice);
        if (choice < 0 || choice > 8)
        {
            printf("Invalid coordinate, try again\n");
        }
        else
        {
            c = choice;
            break;
        }
    }
    while (1)
    {
        int choice = 0;
        printf("Give value: ");
        scanf("%d", &choice);
        if (choice < 1 || choice > 9)
        {
            printf("Invalid value, try again\n");
        }
        else
        {
            v = choice;
            break;
        }
    }
    if(initialBoard[r][c] != 0)
    {
        printf("\nThe coordinates selected contain an unchangeable value...\n");
        return 0;
    }
    if (checkInput(r, c, v, board) == 1)
    {
        t.row = r;
        t.column = c;
        t.ov = board[r][c];
        t.nv = v;
        board[r][c] = v;
        push(&s, &t);
        moves++;
        UNDOs = 0;
        return 1;
    }
    else
    {
        printf("Invalid value placement\n");
        return 0;
    }
}
// Function that will display a hint
void hint()
{
    while (1)
    {
        srand(time(0));
        int ro = (rand() % 9); // generate random number between 0 and 8
        int co = (rand() % 9); // generate random number between 0 and 8
        if (board[ro][co] != solved[ro][co])
        {
            printf("\n\nHINTS:\n\nRow: %d\nColumn: %d\nValue: %d\n", ro, co, solved[ro][co]);
            break;
        }
    }
}