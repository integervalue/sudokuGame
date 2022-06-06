// Function that counts the number of non-blank lines in a file
// requires the name of the file to be passed through the string "saveFile"
int getNOfNBLines(char *saveFile)
{
    FILE *sF = fopen(saveFile, "r");
    int counter = 0;
    char line[1000];

    while (fgets(line, 1000, sF))
    {
        // To detect non-blank lines I decided to loop through each line in the file and check whether the first character is NOT a newline character.
        if (line[0] != '\n')
        {
            counter += 1;
            // To make sure that lines that only contain spaces or "tabs" are not counted, I decided to check whether each character of the line, is a space, excluding the newline character;
            // If the conditions are met, i.e. a line that only contains spaces is detected, the counter is decreased by one.
            int spacecounter = 0;
            for (int i = 0; i < strlen(line); ++i)
            {
                if (isspace(line[i]) == 0)
                {
                    spacecounter += 1;
                }
            }
            if ((strlen(line) - 1) == spacecounter)
            {
                counter -= 1;
            }
        }
    }

    fclose(sF);
    return counter;
}
// Function that will output save data to the "saves.txt" file
void save()
{
    int r, c;
    FILE *fp;
    fp = fopen(saveFILE, "a");
    for (r = 0; r < 9; r++)
    {
        for (c = 0; c < 9; c++)
        {
            fprintf(fp, "%d ", initialBoard[r][c]);
        }
    }
    fprintf(fp, "%d %d ", MAX, moves);
    for (r = 0; r < moves; r++)
    {
        fprintf(fp, "%d %d %d %d ", s.array[r].row, s.array[r].column, s.array[r].nv, s.array[r].ov);
    }
    fprintf(fp, "\n");

    fclose(fp);
}
// Function to re-do un-done moves in reverse() function and displaying the board every time (allows to re-watch a previously saved game)
void replay()
{
    if (moves == 0)
    {
        printf("No moves were made\n");
        return;
    }
    else
    {
        printf("Moves made: %d\n", moves);
        printf("\n\nGame start:\n");
    }
    for (int i = 0; i < moves; i++)
    {
        if (i > 0)
        {
            printf("\n\nMove: %d, %d, %d\n", s.array[i - 1].row, s.array[i - 1].column, s.array[i - 1].nv);
        }
        display(board);
        board[s.array[i].row][s.array[i].column] = s.array[i].nv;
        if (i == moves - 1)
        {
            printf("\n\nMove: %d, %d, %d\n", s.array[i].row, s.array[i].column, s.array[i].nv);
        }
    }
    display(board);
}
// Function to apply save data
void apply(char *data, int counter, int saves, int action)
{
    if (action != 1)
    {
        printf("\nDisplaying saved game %d of %d\n", counter + 1, saves);
    }
    if (counter != 0)
    {
        free(s.array);
    }
    char *p = strtok(data, " ");

    for (int r = 0; r < 9; r++)
    {
        for (int c = 0; c < 9; c++)
        {
            board[r][c] = atoi(p);
            p = strtok(NULL, " "); // moving along to the next token
        }
    }
    if(action == 1)
    {
        copy(board, initialBoard);
    }

    MAX = atoi(p);
    p = strtok(NULL, " "); // moving along to the next token
    moves = atoi(p);
    p = strtok(NULL, " "); // moving along to the next token
    init_stack(&s, MAX);

    for (int i = 0; i < moves; i++)
    {
        t.row = atoi(p);
        p = strtok(NULL, " "); // moving along to the next token
        t.column = atoi(p);
        p = strtok(NULL, " "); // moving along to the next token
        t.nv = atoi(p);
        p = strtok(NULL, " "); // moving along to the next token
        t.ov = atoi(p);
        p = strtok(NULL, " "); // moving along to the next token
        push(&s, &t);          // adding moves to stack
        if(action == 1)
        {
            board[t.row][t.column] = t.nv;
        }
    }
    if (action != 1)
    {
        replay();
        if (moves == 0)
        {
            display(board);
        }
    }
}
// Function to prevent double-saves (when choosing to resume a game and saving, the old save is deleted)
void rmDuplicates(int lineTOrm)
{
    int counter = 0;
    char line[200];
    int saves = getNOfNBLines(saveFILE);
    // storing save data
    char lines[saves][200];

    FILE *fp;
    fp = fopen(saveFILE, "r");

    while (fgets(line, 200, fp))
    {
        strcpy(lines[counter], line);
        counter++;
    }
    fclose(fp);

    fp = fopen(saveFILE, "w");
    for (int i = 0; i < saves; i++)
    {
        if (i == lineTOrm)
        {
            continue;
        }
        else
        {
            fprintf(fp, "%s", lines[i]);
        }
    }
    fclose(fp);
}
// Function that loads data from "saves.txt", action=1 means "load and resume" and action!=1 means "load and watch"
void load(int action, int board[Ro][Co])
{
    int counter = 0;
    char line[200];
    int saves = getNOfNBLines(saveFILE);
    if (saves == 0)
    {
        printf("\nNo saved games were found...\n");
        return;
    }
    // storing save data
    char lines[saves][200];
    // copy of stored data since strtok() is destructive
    char temp[saves][200];

    FILE *fp;
    fp = fopen(saveFILE, "r");

    while (fgets(line, 200, fp))
    {
        if (action == 1)
        {
            strcpy(temp[counter], line);
            strcpy(lines[counter], line);
        }
        else
        {
            apply(line, counter, saves, action);
        }
        counter++;
    }
    fclose(fp);

    if (action == 1 && saves > 0)
    {
        printf("\nHere are the saves found: \n");
        int choices;
        for (choices = 0; choices < saves; choices++)
        {
            char *p = strtok(temp[choices], " ");

            printf("\n\nSave number: %d\n", choices + 1);
            init(board);
            for (int r = 0; r < 9; r++)
            {
                for (int c = 0; c < 9; c++)
                {
                    board[r][c] = atoi(p);
                    p = strtok(NULL, " "); // moving along to the next token
                }
            }
            display(board);
        }
        while (1)
        {
            printf("\nWhich saved game would you like to resume?(the greatest number is the latest save) ");
            int choice = 0;
            scanf("%d", &choice);
            if (choice < 1 || choice > choices)
            {
                printf("\nInvalid choice, try again\n");
                choice = 0;
            }
            else
            {
                apply(lines[choice - 1], counter, saves, action);
                solvesudoku(0, 0, board);
                rmDuplicates(choice - 1);
                break;
            }
        }
    }
}