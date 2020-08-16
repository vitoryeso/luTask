all: luTask

luTask: src/main_simple.cpp
	g++ src/main_curses.cpp src/luTask.cpp src/luTaskWindows.cpp src/luUtils.cpp -o luTask -lncurses

update:
	rm ~/luTask && mv luTask ~/
