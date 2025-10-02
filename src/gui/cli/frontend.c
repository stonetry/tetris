#include "frontend.h"

void init_ncurses() {
  initscr();
  srand(time(NULL));
  cbreak();
  noecho();
  keypad(stdscr, TRUE);
  nodelay(stdscr, TRUE);
  curs_set(FALSE);
}

void print_main_menu() {
  mvprintw(6, 3, "#############################");
  mvprintw(7, 3, "#                           #");
  mvprintw(8, 3, "#                           #");
  mvprintw(9, 3, "#                           #");
  mvprintw(10, 3, "#     Welcome to Tetris     #");
  mvprintw(11, 3, "#                           #");
  mvprintw(12, 3, "#                           #");
  mvprintw(13, 3, "#                           #");
  mvprintw(14, 3, "#        Press enter        #");
  mvprintw(15, 3, "#     to start the game     #");
  mvprintw(16, 3, "#                           #");
  mvprintw(17, 3, "#                           #");
  mvprintw(18, 3, "#                           #");
  mvprintw(19, 3, "#                           #");
  mvprintw(20, 3, "#                           #");
  mvprintw(21, 3, "#############################");
}

void print_map(GameInfo_t Game) {
  clear();

  int start_y = 1;
  int start_x = 2;

  for (int i = 0; i < ROWS + 2; i++) {
    move(start_y + i, start_x);
    for (int j = 0; j < COLS + 2; j++) {
      if (Game.field[i][j] == 1) {
        printw(" #");
      } else if (Game.field[i][j] == 2 || Game.field[i][j] == 3) {
        printw(" *");
      } else if (Game.field[i][j] == 5) {
        printw(" !");
      } else {
        printw("  ");
      }
    }
  }

  int info_start_y = 1;
  int info_start_x = start_x + (COLS + 1) * 2 + 3;

  print_additional_information(Game, info_start_y, info_start_x);

  refresh();
}

void print_additional_information(GameInfo_t Game, int start_y, int start_x) {
  int height = ROWS + 2;
  int width = 14;

  for (int i = 0; i < height; i++) {
    move(start_y + i, start_x);
    for (int j = 0; j < width / 2; j++) {
      if (i == 0 || i == height - 1 || j == (width / 2) - 1) {
        printw("# ");
      } else {
        printw("  ");
      }
    }
  }

  print_next_tetramino(Game, start_y, start_x);

  print_score(Game, start_y, start_x);

  move(start_y + 15, start_x + 1);
  printw("lvl-Speed");
  move(start_y + 17, start_x + 3);
  printw("%d - %d", Game.level, (Game.speed - 530) * -1);
}

void print_score(GameInfo_t Game, int start_y, int start_x) {
  move(start_y + 7, start_x + 3);
  printw("Score");
  move(start_y + 9, start_x + 5);
  printw("%d", Game.score);
  move(start_y + 11, start_x + 1);
  printw("High-Score");
  move(start_y + 13, start_x + 5);
  printw("%d", Game.high_score);
}

void print_next_tetramino(GameInfo_t Game, int start_y, int start_x) {
  move(start_y + 1, start_x);
  printw("Next-Figure");
  move(start_y + 2, start_x);
  for (int i = 0; i < 10; i++) {
    move(start_y + 2 + i, start_x);
    for (int j = 4; j < 10; j++) {
      if (Game.next[i][j] == 2) {
        printw(" *");
      } else {
        printw("  ");
      }
    }
  }
}

void print_pause() {
  mvprintw(8, 3, "#######################");
  mvprintw(9, 3, "#        PAUSE        #");
  mvprintw(10, 3, "#######################");
  refresh();
}

void print_game_over() {
  mvprintw(8, 3, "#######################");
  mvprintw(9, 3, "#      GAME OVER      #");
  mvprintw(10, 3, "#       Press Q       #");
  mvprintw(11, 3, "#       to exit       #");
  mvprintw(12, 3, "#######################");
  refresh();
}