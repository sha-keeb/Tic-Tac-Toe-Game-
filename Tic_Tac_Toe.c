#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <time.h> // Used for seeding random number generator or time-based logic

#define MAX_SIZE 10 // maximum board size (10x10)

typedef struct
{
    int n;
    char cells[MAX_SIZE][MAX_SIZE]; // 2d array
} Board;

typedef struct
{
    char symbol;     // for x , o, z
    char name[20];   // name ..while playing multyplayer
    bool isComputer; // cpu
} Player;

/* ================= Board helpers ================= */
void init_board(Board *b, int n)
{
    b->n = n; // b*.n = n   same
    for (int r = 0; r < n; r++)
        for (int c = 0; c < n; c++) // Initialize all cells to blank space to represent an empty board
            b->cells[r][c] = ' ';
}

bool is_empty(Board *b, int r, int c)
{ // Check if a cell is unoccupied
    return b->cells[r][c] == ' ';
}

bool apply_move(Board *b, int r, int c, char sym)
{
    if (r < 0 || r >= b->n || c < 0 || c >= b->n || !is_empty(b, r, c))
        return false;
    b->cells[r][c] = sym; // Apply player's symbol to the board
    return true;
}

void print_board(Board *b)
{
    printf("\n   ");
    for (int c = 0; c < b->n; c++)
        printf(" %2d ", c + 1); // print column headers
    printf("\n");
    for (int r = 0; r < b->n; r++)
    {
        printf("%2d ", r + 1); // print row headers
        for (int c = 0; c < b->n; c++)
        {
            printf(" %c ", b->cells[r][c]); // Print cell content
            if (c != b->n - 1)
                printf("|"); // Print vertical separator between cells
        }
        printf("\n   ");
        if (r != b->n - 1)
        {
            for (int c = 0; c < b->n; c++)
            {
                printf("---"); // horizontal line
                if (c != (*b).n - 1)
                    printf("+");
            }
        }
        printf("\n");
    }
}

/* ================= Win / Draw ================= */
bool check_row(Board *b, int r, char s)
{
    for (int c = 0; c < b->n; c++)
        if (b->cells[r][c] != s)
            return false;
    return true;
}

bool check_col(Board *b, int c, char s)
{
    for (int r = 0; r < b->n; r++)
        if (b->cells[r][c] != s)
            return false;
    return true;
}

bool check_diag(Board *b, char s)
{
    bool main = true, anti = true; // Check both diagonals for a win condition
    for (int i = 0; i < b->n; i++)
    {
        if (b->cells[i][i] != s)
            main = false;
        if (b->cells[i][b->n - 1 - i] != s)
            anti = false;
    }
    return main || anti; // Return true if either diagonal is a win
}

bool check_win(Board *b, char s)
{
    for (int r = 0; r < b->n; r++)
        if (check_row(b, r, s))
            return true;
    for (int c = 0; c < b->n; c++)
        if (check_col(b, c, s))
            return true;
    return check_diag(b, s);
}

bool board_full(Board *b)
{ // Check if all cells are filled
    for (int r = 0; r < b->n; r++)
        for (int c = 0; c < b->n; c++)
            if (b->cells[r][c] == ' ')
                return false;
    return true; // Board is full, possibly a draw
}

/* ================= Input helpers ================= */
void flush_line(void)
{
    int ch;
    while ((ch = getchar()) != '\n' && ch != EOF)
    { // Clear input buffer to avoid leftover characters interfering with next input
    }
}

int read_move(Board *b, int *r, int *c)
{
    char line[50];
    while (1)
    {
        printf("\n+--------------------------------------------------+\n");
        printf("| Enter your move as: row column (e.g., 2 3)       |\n");
        printf("| Or type: M - Main Menu | E - Exit Game           |\n");
        printf("+--------------------------------------------------+\n");
        printf("Your move: ");
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

/* ================= Computer move ================= */
void computer_move(Board *b, int *r, int *c)
{
    int n = b->n;
    int empty_cells[MAX_SIZE * MAX_SIZE][2]; // Store coordinates of all empty cells
    int count = 0;
    for (int i = 0; i < n; i++) // Scan board for empty cells and store their positions
        for (int j = 0; j < n; j++)
            if (is_empty(b, i, j))
            {
                empty_cells[count][0] = i;
                empty_cells[count][1] = j;
                count++;
            }
    if (count > 0)
    {
        int pick = rand() % count; // Randomly select one of the available moves
        *r = empty_cells[pick][0];
        *c = empty_cells[pick][1];
    }
}

/* ================= Game loop ================= */
int run_game(Board *b, Player *players, int numPlayers)
{
    int moveNo = 0;
    srand((unsigned)time(NULL)); // Seed random number generator for AI move randomness
    while (1)
    {
        for (int p = 0; p < numPlayers; p++)
        {
            Player *cur = &players[p]; // Pointer to current player
            printf("\nTurn: %s (%c)\n", cur->name, cur->symbol);

            int r, c;
            int action = 0;
            if (cur->isComputer)
            {
                computer_move(b, &r, &c);
                apply_move(b, r, c, cur->symbol);
            }
            else
            {
                bool success = false;
                do
                {
                    action = read_move(b, &r, &c); // get user input
                    if (action == 1)
                        return 1; // Main Menu
                    if (action == 2)
                        return 2; // Exit
                    success = apply_move(b, r, c, cur->symbol);
                    if (!success)
                        printf("Cell already occupied. Try again.\n");
                } while (!success);
            }

            moveNo++;
            print_board(b);

            if (check_win(b, cur->symbol))
            {
                printf(">>> %s (%c) WINS!\n", cur->name, cur->symbol);
                return 0;
            }
            if (board_full(b))
            {
                puts(">>> It's a DRAW.");
                return 0;
            }
        }
    }
}

/* ================= UI helpers ================= */
int ask_board_size(void)
{
    int n;
    while (1)
    {
        printf("Enter board size N (3..10): ");
        if (scanf("%d", &n) == 1 && n >= 3 && n <= 10)
        {
            flush_line();
            return n;
        }
        printf("Invalid input. N must be in range 3 <= N <= 10.\n");
        printf("Try again.\n");
        flush_line();
    }
}

int ask_mode(void)
{
    int mode;
    while (1)
    {
        printf("\nSelect Game Mode:\n1) Player vs Player\n2) Player vs Computer\n3) 3 Players\nEnter 1/2/3: ");
        if (scanf("%d", &mode) == 1 && mode >= 1 && mode <= 3)
        {
            flush_line();
            return mode;
        }
        printf("Invalid choice. Try again.\n");
        flush_line();
    }
}

/* ================= Main Menu ================= */
void main_menu(void)
{
    while (1)
    {
        printf("\n");
        printf("=====================================================\n");
        printf("||                                                 ||\n");
        printf("||                 TIC - TAC - TOE                 ||\n");
        printf("||                                                 ||\n");
        printf("=====================================================\n");
        printf("\n");
        printf("                      MAIN MENU\n");
        printf("\n");
        printf("\n");
        printf("1) Start Game\n");
        printf("2) Exit\n");
        int choice;
        if (scanf("%d", &choice) == 1)
        {
            flush_line();
            if (choice == 2)
            {
                printf("\n+==================================================+\n");
                printf("|               Exiting the game...                |\n");
                printf("|             Hope to see you soon!                |\n");
                printf("\n+==================================================+\n");
                printf("\a");
                exit(0);
            }
            else if (choice == 1)
                break;
        }
        printf("Invalid choice.\n");
    }
}

/* ================= main ================= */
int main(void)
{
    srand((unsigned)time(NULL));

    while (1)
    {
        main_menu();

        int n = ask_board_size();
        Board b;
        init_board(&b, n);

        printf("\n+==================================================+\n");
        printf("|           HOW TO PLAY TIC-TAC-TOE                |\n");
        printf("+==================================================+\n");
        printf("| Objective:                                       |\n");
        printf("|   Align your symbols in a row to win the game.   |\n");
        printf("|                                                  |\n");
        printf("| How to Play:                                     |\n");
        printf("|   - Players take turns placing their symbol.     |\n");
        printf("|   - Enter your move as: row column               |\n");
        printf("|     Example: 2 3 (places symbol at row 2, col 3) |\n");
        printf("|                                                  |\n");
        printf("| Special Commands:                                |\n");
        printf("|   M - Return to Main Menu                        |\n");
        printf("|   E - Exit the Game                              |\n");
        printf("|                                                  |\n");
        printf("| Symbols:                                         |\n");
        printf("|   Player 1: X                                    |\n");
        printf("|   Player 2: O                                    |\n");
        printf("|   Player 3: Z                                    |\n");
        printf("+==================================================+\n");

        int mode = ask_mode(); // ← already declared below, so you can use it here
        if (mode == 3)
            printf("  Player 3: Z\n");

        printf("Let's begin!\n");

        print_board(&b);

        Player players[3];
        int numPlayers = 2;

        if (mode == 1)
        { // PvP
            strcpy(players[0].name, "Player1");
            players[0].symbol = 'X';
            players[0].isComputer = false;
            strcpy(players[1].name, "Player2");
            players[1].symbol = 'O';
            players[1].isComputer = false;
            numPlayers = 2;
        }
        else if (mode == 2)
        { // PvC
            strcpy(players[0].name, "You");
            players[0].symbol = 'X';
            players[0].isComputer = false;
            strcpy(players[1].name, "Computer");
            players[1].symbol = 'O';
            players[1].isComputer = true;
            numPlayers = 2;
        }
        else
        { // 3 players
            char name[20];
            char symbols[3] = {'X', 'O', 'Z'};
            numPlayers = 3;
            for (int i = 0; i < 3; i++)
            {
                printf("Enter name for player %d or type CPU: ", i + 1);
                if (!fgets(name, sizeof(name), stdin))
                    continue;
                name[strcspn(name, "\n")] = 0;
                if (strcmp(name, "CPU") == 0 || strcmp(name, "cpu") == 0)
                {
                    snprintf(players[i].name, sizeof(players[i].name), "CPU%d", i + 1);
                    players[i].isComputer = true;
                }
                else
                {
                    strcpy(players[i].name, name);
                    players[i].isComputer = false;
                }
                players[i].symbol = symbols[i];
            }
        }

        int result = run_game(&b, players, numPlayers);
        if (result == 2)
        {
            printf("+==================================================+\n");
            printf("|               Exiting the Game...                |\n");
            printf("|                   Goodbye                        |\n");
            printf("+==================================================+\n");
            printf("\a"); // Beep sound for dramatic effect
            break;
        }
        // If result == 1 → player chose Main Menu → loop restarts
    }

    return 0;
}
