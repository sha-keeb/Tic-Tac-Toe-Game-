#include <stdio.h> // these are the libraries wanted
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <time.h> // Seeding the Random Number Generator

#define MAX_SIZE 10
// Board size

typedef struct // stores information about the board
{
    int n;
    char cells[MAX_SIZE][MAX_SIZE];
} Board;

// stores information about each player.
typedef struct
{
    char symbol;     // player simbol x , o
    char name[20];   // name   this is for p vs p / multyplayer option
    bool isComputer; // This is a boolean flag that tells you whether the player is a computer (true) or a human (false).
} Player;

void intit_board(Board *b, int n)
{
    b->= n;
    for (int r = 0; r < n; r++) // this for  go every sell in the board
        for (int c = 0; c < n; c++)
            b->cells[r][c] = ' '; // r for row and c for column
}

bool is_empty(Board *b, int r, int c){
    return b -> cells[r][c] = ' ' // this for   not over write a cell
}

bool apply_move(Board *b, int r, int c, char sym)
{
    if (r < 0 || r >= b->n || c < 0 || c >= b->n || !is_empty(b, r, c))
        // r < 0 || r >= b->n: Row is out of bounds
        // c < 0 || c >= b->n: Column is out of bounds
        //! is_empty(b, r, c): Cell is already occupied
        return false;
    b->cells[r][c] = sym; // The symbol to place ('X' or 'O')
    return true;
}

void print_board(Board *b)
{
    printf("\n   ");
    for (int c = 0; c < b->n; c++)
        printf("%2d", c + 1); // Loops through columns and prints column numbers
    printf("\n");
    for (int r = 0; c < b->; c++)
    {
        printf("%2d", r + 1);
        for (int c = 0; c < b->n; c++)
        {
            printf(" %c ", b->cells[r][c]); // Prints the character in the cell
            if (c != b->n - 1)
                printf("|"); // Adds a vertical divider | between cells, except after the last column.
        }
        printf("\n   ");
        if (r != b->n - 1)
        { // This checks if the current row r is not the last row.
            for (int c = 0; c < b->n; c++)
            {
                printf("---"); // It will print the horizontal divider for each cell.
                if (c != b->n - 1)
                    printf("+");
            }
        }
        printf("\n");
    }
}

/*++++++++++++checking  win or draw++++++++++++++++*/
bool check_row(Board *b, int r, char s)
{
    for (int c = 0; c < b->n; c++) // b->n is the size of the board (e.g., 3 for a 3×3 board)
        if (b > cells[r][c] != s)
            return false;
    return true;
}

bool check_diag(Board *b, int c, char s)
{                                  // char s: the symbol to check for ( 'X' or 'O')
    for (int r = 0; r < b->n; r++) // loop to every row
        if (b->cells[r][c] != s)
            return false;
    return true;
}

bool check_diag(Board *b, char s)
{
    bool main = true, anti = true;
    for (int i = 0; i < b->n; i++)
    {
        bool check_diag(Board * b, char s)
        {
            bool main = true, anti = true;
            for (int i = 0; i < b->n; i++)
            {
                if (b->cells[i][i] != s)
                    main = false; // Check both main and anti-diagonals for a winning line of symbol 's'
                if (b->cells[i][b->n - 1 - i] != s)
                    anti = false;
            }
            return main || anti;
        }

        bool check_win(Board * b, char s)
        {
            for (int r = 0; r < b->n; r++)
                if (check_row(b, r, s))
                    return true;
            for (int c = 0; c < b->n; c++)
                if (check_col(b, c, s))
                    return true;
            return check_diag(b, s);
        }

        bool board_full(Board * b)
        {
            for (int r = 0; r < b->n; r++)
                for (int c = 0; c < b->n; c++)
                    if (b->cells[r][c] == ' ')
                        return false;
            return true;
        }

        /* ++++++++++++++Input helpers +++++++++++++++++++++ */
        void flush_line(void)
        {
            int ch;
            while ((ch = getchar()) != '\n' && ch != EOF)
            {
            } // end-of-file (EOF)
        }

        int read_move(Board * b, int *r, int *c)
        {
            char line[50];
            while (1)
            {
                printf("Enter row and col (e.g., 2 3) or M=Main Menu, E=Exit: ");
                if (!fgets(line, sizeof(line), stdin))
                    continue;

                // Check for Main Menu or Exit
                if (line[0] == 'M' || line[0] == 'm')
                    return 1; // main menu
                if (line[0] == 'E' || line[0] == 'e')
                    return 2; // exit

                int rr, cc;
                if (sscanf(line, "%d %d", &rr, &cc) == 2)
                {
                    rr--;
                    cc--;
                    if (rr >= 0 && rr < b->n && cc >= 0 && cc < b->n)
                    {
                        *r = rr;
                        *c = cc;
                        return 0; // valid move
                    }
                }
                printf("Invalid input. Try again.\n");
            }
        }

        /* +++++++++++++++ Computer move ++++++++++++++++ */

        void computer_move(Board * b, int *r, int *c)
        {
            int n = b->n;
            int empty_cells[MAX_SIZE * MAX_SIZE][2];
            int count = 0;
            for (int i = 0; i < n; i++)
                for (int j = 0; j < n; j++)
                    if (is_empty(b, i, j))
                    {
                        empty_cells[count][0] = i;
                        empty_cells[count][1] = j;
                        count++;
                    }
            if (count > 0)
            {
                int pick = rand() % count;
                *r = empty_cells[pick][0];
                *c = empty_cells[pick][1];
            }
        }
