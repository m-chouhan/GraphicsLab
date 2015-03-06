#ifndef __SIMULATION__
#define __SIMULATION__

#include <stdlib.h>
#include <GL/glut.h>

#include "Shape.h"
#include "Sphere.hpp"
#include "Cube.hpp"

class Simulator {
            public:
            static int Width,Height;
            static ShapeList World;
            static Point3D CamVector;

            static void Reshape(int w, int h) ;
            static void RenderScene(void);
            static void NormalKeyEvent(unsigned char key, int x, int y) ;
            static void SpecialKeyEvent(int key, int x, int y) ;
            static void MouseEvent(int button, int state, int x, int y);
            static void drawSphere(Sphere &s);
            static void drawCube(Cube &c);
            static void draw2DFrame(void);

            static void SimulatorInit(int argc, char *argv[],int W,int H);
};            
#endif
