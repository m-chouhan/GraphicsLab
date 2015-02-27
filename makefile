
CC = g++
CFLAGS = -g -Wall

SOURCE = src
.PHONY : lib
lib:
	$(MAKE) -C $(SOURCE) lib
cube14 :
	${CC} ${CFLAGS} cube14.cpp src/graphics.o src/Shape.o src/Point3D.o -o exec/cube14
rcube :
	${CC} ${CFLAGS} randomCubes.cpp src/graphics.o src/Shape.o src/Point3D.o -o exec/rcube
polygon:
	${CC} ${CFLAGS} polygon.cpp src/graphics.o src/Shape.o src/Point3D.o src/Dcel.o -o exec/polygon
opagl:  pb1.cpp
	${CC} ${CFLAGS} pb1.cpp -lglut -lGLU -o opagl
clean:
	rm src/*.o
	rm exec/*
