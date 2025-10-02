#include "field.h"

GameInfo_t *game_info_struct() {
  static GameInfo_t game_info = {0};
  return &game_info;
}

Figure *tetramino_struct() {
  static Figure tetramino = {0};
  return &tetramino;
}

Status_game *status_game_struct() {
  static Status_game status = {0};
  return &status;
}