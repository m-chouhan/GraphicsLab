
#include <iostream>
#include "Simulator.hpp"

int Simulator::Width = 400;
int Simulator::Height = 400;
bool Simulator::Pause = false;
//~ ShapeList Simulator::World;
ShapeList2 Simulator::World;

Point3D Simulator::CamVector(0,10,40);
Physics Simulator::PhysicsEngine(20,1.1,0.99);

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
      //Painter.Paint(World);
      //some delay also      
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
                  
                  for(int j = 0;j<size;j+=3)
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

void Simulator::drawSphere(Point3D P,float rad,Color col)
{
      glPushMatrix();
      glColor3f(col.r,col.g,col.b);
      glTranslatef(P.x,P.y,P.z);
      glutSolidSphere(rad,20,20);
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
                  case 'w': 
                                    CamVector = CamVector*0.98f;
                                    break;
                  case 's':
                                    CamVector = CamVector*1.02f;
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
      
      glEnable(GL_COLOR_MATERIAL);
      glEnable(GL_SMOOTH);
      glEnable(GL_LIGHTING);
      glColorMaterial(GL_FRONT,GL_DIFFUSE);
      
      glutInitWindowPosition(100,100);
      glutInitWindowSize(Width,Height);
      glutCreateWindow("So-lLimunation");

      // register callbacks
      glutDisplayFunc(Simulator::RenderScene);
      glutReshapeFunc(Simulator::Reshape);
      glutIdleFunc(Simulator::RenderScene);

      // here are the new entries
      glutKeyboardFunc(Simulator::NormalKeyEvent);
      glutSpecialFunc(Simulator::SpecialKeyEvent);
      glutMouseFunc(Simulator::MouseEvent);
}
