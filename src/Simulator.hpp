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
#include "imageloader.h"

enum Planets{
            Moon,Earth,Earth3,Neptune,Background,Sun
      };

class Simulator {
      
            public:
            static GLuint TextureIds[15];
            static int Width,Height,WorldSize;
            static bool Pause;
            static std::vector<Sphere *> Stars;
            static ShapeList2 World;
            static Point3D CamVector;
            static Point3D LightPos;
            static Physics PhysicsEngine;
            static GLUquadric *quad;

            static void Reshape(int w, int h) ;
            static void RenderScene(void);
            static void NormalKeyEvent(unsigned char key, int x, int y) ;
            static void SpecialKeyEvent(int key, int x, int y) ;
            static void MouseEvent(int button, int state, int x, int y);
            static void drawSphere(Point3D P,float rad,Color col,bool light=false);
            static void drawCube(Cube &c);
            static void draw2DFrame(void);
            static void move_light(Point3D pos);
            static GLuint loadTexture(Image* image);
            
            static void StartSimulation(void) 
            {     
                  PhysicsEngine.CollisionManager(World);
                  std::cout<<"\n\n\n";
                  PhysicsEngine.Update(World);
                  //~ Init Dynamics Values
                  glutMainLoop(); 
            }
            static void AddObject(Sphere *s,Planets id = Earth)
            {
                  s->TextureID = TextureIds[id];
                  s->Quad = quad;
                  World.push_back(std::make_pair(s,FifoQ(14)));
                  //~ PhysicsEngine.CollisionManager(World);
            }
            static void AddLighSource(Sphere *s)
            {
                  s->light = true;
                  s->TextureID = TextureIds[Sun];
                  Stars.push_back(s);
            }
            static void ApplyLights()
            {
                        // Create light components 
                  float ambi = 0.10,diffuse = 5.0,spec = 1.0;
                        
                  GLfloat ambientLight[] = { ambi, ambi, ambi, 1.0f }; 
                  GLfloat diffuseLight[] = { diffuse, diffuse, diffuse, 1.0f }; 
                  GLfloat specularLight[] = { spec, spec, spec, 1.0f }; 

                  for(unsigned int i = 0;i<Stars.size();++i)
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
