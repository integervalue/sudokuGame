// Size of board (row and column)
const int Ro = 9;
const int Co = 9;
// Main game board that's used to play (declared globally for easier access)
int board[Ro][Co];
// Solution to main game board (declared globally for easier access)
int solved[Ro][Co];
//Copy of game board - used to keep track of unchangeabe values
int initialBoard[Ro][Co];
// Initial size of stack (increased as needed through realloc())
int MAX = 10;
// Save file
char *saveFILE = "saves.txt";
// Number of moves made
int moves = 0;
// Number of UNDOs
int UNDOs = 0;

void display(int board[Ro][Co]);
int menu();