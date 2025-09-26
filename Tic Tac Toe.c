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