#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

//Board size 

typedef struct {
    int n;                 
    char cells[10][10];      
} Board;

typedef struct {
    char symbol;           // 'X','O','Z'
    bool isComputer;       // true = CPU, false = human
    char name[20];
} Player;
