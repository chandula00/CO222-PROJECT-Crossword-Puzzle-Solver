#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

typedef struct possible
{
    int occurances;
    int column;
    int row;
} possible;

void print_puzzle(char grid[100][100], int count)
{
    for (int row = 0; row < count; row++)
    {
        printf(grid[row]);
        putchar('\n');
    }
}

void fill_horizontal(char grid[100][100], char *word, possible horizontal)
{
    int column = horizontal.column;
    int row = horizontal.row;
    int i, k = 0;
    for (i = column; i < column + strlen(word); i++)
    {
        grid[row][i] = word[k];
        k++;
    }
}

void fill_vertical(char grid[100][100], char *word, possible vertical)
{
    int column = vertical.column;
    int row = vertical.row;
    int i, k = 0;
    for (i = row; i < row + strlen(word); i++)
    {
        grid[i][column] = word[k];
        k++;
    }
}

possible check_horizontal(char *word, char grid[100][100], int row_grid)
{
    int column, row;
    int slots_for_word = 0;
    possible horizontal;
    horizontal.occurances = 0;

    for (row = 0; row < row_grid; row++)
    {
        slots_for_word = 0;
        for (column = 0; column < strlen(grid[row]); column++)
        {
            if (grid[row][column] == '#' || toupper(grid[row][column]) == toupper(word[slots_for_word]))
            {
                slots_for_word++;
            }
            else
            {
                if (slots_for_word == strlen(word))
                {
                    horizontal.occurances++;
                    horizontal.row = row;
                    horizontal.column = column - strlen(word);
                }
                slots_for_word = 0;
            }
        }
        if (slots_for_word == strlen(word))
        {
            horizontal.occurances++;
            horizontal.row = row;
            horizontal.column = column - strlen(word);
        }
    }

    return horizontal;
}

possible check_vertical(char *word, char grid[100][100], int row_grid)
{
    int column, row;
    int slots_for_word = 0;
    possible vertical;
    vertical.occurances = 0;

    for (column = 0; column < strlen(grid[0]); column++)
    {
        slots_for_word = 0;
        for (row = 0; row < row_grid; row++)
        {
            if (grid[row][column] == '#' || toupper(grid[row][column]) == toupper(word[slots_for_word]))
            {
                slots_for_word++;
            }
            else
            {
                if (slots_for_word == strlen(word))
                {
                    vertical.occurances++;
                    vertical.column = column;
                    vertical.row = row - strlen(word);
                }
                slots_for_word = 0;
            }
        }
        if (slots_for_word == strlen(word))
        {
            vertical.occurances++;
            vertical.column = column;
            vertical.row = row - strlen(word);
        }
    }

    return vertical;
}

int main()
{
    static char grid[100][100];
    char word[100][100];

    int row_grid = 0;
    int column_grid = 0;

    int row_word = 0;
    int column_word = 0;

    for (; scanf("%[^\n]%*c", grid[row_grid]) == 1; row_grid++)
    {

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
    }

    fflush(stdin);

    for (; scanf("%[^\n]%*c", word[row_word]) == 1; row_word++)
    {

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
    
    int word_count = row_word;
    int row_count = row_grid;

    int checking = 0;

    while (checking < 3)
    {

        for (int i = 0; i < word_count; i++)
        {
            possible horizontal, vertical;

            horizontal = check_horizontal(word[i], grid, row_count);
            vertical = check_vertical(word[i], grid, row_count);

            if (horizontal.occurances == 1)
            {
                fill_horizontal(grid, word[i], horizontal);
            }
            else if (vertical.occurances == 1)
            {
                fill_vertical(grid, word[i], vertical);
            }
            else if (horizontal.occurances + vertical.occurances == 0)
            {
                printf("IMPOSSIBLE\n");
                return 0;
            }
        }
        checking++;
    }
    for (int i = 0; i < word_count; i++)
    {
        possible horizontal, vertical;

        horizontal = check_horizontal(word[i], grid, row_count);
        vertical = check_vertical(word[i], grid, row_count);

        if (horizontal.occurances > 0)
        {
            fill_horizontal(grid, word[i], horizontal);
        }
        else if (vertical.occurances > 0)
        {
            fill_vertical(grid, word[i], vertical);
        }
    }

    print_puzzle(grid, row_count);

    return 0;
}
