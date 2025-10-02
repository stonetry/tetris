#include "game.h"

int main() {
  init_ncurses();

  if (main_menu() == 1) {
    game_process();
  }
  endwin();
  return 0;
}

int main_menu() {
  Status_game *Status = status_game_struct();
  int key = -1;

  print_main_menu();
  while (key != Start) {
    key = input_key();
  }

  Status->Game_Start = 1;
  return 1;
}

void game_process() {
  Status_game *Status = status_game_struct();

  if (Status->Game_Start) {
    while (1) {
      static clock_t time = 0;
      GameInfo_t Game = updateCurrentState();
      clock_t current_time = clock();

      if (PAUSE) {
        print_pause();
        game_Pause();
      }

      if (((current_time - time) * 1000 / CLOCKS_PER_SEC >= 2) &&
          !(GAME_OVER)) {
        print_map(Game);
        time = current_time;
      }

      if (GAME_OVER) {
        print_game_over();
        int key = -1;
        while (key != 81 && key != 113) {
          key = getch();
        }
        break;
      }
    }
  }
}