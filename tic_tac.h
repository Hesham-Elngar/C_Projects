#ifndef TIC_TAC_H
#define TIC_TAC_H

/***********************Includes Section*********************/
#include <stdio.h>
#include <stdlib.h>
#include<string.h>
#include<windows.h>
#include "STD_types.h"
/*********************MACRO Declarations***********************/
#define MAX_SIZE 3
#define PLAYER1_TURN 1
#define PLAYER2_TURN 2
#define EXIT_SUCCESSFUL 0
#define COL_START_INDEX 0
#define ROW_START_INDEX 0
#define START_GAME 1
#define EXIT_GAME 0
#define HELP 2
#define PLAYER1_SYMBOL 'X'
#define PLAYER2_SYMBOL 'O'
/*********************MACRO Functions***********************/
#define SQUARE(X) (X*X)

typedef enum{
    r_nok,
    r_ok
}return_status;

/**********************Function Declarations*********************/
void main_menu();
#endif // TIC_TAC_H
