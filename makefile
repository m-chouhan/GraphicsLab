
CC = g++
CFLAGS = -g -Wall
GLUTF = -lglut -lGL -l GLU 

SOURCE = src
.PHONY : lib
lib:
	$(MAKE) -C $(SOURCE) lib
cube14 :
	${CC} ${CFLAGS} cube14.cpp src/*.o ${GLUTF} -o exec/cube14
rcube :
	${CC} ${CFLAGS} randomCubes.cpp src/*.o -o exec/rcube
polygon:
	${CC} ${CFLAGS} polygon.cpp src/*.o -o exec/polygon
opagl:  pb1.cpp
	${CC} ${CFLAGS} pb1.cpp ${GLUTF} -o opagl
glplay: glplay.cpp
	${CC} ${CFLAGS} glplay.cpp ${GLUTF} -o glplay
snowman: snowman.cpp
	${CC} ${CFLAGS} snowman.cpp ${GLUTF} -o snowman
spheres:spheres.cpp src/*.cpp src/*.hpp src/*.h	
	${CC} ${CFLAGS} spheres.cpp src/*.o ${GLUTF} -o spheres
clean:
	rm src/*.o
	rm exec/*
