#ifndef FIELD_H_
#define FIELD_H_

#include <ncurses.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "struct.h"

#define ROWS 20
#define COLS 10

#define INCORRECT_MATRIX 1
#define Ok 0

void userInput(UserAction_t action, bool hold);

GameInfo_t updateCurrentState();

#endif
// МАТРИЦА СОЗДАНИЕ ПОЛЯ И ФИГУРЫ НА ПОЛЕ
int s21_create_matrix(int ***field, int x, int y);
void s21_remove_matrix(int ***field, int x);
void create_map(GameInfo_t *Game);
int if_block(Figure figure, int i, int j);
void erase_line(GameInfo_t *Game);

// СОЗДАНИЕ ФИГУРКИ И СЛЕДУЮЩЕЙ ФИГУРКИ
Figure generate_Shape(int random);
Figure create_newTetramino(GameInfo_t *Game);
void next_Tetramino_gen(Figure NextTetramino);
void zero_prev_Tetramino();

// ДВИЖЕНИЕ ФИГУРКИ ВПРАВО И ВЛЕВО
void move_side_right(GameInfo_t *Game);
void move_side_left(GameInfo_t *Game);

// ПОВОРОТ ФИГУРКИ
void rotate_Figure_right(GameInfo_t *Game);
void rotate_Figure_left(GameInfo_t *Game);
int can_rotate_Left(GameInfo_t *Game);
int can_rotate_Right(GameInfo_t *Game);

// ПАДЕНИЕ ФИГУРКИ ВНИЗ
void physics(GameInfo_t *Game);
int can_move_Down();
void update_Tetramino(GameInfo_t *Game);

// СТРУКТУРЫ
GameInfo_t *game_info_struct();
Figure *tetramino_struct();
Status_game *status_game_struct();

// БЭКЕНД
void game_Start();
void game_Spawn();
void game_Moving();
void game_Attaching();
void game_Over();
void game_Pause();

// ДЛЯ БЭКЕНДА
void speed();
void score_calc(int count_lines);
void if_game_over();
void save_score();
int input_key();
void fall_down(GameInfo_t *Game);
void best_Score();