#include "field.h"

void speed() {
  GameInfo_t *Game = game_info_struct();
  if (Game->level != 10) {
    Game->level = Game->score / 600;
    Game->speed = 500 - (30 * Game->level);
  }
}

void score_calc(int count_lines) {
  GameInfo_t *Game = game_info_struct();
  switch (count_lines) {
    case (1):
      Game->score += 100;
      break;
    case (2):
      Game->score += 300;
      break;
    case (3):
      Game->score += 700;
      break;
    case (4):
      Game->score += 1500;
      break;
    default:
      break;
  }
}

void save_score() {
  GameInfo_t *Game = game_info_struct();
  FILE *file = fopen(".final_score.txt", "w");
  if (file != NULL) {
    if (Game->high_score < Game->score) {
      fprintf(file, "%d\n", Game->score);
    } else {
      fprintf(file, "%d\n", Game->high_score);
    }
    fclose(file);
  }
}

void best_Score() {
  GameInfo_t *Game = game_info_struct();
  FILE *file = fopen(".final_score.txt", "r");
  if (file != NULL) {
    fscanf(file, "%d", &Game->high_score);
    fclose(file);
  }
}

void fall_down(GameInfo_t *Game) {
  Status_game *Status = status_game_struct();
  int fallen = 0;
  while (!fallen) {
    int can_move = 1;
    can_move = can_move_Down();

    if (can_move) {
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
      fallen = 1;
    }
  }
  Status->Game_Moving = 0;
  Status->Game_Attaching = 1;
}

void if_game_over() {
  Status_game *Status = status_game_struct();
  GameInfo_t *Game = game_info_struct();
  int game_over_check = 0;
  for (int i = 0; i < COLS + 1; i++) {
    if (Game->field[1][i] == 3) {
      game_over_check = 1;
      Status->Game_Over = 1;
    }
  }
  if (game_over_check == 0) {
    Status->Game_Spawn = 1;
    Status->Game_Over = 0;
  }
}