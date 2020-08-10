all: luTask

luTask: src/main_simple.cpp
	g++ src/main_simple.cpp src/luTask.cpp -o luTask -lluUtils

update:
	rm ~/luTask && mv luTask ~/
