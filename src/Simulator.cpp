
#include <iostream>
#include <assert.h>
#include "Simulator.hpp"

int Simulator::Width = 400;
int Simulator::Height = 400;
bool Simulator::Pause = false;
//~ ShapeList Simulator::World;
ShapeList2 Simulator::World;

Point3D Simulator::CamVector(0,10,40);
Point3D Simulator::LightPos(0,0,05);
Physics Simulator::PhysicsEngine(20,1.1,0.99);

void Simulator::move_light(Point3D pos)
{
      // Create light components 
      GLfloat ambientLight[] = { 0.2f, 0.2f, 0.2f, 1.0f }; 
      GLfloat diffuseLight[] = { 0.8f, 0.8f, 0.8, 1.0f }; 
      GLfloat specularLight[] = { 1.5f, 1.5f, 1.5f, 1.0f }; 
      GLfloat position[] = { pos.x, pos.y, pos.z, 1.0f }; 
      
      // Assign created components to GL_LIGHT0 
      glLightfv(GL_LIGHT0, GL_AMBIENT, ambientLight); 
      glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuseLight); 
      glLightfv(GL_LIGHT0, GL_SPECULAR, specularLight); 
      glLightfv(GL_LIGHT0, GL_POSITION, position);
}

void Simulator::Reshape(int w,int h)
{
      if (h == 0)
            h = 1;
      float ratio =  w * 1.0 / h;
      Width = w,Height = h;
        // Use the Projection Matrix
      glMatrixMode(GL_PROJECTION);
        // Reset Matrix
      glLoadIdentity();
      // Set the viewport to be the entire window
      glViewport(0, 0, w, h);
      // Set the correct perspective.
      gluPerspective(45.0f, ratio, 0.1f, 100.0f);
      // Get Back to the Modelview
      glMatrixMode(GL_MODELVIEW);
}

void Simulator::RenderScene()
{
      if(!Pause) PhysicsEngine.Update(World);
      
      glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	// Reset transformations
	glLoadIdentity();
      
      gluLookAt(	CamVector.x, CamVector.y, CamVector.z,
                              0, 0,  0,
                              0.0f, 1.0 ,0.0f);

      for(int i = 0;i<World.size();++i)
      {
            World[i].first->Draw();
            if(  Sphere *s = dynamic_cast<Sphere *>(World[i].first) )
            {
                  int size = World[i].second.Q.size();
                  float radius = s->getRad()*0.7;
                  Color color = s->col;
                  color.r = color.r *0.5;
                  color.g = color.g *0.5;
                  color.b = color.b*0.5;
                  
                  color.r = 0.2;
                  color.g = 0.2;
                  color.b = 0.2;
                  
                  for(int j = 0;j<size;j+=1)
                  {
                        drawSphere(World[i].second.Q[j], j*radius/size,color );
                        color.r = color.g = color.b = color.r*1.3;
                  }
            }
      }
      
      draw2DFrame();
      glRotatef(90, 1.0f, 0.0f, 0.0f);
      draw2DFrame();

      glEnable(GL_DEPTH_TEST);
	glutSwapBuffers();
}

void Simulator::drawCube(Cube &c)
{
      glPushMatrix();
      glutWireCube(c.length);
      glPopMatrix();
}

//~ void Simulator::drawSphere(Sphere &s)
//~ {
      //~ Point3D loc =  s.getOrigin();
      //~ glPushMatrix();
      //~ glColor3f(s.col.r,s.col.g,s.col.b);
      //~ glTranslatef(loc.x,loc.y,loc.z);
      //~ glutSolidSphere(s.getRad(),30,30);
      //~ glPopMatrix();
//~ }

void Simulator::drawSphere(Point3D P,float rad,Color col,bool light)
{
      glPushMatrix();

      glColor3f(col.r,col.g,col.b);
      glTranslatef(P.x,P.y,P.z);

      
      if(light)
      {
            //~ Material properties
            GLfloat emissiveLight[] = { 1.2f, 1.2f, 1.2f}; 
            move_light(Point3D());
            glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, emissiveLight);
            glutSolidSphere(rad,20,20);
            emissiveLight[0] = emissiveLight[1] = emissiveLight[2]  = 0;
            glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, emissiveLight);
      }

      else glutSolidSphere(rad,20,20);
      glPopMatrix();
}

void Simulator::draw2DFrame()
{
      glBegin(GL_LINES);
      glColor3f(0,0.5,0);
      for(int i = 0;i<40;i++)
      {
            glVertex3f(-20.0f+i, 20.0f, 0);
		glVertex3f(-20.0f+i, -20.0f,0);
		
            glVertex3f( -20.0f, -20.0f+i,0);
		glVertex3f( 20.0f, -20.0f+i, 0);
      }
      glEnd();
}

void Simulator::NormalKeyEvent(unsigned char key, int x, int y) {
      
	if (key == 27) exit(0);
      //std::cout<<"["<<key<<"]";
      switch(key)
      {
                  case ' ' :   //CamVector = CamVector*1.02f;
                                    Pause = !Pause; 
                                    std::cout<<"space";
                                    break;
                  case  'i':   LightPos.x+=0.1;
                                    break;
                  case 'j':   LightPos.y+=0.1;
                                    break;
                  case 'k':   LightPos.x-=0.1;
                                    break;
                  case 'l':     LightPos.y-=0.1;
                                    break;                 
                  case 'w': 
                                    LightPos.z -= 0.1;
                                    //~ CamVector = CamVector*0.98f;
                                    break;
                  case 's':   LightPos.z+=0.1;
                                    //~ CamVector = CamVector*1.02f;
                                    break;                              
                  case'a': case 'd':
                                    std::cout<<"["<<key<<"]";
                                    break;
      }
}

void Simulator::SpecialKeyEvent(int key, int x, int y) {

	switch (key) {
		case GLUT_KEY_LEFT :
                  CamVector.RotateXYZ(0,2,0);
			break;
		case GLUT_KEY_RIGHT :
                  CamVector.RotateXYZ(0,-2,0);
			break;
		case GLUT_KEY_UP :
                  CamVector.RotateXYZ(2,0,0);
			break;
		case GLUT_KEY_DOWN :
                  CamVector.RotateXYZ(-2,0,0);                  
			break;
	}
}
/* Callback handler for mouse event */
void Simulator::MouseEvent(int button, int state, int x, int y)
 {
      /*
      if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) { 
            int deltax = (SCREEN.bottomX-SCREEN.topX)/2;
            int deltay = (SCREEN.bottomY-SCREEN.topY)/2;
            ::x = x-Width/2,::y = y-Height/2;   
            cout<<"["<<::x<<","<<::y<<"]\n";
      }*/
      std::cout<<"["<<x<<","<<y<<"]\n";
}

void Simulator::SimulatorInit(int argc, char *argv[],int W,int H)
{
      Width = W;Height = H;
      // init GLUT and create window
      glutInit(&argc, argv);
      glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
      
      glutInitWindowPosition(100,100);
      glutInitWindowSize(Width,Height);
      glutCreateWindow("So-lLimunation");
      //~ GLfloat light_position[] = { LightPos.x,LightPos.y, LightPos.z, 1 };
      //~ GLfloat white_light[] = { 1.5, 1.0, 1.3, 1.0 };
      //~ GLfloat lmodel_ambient[] = { 0.5, 0.0, 0.0, 1.0 };
      //~ glClearColor(0.0, 0.0, 0.0, 0.0);
      //~ glEnable(GL_SMOOTH);
      //~ glLightfv(GL_LIGHT0, GL_POSITION, light_position);
      //~ glLightf(GL_LIGHT0, GL_CONSTANT_ATTENUATION, 1.0);
      //~ glLightf(GL_LIGHT0, GL_LINEAR_ATTENUATION, 0.5);
      //~ glLightf(GL_LIGHT0, GL_QUADRATIC_ATTENUATION, 0.3);
      //~ glLightfv(GL_LIGHT0, GL_DIFFUSE, white_light);
      //~ glLightfv(GL_LIGHT0, GL_SPECULAR, white_light);
      //~ glLightModelfv(GL_LIGHT_MODEL_AMBIENT, lmodel_ambient);
      glEnable(GL_LIGHTING);
      glEnable(GL_LIGHT0);      
      glEnable(GL_LIGHT1);      
      glEnable(GL_NORMALIZE);
      glEnable(GL_SMOOTH);
      glEnable(GL_COLOR_MATERIAL);
      //glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);

      float spec[4] = { 0.75, 0.75, 0.75, 1 };
      float diff[4] = { 0.75, 0.75, 0, 1 };
      glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, spec);
      glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, diff);

      glMateriali(GL_FRONT, GL_SHININESS, 52);
      //~ GLfloat ambientColor[] = {1.2f, 1.2f, 1.2f, 1.0f}; //Color(0.2, 0.2, 0.2)
      //~ glLightModelfv(GL_LIGHT_MODEL_AMBIENT, ambientColor);
      //~ float mcolor[] = { 1.0f, 0.0f, 0.0f, 1.0f };
      //~ glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, mcolor);
      
      // register callbacks
      glutDisplayFunc(Simulator::RenderScene);
      glutReshapeFunc(Simulator::Reshape);
      glutIdleFunc(Simulator::RenderScene);

      glutKeyboardFunc(Simulator::NormalKeyEvent);
      glutSpecialFunc(Simulator::SpecialKeyEvent);
      glutMouseFunc(Simulator::MouseEvent);
}
