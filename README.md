# sudokuGame
A CLI version of the sudoku game

**Features**
* Randomly generated solvable sudoku puzzles every new game
* Input validity checking
* Three difficulty levels
* Record every move and save to "saves.txt"
* Replay (like a video) previous saves OR resume a previous game
* Undo a move
* Re-do an undone move

To compile: 

clang -o <pick-a-name> main.c
  
**replay/resume functions will return errors if the "saves.txt" file is missing
