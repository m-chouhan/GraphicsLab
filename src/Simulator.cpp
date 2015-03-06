
#include <iostream>
#include "Simulator.hpp"

//~ int Simulator::Width = 200;
//~ int Simulator::Height = 200;
//~ ShapeList Simulator::World;

void Reshape(int w,int h)
{
      // Prevent a divide by zero, when window is too short
      // (you cant make a window of zero width).
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

      for(int i = 0;i<World.size();++i)
      {
            if( Cube *c = dynamic_cast<Cube *>( World[i] ) ) 
                  drawCube(*c);
            if( Sphere *s = dynamic_cast<Sphere *>( World[i]) )
                  drawSphere(*s);
      }/* */
      
      glEnable(GL_DEPTH_TEST);
	glutSwapBuffers();
      sleep(20);
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
      glutWireSphere(0.6,20,20);
      glPopMatrix();
      //std::cout<<"printing"<<loc;
}

void NormalKeyEvent(unsigned char key, int x, int y) {
      
	if (key == 27) exit(0);
}

void SpecialKeyEvent(int key, int x, int y) {

	switch (key) {
		case GLUT_KEY_LEFT :
			break;
		case GLUT_KEY_RIGHT :
			break;
		case GLUT_KEY_UP :
			break;
		case GLUT_KEY_DOWN :
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
                  //::Width = W;::Height = H;
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
                  //glutKeyboardFunc(Simulator::NormalKeyEvent);
                  glutSpecialFunc(SpecialKeyEvent);
                  glutMouseFunc(MouseEvent);
            }
