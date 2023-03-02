/*
CO222 Programming Methodology - Project
Authours    : Adhikari R.A.J.C (E/19/008)
              Adikari A.M.K.M (E/19/009)
Topic       : Crossword Puzzle Solver - Dynamic
*/

// Header file that needed to perform IOs.
#include <stdio.h>

// Header file that needed to perform "exit()" environmental function.
#include <stdlib.h>

// Header file that declares a set of functions to work with strings. (strlen())
#include <string.h>

// Header file that declares several functions that are useful for testing and mapping characters.(toupper())
#include <ctype.h>

// Heater file that needed to perform execution time calculations
#include <time.h>

// Creating a collection of commonly used variables under a single name. (This make it easy to create and return several variables at once.)
typedef struct possible
{
    int occurances;      // How many times did any event occured
    int best_occurances; // How many times did any more appropriate event occured
    int column;          // Which column
    int best_column;
    int row; // Which row
    int best_row;
} possible;

// Declare two global variables to store width
int grid_width = 0, word_width = 0;

// Function to fill the solved puzzle
void print_puzzle(int count, char **grid)
{
    for (int row = 0; row < count; row++) // Call row by row
    {
        for (int column = 0; *(*(grid + row) + column) != '\0'; column++)
        {
            printf("%c", *(*(grid + row) + column));
        }
        putchar('\n'); // Going to a new line
    }
}

// Function to fill the specific word horizontally in the appropriate place
void fill_horizontal(char *word, char **grid, possible horizontal)
{
    // Row and Column values of the starting posithion
    int column = horizontal.column;
    int row = horizontal.row;

    int j = 0; // Declare a int variable to represent the index values of characters in the word
    for (int i = column; i < column + strlen(word); i++)
    {
        grid[row][i] = word[j]; // Filling the puzzle grid character by character
        j++;                    // Changing to next index
    }
}

// Function to fill the specific word horizontally in the best place
void fill_horizontal_best(char *word, char **grid, possible horizontal)
{

    // Row and Column values of the starting posithion
    int column = horizontal.best_column;
    int row = horizontal.best_row;
    int j = 0; // Declare a int variable to represent the index values of characters in the word
    for (int i = column; i < column + strlen(word); i++)
    {
        grid[row][i] = word[j]; // Filling the puzzle grid character by character
        j++;                    // Changing to next index
    }
}

// Function to fill the specific word vertically in the appropriate place
void fill_vertical(char *word, char **grid, possible vertical)
{
    // Row and Column values of the starting posithion
    int column = vertical.column;
    int row = vertical.row;

    int j = 0; // Declare a int variable to represent the index values of characters in the word
    for (int i = row; i < row + strlen(word); i++)
    {
        grid[i][column] = word[j]; // Filling the puzzle grid character by character
        j++;                       // Changing to next index
    }
}

// Function to fill the specific word vertically in the best place
void fill_vertical_best(char *word, char **grid, possible vertical)
{
    // Row and Column values of the starting posithion
    int column = vertical.best_column;
    int row = vertical.best_row;

    int j = 0; // Declare a int variable to represent the index values of characters in the word
    for (int i = row; i < row + strlen(word); i++)
    {
        grid[i][column] = word[j]; // Filling the puzzle grid character by character
        j++;                       // Changing to next index
    }
}

// Function to check if there are any appropriate slots for the word in horizontal and count how many set of slots are there
possible check_horizontal(char *word, char **grid, int row_count)
{
    /*
    Parameters : char *word    >>>> pointer to the selected word
                 char **grid   >>>> pointer from pointer to characters in puzzle grid
                 int row_count >>>> number of rows in the puzzle grid
    */
    int column, row;                        // Declare two integer variables to represent rows and colums
    int slots_for_word = 0, best_slots = 0; // Declare two integer variable for count of slots and best slots
    possible horizontal;                    // Declare s set of new horizontal variables
    horizontal.occurances = 0;              // variable to count event occurances
    horizontal.best_occurances = 0;

    for (row = 0; row < row_count; row++) // Calling row by row
    {
        slots_for_word = 0;
        for (column = 0; column < grid_width + 1; column++) // going throug grid characters in the row
        {
            // Check whether if the character is fillable or it is the character that we trying to assign
            if (grid[row][column] == '#' || toupper(grid[row][column]) == toupper(word[slots_for_word]))
            {

                if (toupper(grid[row][column]) == toupper(word[slots_for_word]))
                {
                    best_slots++; // Counting it as a best slot
                }
                slots_for_word++; // Counting it as a possible slot
            }
            else
            {
                if (slots_for_word == strlen(word) && best_slots >= 1)
                {
                    horizontal.best_occurances++;                   // Counting event occurences
                    horizontal.best_column = column - strlen(word); // Starting column value of the possible slot
                    horizontal.best_row = row;                      // Starting row value of the possible slot
                    horizontal.occurances++;
                    horizontal.column = column - strlen(word);
                    horizontal.row = row;
                }
                else if (slots_for_word == strlen(word)) // Checking number of possible slots equal to the length of the selected word
                {
                    horizontal.occurances++;                   // Counting event occurences
                    horizontal.row = row;                      // Starting row value of the possible slot
                    horizontal.column = column - strlen(word); // Starting column value of the possible slot
                }
                best_slots = 0;
                slots_for_word = 0; // Possible slot numbers set to 0
            }
        }
        // When above loop ended with it limits while satisfying conditions
        if (slots_for_word == strlen(word) && best_slots >= 1)
        {
            horizontal.best_occurances++;                   // Counting event occurences
            horizontal.best_column = column - strlen(word); // Starting column value of the possible slot
            horizontal.best_row = row;                      // Starting row value of the possible slot

            horizontal.occurances++;
            horizontal.column = column - strlen(word);
            horizontal.row = row;
        }
        else if (slots_for_word == strlen(word)) // Checking number of possible slots equal to the length of the selected word
        {
            horizontal.occurances++;                   // Counting event occurences
            horizontal.row = row;                      // Starting row value of the possible slot
            horizontal.column = column - strlen(word); // Starting column value of the possible slot
        }
    }

    return horizontal; // Return the variables set
}

// Function to check if there are any appropriate slots in vertical and count how many set of slots are there
possible check_vertical(char *word, char **grid, int row_grid)
{
    /*
    Parameters : char *word    >>>> pointer to the selected word
                 char **grid   >>>> pointer from pointer to characters in puzzle grid
                 int row_count >>>> number of rows in the puzzle grid
    */
    int column, row;                        // Declare two integer variables to represent rows and colums
    int slots_for_word = 0, best_slots = 0; // Declare two integer variable for count of slots and best slots
    possible vertical;                      // Declare s set of new horizontal variables
    vertical.occurances = 0;                // variable to count event occurances
    vertical.best_occurances = 0;

    for (column = 0; column < grid_width + 1; column++) // Calling column by column
    {
        slots_for_word = 0;
        for (row = 0; row < row_grid; row++) // going throug grid characters in the column
        {
            if (grid[row][column] == '#' || toupper(grid[row][column]) == toupper(word[slots_for_word])) // Checking number of possible slots equal to the length of the selected word
            {
                // Counting it as a possible slot
                if (toupper(grid[row][column]) == toupper(word[slots_for_word]))
                {
                    best_slots++; // Counting it as a best slot
                }
                slots_for_word++;
            }
            else
            {
                if (slots_for_word == strlen(word) && best_slots >= 1) // Checking number of possible slots equal to the length of the selected word and is this athe appropriate one
                {

                    vertical.best_occurances++;             // Counting event occurences
                    vertical.best_column = column;          // Starting column value of the possible slot
                    vertical.best_row = row - strlen(word); // Starting row value of the possible slot
                    vertical.occurances++;
                    vertical.column = column;
                    vertical.row = row - strlen(word);
                }
                else if (slots_for_word == strlen(word)) // Checking number of possible slots equal to the length of the selected word
                {
                    vertical.occurances++;             // Counting event occurences
                    vertical.column = column;          // Starting column value of the possible slot
                    vertical.row = row - strlen(word); // Starting row value of the possible slot
                }
                best_slots = 0;
                slots_for_word = 0; // Possible slot numbers set to 0
            }
        }
        // When above loop ended with it limits while satisfying conditions
        if (slots_for_word == strlen(word) && best_slots >= 1) // Checking number of possible slots equal to the length of the selected word and is this the appropriate one
        {
            vertical.best_occurances++;             // Counting event best occurences
            vertical.best_column = column;          // Starting column value of the possible slot
            vertical.best_row = row - strlen(word); // Starting row value of the possible slot
            best_slots = 0;
            vertical.occurances++;
            vertical.column = column;
            vertical.row = row - strlen(word);
        }
        else if (slots_for_word == strlen(word)) // Checking number of possible slots equal to the length of the selected word
        {
            vertical.occurances++;             // Counting event occurences
            vertical.column = column;          // Starting column value of the possible slot
            vertical.row = row - strlen(word); // Starting row value of the possible slot
        }
    }

    return vertical; // Return the variables set
}

int main()
{
    // Declaring two integer variables to count row counts in grid 2d array and word 2d array
    int row_grid = 0, row_word = 0;
    // double time_spent = 0.0;
    // clock_t begin = clock();
    //  Reserve a memory space for a 2D dynamic array of size 100x100 to store puzzle grid
    //  (since initially we don't know the actual size of the puzzle grid that user going to enter)
    char **grid_temp = (char **)malloc(100 * sizeof(char *));
    for (int i = 0; i < 100; i++)
    {
        *(grid_temp + i) = (char *)malloc(100 * sizeof(char));
    }

    // 'for loop' to get grid_temp line by line
    for (; scanf("%[^\n]%*c", grid_temp[row_grid]) == 1; row_grid++)
    {
        //   Go through the row untill meet null character

        for (int column_grid = 0; grid_temp[row_grid][column_grid] != '\0'; column_grid++)
        {
            // printf("%c", grid_temp[row_grid_temp][column_grid_temp]);
            //  Check whether each characters are valit or not
            if (!(*(*(grid_temp + row_grid) + column_grid) == '#' ||
                  *(*(grid_temp + row_grid) + column_grid) == '*' ||
                  (*(*(grid_temp + row_grid) + column_grid) >= 'A' && *(*(grid_temp + row_grid) + column_grid) <= 'Z') ||
                  (*(*(grid_temp + row_grid) + column_grid) >= 'a' && *(*(grid_temp + row_grid) + column_grid) <= 'z')))
            {
                // When any character is invalid
                printf("INVALID INPUT"); // Print
                exit(0);                 // Exit from the program
            }
            if (grid_width < column_grid)
            {
                grid_width = column_grid;
            }
        }
    }

    // With the values which calculated while getting the puzzle grid, creating a more appropriate new memory space to store the puzzle grid
    char **grid = (char **)malloc(row_grid * sizeof(char *));
    for (int i = 0; i <= row_grid; i++)
    {
        *(grid + i) = (char *)malloc((grid_width + 1) * sizeof(char));
    }

    // Copy the elements from the previous array to the new array
    for (int row = 0; row < row_grid; row++)
    {
        memcpy(grid[row], grid_temp[row], (grid_width + 1) * sizeof(char) + 1);
    }

    // Free the memory allocated for the previous array
    for (int i = 0; i < 100; i++)
        free(grid_temp[i]);
    free(grid_temp);

    // Reserve a memory space for a 2D dynamic array of size 100x100 to store words
    //(Since initially we don't know how many which size of words that user going to enter)
    char **word_temp = (char **)malloc(100 * sizeof(char *));
    for (int i = 0; i < 100; i++)
    {
        *(word_temp + i) = (char *)malloc(100 * sizeof(char));
    }

    // fflush(stdin);
    char t1;
    scanf("%c", &t1); // Clear the newline character entered before using std input

    // 'for loop' to get word_temps line by line
    for (; scanf("%[^\n]%*c", word_temp[row_word]) == 1; row_word++)
    {
        // Go through the row untill meet null character
        for (int column_word = 0; word_temp[row_word][column_word] != '\0'; column_word++)
        {
            // Check whether each characters are valit or not
            if (!((word_temp[row_word][column_word] >= 'A' && word_temp[row_word][column_word] <= 'Z') ||
                  (word_temp[row_word][column_word] >= 'a' && word_temp[row_word][column_word] <= 'z')))
            {
                // When any character is invalid
                printf("INVALID INPUT"); // Print
                exit(0);                 // Exit from the program
            }
            // word_temp[row_word_temp][column_word_temp] = toupper(word_temp[row_word_temp][column_word_temp]); // Convert all to capitals
            if (word_width < column_word)
            {
                word_width = column_word;
            }
        }
    }

    // With the values which calculated while getting the words, creating a more appropriate new memory space to store the words
    char **word = (char **)malloc(row_word * sizeof(char *));
    for (int i = 0; i < row_word; i++)
    {
        *(word + i) = (char *)malloc((word_width + 1) * sizeof(char));
    }

    // Copy the elements from the previous array to the new array
    for (int row = 0; row < row_word; row++)
    {
        memcpy(word[row], word_temp[row], strlen(word_temp[row]) * sizeof(char) + 1);
    }

    // Free the memory allocated for the word_temp array
    for (int i = 0; i < 100; i++)
        free(word_temp[i]);
    free(word_temp);

    int word_count = row_word; // Assign number of row count in word 2d array to word_count
    int row_count = row_grid;  // Assign number of row count in grid 2d array to row_count

    int checking = 0; // Declare variable for puzzle grid check count

    while (checking < word_count) // Check multiple times if there only one suitable place for a single word
    {
        // Checking word by word
        for (int i = 0; i < word_count; i++)
        {
            // Declaring set of variables for each horizontal checkings and vertical checkings
            possible horizontal, vertical;

            vertical = check_vertical(word[i], grid, row_count);     // Check suitable slots in vertical direction
            horizontal = check_horizontal(word[i], grid, row_count); // Check suitable slots in horizontal direction

            // When there is only one most suitable horizontal space that fit for the word
            if (horizontal.best_occurances > 0)
            {
                fill_horizontal_best(word[i], grid, horizontal); // Fill the puzzle grid
            }

            // When there is only one most suitable vertical space that fit for the word
            else if (vertical.best_occurances > 0)
            {
                fill_vertical_best(word[i], grid, vertical); // Fill the puzzle grid
            }

            // When there is only one suitable horizontal space that fit for the word
            else if (horizontal.occurances == 1 && vertical.occurances == 0)
            {
                fill_horizontal(word[i], grid, horizontal); // Fill the puzzle grid
            }

            // When there is only one suitable vertical space that fit for the word
            else if (vertical.occurances == 1 && horizontal.occurances == 0)
            {
                fill_vertical(word[i], grid, vertical); // Fill the puzzle grid
            }
        }
        checking++; // Incrementing the checking count
    }

    // When there were more than one suitable place for a single word
    for (int i = 0; i < word_count; i++)
    {
        possible horizontal, vertical;

        horizontal = check_horizontal(word[i], grid, row_count);
        vertical = check_vertical(word[i], grid, row_count);

        if (horizontal.occurances > 0)
        {
            fill_horizontal(word[i], grid, horizontal);
        }
        else if (vertical.occurances > 0)
        {
            fill_vertical(word[i], grid, vertical);
        }
        // When there is no any suitable place for the word
        else if (horizontal.occurances + vertical.occurances == 0)
        {
            printf("IMPOSSIBLE\n"); // Print filling puzzle grid is IMPOSSIBLE
            return 0;
        }
    }

    // Print final filled puzzle
    print_puzzle(row_count, grid);

    // Free the memory allocated for the word 2d array
    for (int i = 0; i < word_count; i++)
        free(word[i]);
    free(word);

    // Free the memory allocated for the grid 2d array
    for (int i = 0; i < row_count; i++)
        free(grid[i]);
    free(grid);

    /* // Calculate execution time
     clock_t end = clock();
     time_spent += (double)(end - begin) / CLOCKS_PER_SEC;
     printf("\nTime Taken = %fs\n", time_spent);
    */
    return 0;
}