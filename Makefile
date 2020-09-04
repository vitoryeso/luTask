all: luTask

luTask: src/main_curses.cpp
	g++ src/main_curses.cpp src/luTask.cpp src/luTaskWindows.cpp src/luUtils.cpp -o luTask -lncurses

clear:
	rm luTask
