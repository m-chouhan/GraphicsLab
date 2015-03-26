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
            static std::vector<Sphere *> Stars;
            static ShapeList2 World;
            static Point3D CamVector;
            static Point3D LightPos;
            static Physics PhysicsEngine;
            
            static void Reshape(int w, int h) ;
            static void RenderScene(void);
            static void NormalKeyEvent(unsigned char key, int x, int y) ;
            static void SpecialKeyEvent(int key, int x, int y) ;
            static void MouseEvent(int button, int state, int x, int y);
            static void drawSphere(Point3D P,float rad,Color col,bool light=false);
            static void drawCube(Cube &c);
            static void draw2DFrame(void);
            static void move_light(Point3D pos);
            static void StartSimulation(void) 
            {     
                  PhysicsEngine.Update(World);
                  //~ Init Dynamics Values
                  glutMainLoop(); 
            }
            static void AddObject(Shape *s)
            {
                  World.push_back(std::make_pair(s,FifoQ(15)));
            }
            static void AddLighSource(Sphere *s)
            {
                  s->light = true;
                  Stars.push_back(s);
            }
            static void ApplyLights()
            {
                        // Create light components 
                  GLfloat ambientLight[] = { 0.1f, 0.1f, 0.1f, 1.0f }; 
                  GLfloat diffuseLight[] = { 0.8f, 0.8f, 0.8, 1.0f }; 
                  GLfloat specularLight[] = { 1.5f, 1.5f, 1.5f, 1.0f }; 

                  for(int i = 0;i<Stars.size();++i)
                  {
                        Point3D pos = Stars[i]->getOrigin();
                        GLfloat position[] = { pos.x, pos.y, pos.z, 1.0f }; 
                        
                        // Assign created components to GL_LIGHT0 
                        glLightfv(GL_LIGHT0+i, GL_AMBIENT, ambientLight); 
                        glLightfv(GL_LIGHT0+i, GL_DIFFUSE, diffuseLight); 
                        glLightfv(GL_LIGHT0+i, GL_SPECULAR, specularLight); 
                        glLightfv(GL_LIGHT0+i, GL_POSITION, position);                        
                  }
            }
            static void SimulatorInit(int argc, char *argv[],int W,int H);
};            
#endif
