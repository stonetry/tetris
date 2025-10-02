#ifndef GAME_H
#define GAME_H

#include "../../gui/cli/frontend.h"
#include "field.h"

#define GAME_OVER Game.field == NULL
#define PAUSE Game.pause == 1

void game_process();
int main_menu();

#endif