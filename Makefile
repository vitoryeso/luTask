all: luTask

luTask: src/main_simple.cpp
	g++ src/main_curses.cpp src/luTask.cpp src/luTaskWindows.cpp -o luTask -lluUtils -lncurses

update:
	rm ~/luTask && mv luTask ~/
