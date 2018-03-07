CC=mingw32-g++
CFLAGS=-Wall -std=c++11 -O3
INCLUDE_DIR=-IC:\Users\nooby\Desktop\Downloads\CodeBlocks16\UnitTest++\unittest-cpp-master\UnitTest++ -IC:\Users\nooby\Desktop\Downloads\CodeBlocks16\EXTRA_moodle\glfw-2.7.bin.WIN32\include 
Files=main.cpp Cube.cpp CubeSide.cpp GUI.cpp UnitTests.cpp Utilities.cpp
libs=-lglfw -lopengl32 -lglu32 -lgdi32 -lUnitTest++
LINK_DIR=-LC:\Users\nooby\Desktop\Downloads\CodeBlocks16\UnitTest++\unittest-cpp-master\Deliv\Release -LC:\Users\nooby\Desktop\Downloads\CodeBlocks16\EXTRA_moodle\glfw-2.7.bin.WIN32\lib

all:
	${CC} ${Files} -o cube ${CFLAGS} ${INCLUDE_DIR} ${LINK_DIR} ${libs}