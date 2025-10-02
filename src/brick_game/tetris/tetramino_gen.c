#include "field.h"

Figure create_newTetramino(GameInfo_t *Game) {
  int second_figure = 0;
  static int first_figure = -1;

  if (first_figure == -1) {
    second_figure = rand() % 7;
    first_figure = rand() % 7;
  } else {
    second_figure = first_figure;
    first_figure = rand() % 7;
  }

  Figure Tetramino = generate_Shape(second_figure);
  Figure NextTetramino = generate_Shape(first_figure);
  zero_prev_Tetramino();
  next_Tetramino_gen(NextTetramino);

  Figure *tetramino = tetramino_struct();
  tetramino->type = Tetramino.type;
  int is_block;
  int centre = 1;
  for (int i = 0; i < ROWS + 2; i++) {
    for (int j = 0; j < COLS + 2; j++) {
      if ((is_block = if_block(Tetramino, i, j)) == 1) {
        Game->field[i][j] = 2;
        if (centre == 1) {
          Game->field[i][j] = 5;
          centre--;
        }
      }
    }
  }
  return Tetramino;
}

Figure generate_Shape(int random) {
  Figure figure;
  switch (random) {
    case (0):
      figure.x = 1;
      figure.y = 5;
      figure.type = 'I';
      figure.blocks[0] = (Block){0, 0};
      figure.blocks[1] = (Block){0, 1};
      figure.blocks[2] = (Block){0, 2};
      figure.blocks[3] = (Block){0, 3};

      figure.centre = figure.blocks[0];
      break;

    case (1):
      figure.x = 1;
      figure.y = 5;
      figure.type = 'O';
      figure.blocks[0] = (Block){0, 0};
      figure.blocks[1] = (Block){1, 0};
      figure.blocks[2] = (Block){0, 1};
      figure.blocks[3] = (Block){1, 1};

      figure.centre = figure.blocks[0];
      break;

    case (2):
      figure.x = 1;
      figure.y = 5;
      figure.type = 'S';
      figure.blocks[0] = (Block){0, 1};
      figure.blocks[1] = (Block){1, 1};
      figure.blocks[2] = (Block){1, 2};
      figure.blocks[3] = (Block){2, 2};

      figure.centre = figure.blocks[0];
      break;

    case (3):
      figure.x = 1;
      figure.y = 5;
      figure.type = 'Z';
      figure.blocks[0] = (Block){0, 2};
      figure.blocks[1] = (Block){1, 1};
      figure.blocks[2] = (Block){1, 2};
      figure.blocks[3] = (Block){2, 1};

      figure.centre = figure.blocks[0];
      break;

    case (4):
      figure.x = 1;
      figure.y = 5;
      figure.type = 'J';
      figure.blocks[0] = (Block){0, 0};
      figure.blocks[1] = (Block){0, 1};
      figure.blocks[2] = (Block){0, 2};
      figure.blocks[3] = (Block){1, 2};

      figure.centre = figure.blocks[0];
      break;

    case (5):
      figure.x = 1;
      figure.y = 5;
      figure.type = 'L';
      figure.blocks[0] = (Block){1, 0};
      figure.blocks[1] = (Block){1, 1};
      figure.blocks[2] = (Block){1, 2};
      figure.blocks[3] = (Block){0, 2};

      figure.centre = figure.blocks[0];
      break;

    case (6):
      figure.x = 1;
      figure.y = 5;
      figure.type = 'T';
      figure.blocks[0] = (Block){0, 1};
      figure.blocks[1] = (Block){1, 0};
      figure.blocks[2] = (Block){1, 1};
      figure.blocks[3] = (Block){1, 2};

      figure.centre = figure.blocks[0];
      break;
  }
  return figure;
}

void next_Tetramino_gen(Figure NextTetramino) {
  GameInfo_t *Game = game_info_struct();

  int is_block;
  for (int i = 0; i < 10; i++) {
    for (int j = 0; j < 10; j++) {
      if ((is_block = if_block(NextTetramino, i, j)) == 1) {
        Game->next[i][j] = 2;
      }
    }
  }
}

void zero_prev_Tetramino() {
  GameInfo_t *Game = game_info_struct();
  for (int i = 0; i < 10; i++) {
    for (int j = 0; j < 10; j++) {
      if (Game->next[i][j] == 2) {
        Game->next[i][j] = 0;
      }
    }
  }
}