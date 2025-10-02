#include "field.h"

GameInfo_t updateCurrentState() {
  Status_game *Status = status_game_struct();
  GameInfo_t *Game = game_info_struct();

  if (Status->Game_Start) {
    game_Start();
  } else if (Status->Game_Spawn) {
    game_Spawn();
  } else if (Status->Game_Moving) {
    game_Moving();
  } else if (Status->Game_Attaching) {
    game_Attaching();
  } else if (Status->Game_Over) {
    game_Over();
  }

  return *Game;
}

void game_Start() {
  Status_game *Status = status_game_struct();
  GameInfo_t *Game = game_info_struct();

  if (s21_create_matrix(&Game->field, ROWS, COLS) == INCORRECT_MATRIX ||
      s21_create_matrix(&Game->next, 10, 10) == INCORRECT_MATRIX) {
    Status->Game_Start = 0;
    Status->Game_Over = 1;
  } else {
    best_Score();
    Status->Game_Start = 0;
    Status->Game_Spawn = 1;
  }
  create_map(Game);
}

void game_Spawn() {
  Status_game *Status = status_game_struct();
  GameInfo_t *Game = game_info_struct();

  create_newTetramino(Game);
  Status->Game_Spawn = 0;
  Status->Game_Moving = 1;
}

void game_Moving() {
  GameInfo_t *Game = game_info_struct();

  int key = input_key();
  bool hold = false;
  if (key == Down) {
    hold = true;
  }
  userInput(key, hold);

  static clock_t time = 0;
  speed();
  clock_t current_time = clock();

  if ((current_time - time) * 1000 / CLOCKS_PER_SEC >=
      (unsigned long)Game->speed) {
    physics(Game);
    time = current_time;
  }
}

void game_Attaching() {
  Status_game *Status = status_game_struct();
  GameInfo_t *Game = game_info_struct();

  erase_line(Game);
  Status->Game_Attaching = 0;

  if_game_over();
}

void game_Over() {
  GameInfo_t *Game = game_info_struct();

  save_score();
  s21_remove_matrix(&Game->field, ROWS);
  s21_remove_matrix(&Game->next, 10);
  Game->field = NULL;
}

void userInput(UserAction_t action, bool hold) {
  GameInfo_t *Game = game_info_struct();
  Status_game *Status = status_game_struct();
  switch (action) {
    case (Left):
      move_side_left(Game);
      break;
    case (Right):
      move_side_right(Game);
      break;
    case (Action):
      rotate_Figure_right(Game);
      break;
    case (Down):
      if (hold == 1) {
        fall_down(Game);
      }
      break;
    case (Pause):
      Game->pause = 1;
      break;
    case (Terminate):
      save_score(Game);
      Status->Game_Over = 1;
      Status->Game_Moving = 0;
      break;
    default:
      break;
  }
}

int input_key() {
  int key = -1;
  switch (getch()) {
    case (10):
      key = Start;
      break;
    case (32):
      key = Action;
      break;
    case (260):
      key = Left;
      break;
    case (261):
      key = Right;
      break;
    case (258):
      key = Down;
      break;
    case (259):
      key = Up;
      break;
    case (81):
    case (113):
      key = Terminate;
      break;
    case (80):
    case (112):
      key = Pause;
      break;
    default:
      key = -1;
      break;
  }
  return key;
}

void game_Pause() {
  GameInfo_t *Game = game_info_struct();
  int key = -1;

  while (key != 80 && key != 112 && Game->pause) {
    key = getch();
  }

  Game->pause = 0;
}