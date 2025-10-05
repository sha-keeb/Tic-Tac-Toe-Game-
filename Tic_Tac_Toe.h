#ifndef TIC_TAC_TOE_H
#define TIC_TAC_TOE_H

#include <stdbool.h>

#define MAX_SIZE 10

typedef struct
{
    int n;
    char cells[MAX_SIZE][MAX_SIZE];
} Board;

typedef struct
{
    char symbol;
    char name[20];
    bool isComputer;
} Player;

void init_board(Board *b, int n);
bool is_empty(Board *b, int r, int c);
bool apply_move(Board *b, int r, int c, char sym);
void print_board(Board *b);
bool check_row(Board *b, int r, char s);
bool check_col(Board *b, int c, char s);
bool check_diag(Board *b, char s);
bool check_win(Board *b, char s);
bool board_full(Board *b);
void flush_line(void);
int read_move(Board *b, int *r, int *c);
void computer_move(Board *b, int *r, int *c);
int run_game(Board *b, Player *players, int numPlayers);
int ask_board_size(void);
int ask_mode(void);
void main_menu(void);
void save_board_to_file(Board *b, const char *filename);

#endif
