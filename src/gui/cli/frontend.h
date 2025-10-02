#ifndef FRONTEND_H_
#define FRONTEND_H_

#include "../../brick_game/tetris/field.h"
#include "../../brick_game/tetris/struct.h"

void init_ncurses();
void print_main_menu();
void print_additional_information(GameInfo_t Game, int start_y, int start_x);
void print_score(GameInfo_t Game, int start_y, int start_x);
void print_game_over();
void print_pause();
void print_next_tetramino(GameInfo_t Game, int start_y, int start_x);
void print_map(GameInfo_t Game);

#endif