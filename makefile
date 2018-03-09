CC=mingw32-g++
CFLAGS=-Wall -std=c++11 -O3 -static

SOURCE_DIR=source
DEPEND_DIR=.\Dependencies
INCLUDE_DIR=.\include
OUTPUT_DIR=build

Files= ${SOURCE_DIR}\main.cpp ${SOURCE_DIR}\Cube.cpp ${SOURCE_DIR}\CubeSide.cpp ${SOURCE_DIR}\GUI.cpp ${SOURCE_DIR}\UnitTests.cpp ${SOURCE_DIR}\Utilities.cpp
libs=-lglfw -lopengl32 -lglu32 -lgdi32 -lUnitTest++
INCLUDE_DIRS=-I${DEPEND_DIR}\UnitTest++\unittest-cpp-master\UnitTest++ -I${DEPEND_DIR}\glfw-2.7.bin.WIN32\include -I${INCLUDE_DIR}
LINK_DIRS=-L${DEPEND_DIR}\UnitTest++\unittest-cpp-master\Deliv\Release -L${DEPEND_DIR}\glfw-2.7.bin.WIN32\lib

all:
	${CC} ${Files} -o ${OUTPUT_DIR}\cube ${CFLAGS} ${INCLUDE_DIRS} ${LINK_DIRS} ${libs}