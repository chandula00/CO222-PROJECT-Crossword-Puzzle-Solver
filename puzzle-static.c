#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SIZE_ROW 100
#define SIZE_COLUMN 100

int grid_Height;
int grid_Width;
int num_word;
int V_Flag[50];
int H_Flag[50];

char **Horizontal_LR(int x, int y, char **grid, char *SelectedWord, int index);
char **Horizontal_RL(int x, int y, char **grid, char *SelectedWord, int index);
char **Vertical_UD(int x, int y, char **grid, char *SelectedWord, int index);
char **Vertical_DU(int x, int y, char **grid, char *SelectedWord, int index);
int length(char *word);
int PuzzleSolver(char **grid, char **word, int wordIndex);
int printgrid(char **grid);

int main()
{
    int row_grid = 0;
    int column_grid = 0;

    int row_word = 0;
    int column_word = 0;

    char grid[SIZE_ROW][SIZE_COLUMN] = {{}, {}};
    static char word[SIZE_ROW][SIZE_COLUMN] = {{}, {}};

    for (; scanf("%[^\n]%*c", grid[row_grid]) == 1; row_grid++)
    {
        fflush(stdin);
        grid_Height = row_grid;
        for (column_grid = 0; grid[row_grid][column_grid] != '\0'; column_grid++)
        {
            if (!(grid[row_grid][column_grid] == '#' ||
                  grid[row_grid][column_grid] == '*' ||
                  (grid[row_grid][column_grid] >= 'A' && grid[row_grid][column_grid] <= 'Z') ||
                  (grid[row_grid][column_grid] >= 'a' && grid[row_grid][column_grid] <= 'z')))
            {
                printf("INVALID INPUT");
                exit(0);
            }
        }
        if (grid_Width < column_grid)
        {
            grid_Width = column_grid;
        }
    }

    fflush(stdin);

    for (; scanf("%[^\n]%*c", word[row_word]) == 1; row_word++)
    {
        num_word = row_word;
        fflush(stdin);
        for (column_word = 0; word[row_word][column_word] != '\0'; column_word++)
        {
            if (!((word[row_word][column_word] >= 'A' && word[row_word][column_word] <= 'Z') ||
                  (word[row_word][column_word] >= 'a' && word[row_word][column_word] <= 'z')))
            {
                printf("INVALID INPUT");
                exit(0);
            }
        }
    }

    PuzzleSolver((char **)grid, (char **)word, 0);

    for (int i = 0; i < row_grid + 1; i++)
    {
        printf(grid[i]);
        putchar('\n');
    }

    for (int i = 0; i < row_word + 1; i++)
    {
        printf(word[i]);
        putchar('\n');
    }

    return 0;
}

char **Horizontal_LR(int x, int y, char **grid, char *SelectedWord, int index)
{
    int n = length((char *)SelectedWord);
    printf("NOW in horizontal\n");
    for (int i = 0; i < n; i++)
    {
        if (grid[x + i][y] == '#' ||
            grid[x + i][y] == SelectedWord[i])
        {
            grid[x + i][y] = SelectedWord[i];
        }
        else
        {

            // this shows that word
            // cannot be placed vertically
            grid[0][0] = '$';
            H_Flag[index] = 2;
            return grid;
        }
    }
    return grid;
}

char **Vertical_UD(int x, int y, char **grid, char *SelectedWord, int index)
{
    int n = length((char *)SelectedWord);
    for (int i = 0; i < n; i++)
    {
        if (grid[x][y + i] == '#' ||
            grid[x][y + i] == SelectedWord[i])
        {
            grid[x][y + i] = SelectedWord[i];
        }
        else
        {

            // this shows that word
            // cannot be placed vertically
            grid[0][0] = '$';
            V_Flag[index] = 2;
            if (H_Flag[index] == 2)
            {
                printf("IMPOSSIBLE");
                exit(0);
            }
            return grid;
        }
    }
    return grid;
}

int length(char *word)
{
    int length = 0;
    printf("now in length\n");
    printf("%s", word[0]);
    putchar('\n');
    while (word[length] != '\0')
    {
        length++;
        printf("%d\n", length);
    }
    return length;
}

int PuzzleSolver(char **grid, char **word, int wordIndex)
{
    if (wordIndex < num_word)
    {
        printf("Now in puzzle solver\n");
        printf("%s\n", word[wordIndex]);
        char *SelectedWord = word[wordIndex];
        int word_Length = length(SelectedWord);
        printf("%d\n %d\n", word_Length, grid_Height);
        int StartIndex_Vertical = grid_Height - word_Length;
        int StartIndex_Horizontal = grid_Width - word_Length;

        for (int row = 0; row < grid_Height; row++)
        {
            for (int column = 0; column <= StartIndex_Horizontal; column++)
            {
                char **temp_grid = Horizontal_LR(row, column, (char **)grid, (char *)SelectedWord, wordIndex);
                if (temp_grid[0][0] != '$')
                {
                    PuzzleSolver((char **)temp_grid, (char **)word, wordIndex + 1);
                }
            }
        }

        for (int column = 0; column < grid_Width; column++)
        {
            for (int row; row <= StartIndex_Vertical; row++)
            {
                char **temp_grid = Vertical_UD(row, column, (char **)grid, (char *)SelectedWord, wordIndex);
                if (temp_grid[0][0] != '$')
                {
                    PuzzleSolver((char **)temp_grid, (char **)word, wordIndex + 1);
                }
            }
        }
    }
    else
    {
        printgrid((char **)grid);
        return 0;
    }
}

int printgrid(char **grid)
{
    for (int i = 0; i < grid_Height; i++)
    {
        printf(grid[i]);
    }
}