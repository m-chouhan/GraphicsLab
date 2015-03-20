#ifndef __SIMULATION__
#define __SIMULATION__

#include <stdlib.h>
#include <GL/glut.h>
#include <utility>
#include <vector>

#include "Shape.h"
#include "graphics.h"
#include "Sphere.hpp"
#include "Cube.hpp"
#include "Physics.hpp"


class Simulator {
      
            public:
            static int Width,Height;
            static bool Pause;
            //static ShapeList World;
            static ShapeList2 World;
            static Point3D CamVector;
            static Physics PhysicsEngine;
            
            static void Reshape(int w, int h) ;
            static void RenderScene(void);
            static void NormalKeyEvent(unsigned char key, int x, int y) ;
            static void SpecialKeyEvent(int key, int x, int y) ;
            static void MouseEvent(int button, int state, int x, int y);
            //~ static void drawSphere(Sphere &s);
            static void drawSphere(Point3D P,float rad,Color col);
            static void drawCube(Cube &c);
            static void draw2DFrame(void);
            static void move_light(GLfloat l_position[]);
            static void StartSimulation(void) 
            {     
                  PhysicsEngine.Update(World);
                  //~ Init Dynamics Values
                  glutMainLoop(); 
            }
            static void AddObject(Shape *s)
            {
                  World.push_back(std::make_pair(s,FifoQ(20)));
            }
            static void SimulatorInit(int argc, char *argv[],int W,int H);
};            
#endif
