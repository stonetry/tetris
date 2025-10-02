CC = gcc
CFLAGS = -Wall -Wextra -Werror 
NCFLAG = -lncurses
LIB_SOURCES = brick_game/tetris/backend.c brick_game/tetris/struct.c brick_game/tetris/actions.c brick_game/tetris/field.c brick_game/tetris/help_backend_func.c brick_game/tetris/moving.c brick_game/tetris/tetramino_gen.c
MAIN_SOURCES = brick_game/tetris/game.c
GUI_SOURCES = gui/cli/*.c

LIBS = $(shell pkg-config --libs check)
LDFLAGS = -lcheck
GCOVFLAGS = -fprofile-arcs -ftest-coverage
SRC_TEST = brick_game_test/test.c

DVI_DIR = dvi
README_SRC = $(DVI_DIR)/README.md
PDF_OUTPUT = $(DVI_DIR)/Documentation.pdf

VERSION = 1.0
NAME = brickgame-tetris
DIST_DIR = $(NAME)-$(VERSION)
DIST_FILES = Makefile dvi/ brick_game/ gui/ backend_test/

.PHONY: all style install uninstall clean dvi dist

all: install

install: lib_tetris.a
	$(CC) $(CFLAGS) $(MAIN_SOURCES) $(GUI_SOURCES) game/lib_tetris.a $(NCFLAG) -o game/tetris

uninstall: 
	rm -rf game

# test: clean
# 	$(CC) $(LDFLAGS) $(SRC_TEST) game/lib_tetris.a -o test $(LIBS) $(NCFLAG)
# 	./test

gcov_report:
	$(CC) $(GCOVFLAGS) $(SRC_TEST) $(LIB_SOURCES) -o gcov.out $(LIBS) $(NCFLAG)
	./gcov.out 
	lcov --capture --directory . --output-file coverage.info
	genhtml coverage.info --output-directory coverage_report

dvi: $(README_SRC) $(DVI_DIR)/Finite_State_Machine.png
	pandoc -s $(README_SRC) -o $(PDF_OUTPUT) \
	--resource-path=$(DVI_DIR) \
	--pdf-engine=xelatex \
	-V mainfont="DejaVu Serif" \
	-V geometry:margin=2cm
	@echo "PDF document created at $(PDF_OUTPUT)"

dist:
	mkdir $(DIST_DIR)
	cp -r $(DIST_FILES) $(DIST_DIR)
	tar -czf $(NAME)-$(VERSION).tar.gz $(DIST_DIR)
	rm -rf $(DIST_DIR)
	@echo "Distribution package created: $(NAME)-$(VERSION).tar.gz"

lib_tetris.a:
	mkdir -p game
	$(CC) $(CFLAGS) -c $(LIB_SOURCES)
	ar rcs lib_tetris.a *.o
	mv lib_tetris.a game/lib_tetris.a

clean:
	rm -rf *.o *.a *.gcda *.gcno .scores.txt coverage.info coverage_report tetris.info gcov.out report dvi/documentation.pdf brickgame-tetris-1.0 brickgame-tetris-1.0.tar.gz

v: test
	CK_FORK=no valgrind --tool=memcheck --leak-check=yes --log-file="temp" ./test
