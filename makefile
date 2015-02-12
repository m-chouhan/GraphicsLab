
CC = g++
CFLAGS = -g -Wall

src/graphics.o : src/graphics.cpp src/graphics.h
	${CC} ${CFLAGS} -c src/graphics.cpp
src/Shape.o : src/Shape.cpp src/Shape.h
	${CC} ${CFLAGS} -c src/Shape.cpp
src/Point3D.o : src/Point3D.cpp src/Point3D.h
	${CC} ${CFLAGS} -c src/Point3D.cpp
cube14 :
	${CC} ${CFLAGS} cube14.cpp src/graphics.o src/Shape.o src/Point3D.o -o cube14
all:
	${CC} ${CFLAGS} -c src/graphics.cpp src/Shape.cpp src/Point3D.cpp
clear:
	rm src/*.o
