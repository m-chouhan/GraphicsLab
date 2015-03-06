
#include <iostream>
#include "Simulator.hpp"

int Width = 400;
int Height = 400;
ShapeList World;
Point3D CamVector(0,0,30);

void Reshape(int w,int h)
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

void RenderScene()
{
      //PhysicsEngine.Update(World);
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
            if( Cube *c = dynamic_cast<Cube *>( World[i] ) ) 
                  drawCube(*c);
            if( Sphere *s = dynamic_cast<Sphere *>( World[i]) )
                  drawSphere(*s);
      }/* */
      
      draw2DFrame();
      glRotatef(90, 1.0f, 0.0f, 0.0f);
      draw2DFrame();

      glEnable(GL_DEPTH_TEST);
	glutSwapBuffers();
}

void drawCube(Cube &c)
{
      glPushMatrix();
      glutWireCube(c.length);
      glPopMatrix();
}

void drawSphere(Sphere &s)
{
      Point3D loc =  s.getOrigin();
      glPushMatrix();
      glColor3f(1,1,0.5);
      glTranslatef(loc.x,loc.y,loc.z);
      glutWireSphere(s.getRad(),30,30);
      glPopMatrix();
      //s.Translate(Point3D(0.1,0.1,0));
      //std::cout<<"\npos"<<loc;
}
void draw2DFrame()
{
      glBegin(GL_LINES);
      glColor3f(0,1,0);
      for(int i = 0;i<40;i++)
      {
            glVertex3f(-20.0f+i, 20.0f, 0);
		glVertex3f(-20.0f+i, -20.0f,0);
		
            glVertex3f( -20.0f, -20.0f+i,0);
		glVertex3f( 20.0f, -20.0f+i, 0);
      }
      glEnd();
}

void NormalKeyEvent(unsigned char key, int x, int y) {
      
	if (key == 27) exit(0);
      //std::cout<<"["<<key<<"]";
      switch(key)
      {
                  case ' ' :   //CamVector = CamVector*1.02f;
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

void SpecialKeyEvent(int key, int x, int y) {

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
void MouseEvent(int button, int state, int x, int y)
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

void SimulatorInit(int argc, char *argv[],int W,int H)
      {
            Width = W;Height = H;
            // init GLUT and create window
            glutInit(&argc, argv);
            glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
            glutInitWindowPosition(100,100);
            glutInitWindowSize(Width,Height);
            glutCreateWindow("So-lLimunation");

            // register callbacks
            glutDisplayFunc(RenderScene);
            glutReshapeFunc(Reshape);
            glutIdleFunc(RenderScene);

            // here are the new entries
            glutKeyboardFunc(NormalKeyEvent);
            glutSpecialFunc(SpecialKeyEvent);
            glutMouseFunc(MouseEvent);
      }
