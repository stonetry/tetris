#include "field.h"

void physics(GameInfo_t *Game) {
  Status_game *Status = status_game_struct();

  int can_move_down = 1;
  can_move_down = can_move_Down();
  if (can_move_down) {
    for (int i = ROWS + 1; i >= 0; i--) {
      for (int j = 0; j <= COLS + 1; j++) {
        if (Game->field[i][j] == 2) {
          Game->field[i + 1][j] = 2;
          Game->field[i][j] = 0;
        } else if (Game->field[i][j] == 5) {
          Game->field[i + 1][j] = 5;
          Game->field[i][j] = 0;
        }
      }
    }
    update_Tetramino(Game);
  } else {
    for (int i = 0; i <= ROWS + 1; i++) {
      for (int j = 0; j <= COLS + 1; j++) {
        if (Game->field[i][j] == 2 || Game->field[i][j] == 5) {
          Game->field[i][j] = 3;
        }
      }
    }
    Status->Game_Moving = 0;
    Status->Game_Attaching = 1;
  }
}

int can_move_Down() {
  GameInfo_t *Game = game_info_struct();
  int can_move_down = 1;
  for (int i = ROWS; i >= 0 && can_move_down; i--) {
    for (int j = 0; j <= COLS + 1 && can_move_down; j++) {
      if (Game->field[i][j] == 2 || Game->field[i][j] == 5) {
        if (i + 1 > ROWS + 1 || Game->field[i + 1][j] == 1 ||
            Game->field[i + 1][j] == 3) {
          can_move_down = 0;
        }
      }
    }
  }
  return can_move_down;
}

void update_Tetramino(GameInfo_t *Game) {
  Figure *Tetramino = tetramino_struct();
  int k = 0;
  for (int i = 0; i < ROWS + 2 && k < 4; i++) {
    for (int j = 0; j < COLS + 2 && k < 4; j++) {
      if (Game->field[i][j] == 5) {
        Tetramino->blocks[k].x = j;
        Tetramino->blocks[k].y = i;
        Tetramino->centre = Tetramino->blocks[k];
        k++;
      } else if (Game->field[i][j] == 2) {
        Tetramino->blocks[k].x = j;
        Tetramino->blocks[k].y = i;
        k++;
      }
    }
  }
}