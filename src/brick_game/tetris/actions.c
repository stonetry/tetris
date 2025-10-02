#include "field.h"

// СДВИГ
// ВПРАВО--------------------------------------------------------------------------------------------------------------------

int can_move_right(GameInfo_t *Game) {
  Figure *tetramino = tetramino_struct();

  int can_move = 1;
  for (int k = 0; k < 4; k++) {
    int x = tetramino->blocks[k].x;
    int y = tetramino->blocks[k].y;
    if (x + 1 > COLS + 1 || Game->field[y][x + 1] == 1 ||
        Game->field[y][x + 1] == 3) {
      can_move = 0;
    }
  }
  return can_move;
}

void move_side_right(GameInfo_t *Game) {
  Figure *tetramino = tetramino_struct();

  if (can_move_right(Game)) {
    for (int k = 0; k < 4; k++) {
      int x = tetramino->blocks[k].x;
      int y = tetramino->blocks[k].y;
      Game->field[y][x] = 0;
    }

    for (int k = 0; k < 4; k++) {
      tetramino->blocks[k].x += 1;
    }
    tetramino->centre.x += 1;

    for (int k = 0; k < 4; k++) {
      int x = tetramino->blocks[k].x;
      int y = tetramino->blocks[k].y;
      Game->field[y][x] = 2;
    }
    Game->field[tetramino->centre.y][tetramino->centre.x] = 5;
  }
}

// ПОВОРОТ
// ВПРАВО--------------------------------------------------------------------------------------------------------------------
int can_rotate_Right(GameInfo_t *Game) {
  Figure *tetramino = tetramino_struct();

  int can_rotate = 1;
  int new_x[4], new_y[4];

  for (int i = 0; i < 4; i++) {
    int relative_x = tetramino->blocks[i].x - tetramino->centre.x;
    int relative_y = tetramino->blocks[i].y - tetramino->centre.y;

    int rotated_x = relative_y;
    int rotated_y = -relative_x;

    new_x[i] = rotated_x + tetramino->centre.x;
    new_y[i] = rotated_y + tetramino->centre.y;

    if (new_x[i] < 0 || new_x[i] > COLS + 1 || new_y[i] < 0 ||
        new_y[i] > ROWS + 1) {
      can_rotate = 0;
    }

    int cell = Game->field[new_y[i]][new_x[i]];
    if (cell == 1 || cell == 3) {
      can_rotate = 0;
    }
  }
  if (tetramino->type == 'O') {
    can_rotate = 0;
  }
  return can_rotate;
}

void rotate_Figure_right(GameInfo_t *Game) {
  Figure *tetramino = tetramino_struct();

  if (can_rotate_Right(Game)) {
    int min_x = 1000;
    int min_y = 1000;
    int new_x[4], new_y[4];

    for (int k = 0; k < 4; k++) {
      int x = tetramino->blocks[k].x;
      int y = tetramino->blocks[k].y;
      Game->field[y][x] = 0;
    }

    for (int i = 0; i < 4; i++) {
      int relative_x = tetramino->blocks[i].x - tetramino->centre.x;
      int relative_y = tetramino->blocks[i].y - tetramino->centre.y;

      int rotated_x = relative_y;
      int rotated_y = -relative_x;

      new_x[i] = rotated_x + tetramino->centre.x;
      new_y[i] = rotated_y + tetramino->centre.y;

      if (new_x[i] < min_x) min_x = new_x[i];
      if (new_y[i] < min_y) min_y = new_y[i];
    }
    int shift_x = (min_x < 0) ? -min_x : 0;
    int shift_y = (min_y < 0) ? -min_y : 0;

    for (int i = 0; i < 4; i++) {
      tetramino->blocks[i].x = new_x[i] + shift_x;
      tetramino->blocks[i].y = new_y[i] + shift_y;
    }

    for (int k = 0; k < 4; k++) {
      int x = tetramino->blocks[k].x;
      int y = tetramino->blocks[k].y;
      Game->field[y][x] = 2;
    }
  }
  Game->field[tetramino->centre.y][tetramino->centre.x] = 5;
}

// ПОВОРОТ
// ВЛЕВО--------------------------------------------------------------------------------------------------------------------
int can_rotate_Left(GameInfo_t *Game) {
  Figure *tetramino = tetramino_struct();
  int can_rotate = 1;
  int new_x[4], new_y[4];

  for (int i = 0; i < 4; i++) {
    int relative_x = tetramino->blocks[i].x - tetramino->centre.x;
    int relative_y = tetramino->blocks[i].y - tetramino->centre.y;

    int rotated_x = -relative_y;
    int rotated_y = relative_x;

    new_x[i] = rotated_x + tetramino->centre.x;
    new_y[i] = rotated_y + tetramino->centre.y;

    if (new_x[i] < 0 || new_x[i] > COLS + 1 || new_y[i] < 0 ||
        new_y[i] > ROWS + 1) {
      can_rotate = 0;
    }

    int cell = Game->field[new_y[i]][new_x[i]];
    if (cell == 1 || cell == 3) {
      can_rotate = 0;
    }
  }

  if (tetramino->type == 'O') {
    can_rotate = 0;
  }
  return can_rotate;
}

void rotate_Figure_left(GameInfo_t *Game) {
  Figure *tetramino = tetramino_struct();
  if (can_rotate_Left(Game)) {
    int min_x = 1000;
    int min_y = 1000;
    int new_x[4], new_y[4];

    for (int k = 0; k < 4; k++) {
      int x = tetramino->blocks[k].x;
      int y = tetramino->blocks[k].y;
      Game->field[y][x] = 0;
    }

    for (int i = 0; i < 4; i++) {
      int relative_x = tetramino->blocks[i].x - tetramino->centre.x;
      int relative_y = tetramino->blocks[i].y - tetramino->centre.y;

      int rotated_x = -relative_y;
      int rotated_y = relative_x;

      new_x[i] = rotated_x + tetramino->centre.x;
      new_y[i] = rotated_y + tetramino->centre.y;

      if (new_x[i] < min_x) min_x = new_x[i];
      if (new_y[i] < min_y) min_y = new_y[i];
    }
    int shift_x = (min_x < 0) ? -min_x : 0;
    int shift_y = (min_y < 0) ? -min_y : 0;

    for (int i = 0; i < 4; i++) {
      tetramino->blocks[i].x = new_x[i] + shift_x;
      tetramino->blocks[i].y = new_y[i] + shift_y;
    }

    for (int k = 0; k < 4; k++) {
      int x = tetramino->blocks[k].x;
      int y = tetramino->blocks[k].y;
      Game->field[y][x] = 2;
    }
    Game->field[tetramino->centre.y][tetramino->centre.x] = 5;
  }
}

// СДВИГ
// ВЛЕВО--------------------------------------------------------------------------------------------------------------------
int can_move_left(GameInfo_t *Game) {
  Figure *tetramino = tetramino_struct();
  int can_move = 1;
  for (int k = 0; k < 4; k++) {
    int x = tetramino->blocks[k].x;
    int y = tetramino->blocks[k].y;
    if (x - 1 < 1 || Game->field[y][x - 1] == 1 || Game->field[y][x - 1] == 3) {
      can_move = 0;
    }
  }
  return can_move;
}

void move_side_left(GameInfo_t *Game) {
  Figure *tetramino = tetramino_struct();

  if (can_move_left(Game)) {
    for (int k = 0; k < 4; k++) {
      int x = tetramino->blocks[k].x;
      int y = tetramino->blocks[k].y;
      Game->field[y][x] = 0;
    }

    for (int k = 0; k < 4; k++) {
      tetramino->blocks[k].x -= 1;
    }
    tetramino->centre.x -= 1;

    for (int k = 0; k < 4; k++) {
      int x = tetramino->blocks[k].x;
      int y = tetramino->blocks[k].y;
      Game->field[y][x] = 2;
    }
    Game->field[tetramino->centre.y][tetramino->centre.x] = 5;
  }
}