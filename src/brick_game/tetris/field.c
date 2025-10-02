#include "field.h"

int s21_create_matrix(int ***field, int x, int y) {
  int matrix_status = OK;
  *field = (int **)calloc(x + 2, sizeof(int *));
  if (*field == NULL) {
    matrix_status = INCORRECT_MATRIX;
  }
  if (!matrix_status) {
    for (int i = 0; i < x + 2; i++) {
      (*field)[i] = (int *)calloc(y + 2, sizeof(int *));
      if ((*field)[i] == NULL) {
        matrix_status = INCORRECT_MATRIX;
      }
    }
  }
  return matrix_status;
}

void s21_remove_matrix(int ***field, int x) {
  if (*field != NULL) {
    for (int i = 0; i < x + 2; i++) {
      free((*field)[i]);
    }
  }
  free(*field);
}

void create_map(GameInfo_t *Game) {
  for (int i = 0; i < ROWS + 2; i++) {
    for (int j = 0; j < COLS + 2; j++) {
      if (i == 0 || i == ROWS + 1 || j == 0 || j == COLS + 1) {
        Game->field[i][j] = 1;
      } else {
        Game->field[i][j] = 0;
      }
    }
  }
}

int if_block(Figure figure, int i, int j) {
  int isBlock = 0;
  for (int k = 0; k < 4; k++) {
    int absolute_block_x = figure.x + figure.blocks[k].x;
    int absolute_block_y = figure.y + figure.blocks[k].y;

    if (i == absolute_block_x && j == absolute_block_y) {
      isBlock = 1;
    }
  }
  return isBlock;
}

void erase_line(GameInfo_t *Game) {
  int count_lines = 0;
  for (int i = 0; i <= ROWS; i++) {
    int full_line = 1;
    for (int j = 1; j <= COLS; j++) {
      if (Game->field[i][j] != 3) {
        full_line = 0;
      }
    }
    if (full_line) {
      count_lines++;
      for (int k = i; k > 1; k--) {
        for (int j = 1; j <= COLS; j++) {
          Game->field[k][j] = Game->field[k - 1][j];
        }
      }
      for (int j = 1; j <= COLS; j++) {
        Game->field[1][j] = 0;
      }
      i--;
    }
  }
  score_calc(count_lines);
}