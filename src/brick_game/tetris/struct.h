#ifndef STRUCT_H
#define STRUCT_H

typedef struct {
  int x;
  int y;
} Block;

typedef struct {
  Block blocks[4];
  Block centre;
  char type;
  int x, y, Num;
} Figure;

typedef enum UserAction_t {
  Start,
  Pause,
  Terminate,
  Left,
  Right,
  Up,
  Down,
  Action
} UserAction_t;

typedef struct GameInfo_t {
  int **field;
  int **next;
  int score;
  int high_score;
  int level;
  int speed;
  int pause;
} GameInfo_t;

typedef struct Status_game {
  int Game_Start;
  int Game_Attaching;
  int Game_Pause;
  int Game_Over;
  int Game_Moving;
  int Game_Spawn;
} Status_game;

#endif