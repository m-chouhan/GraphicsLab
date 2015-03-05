
#include "Simulator.hpp"

Simulator::Reshape(int w,int h)
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

void Simulator::NormalKeyEvent(unsigned char key, int x, int y) {
      
	if (key == 27) exit(0);
}

void Simulator::SpecialKeyEvent(unsigned char key, int x, int y) {

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
void Simulator::MouseEvent(int button, int state, int x, int y)
 {
   if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) { // Pause/resume
      
      int deltax = (SCREEN.bottomX-SCREEN.topX)/2;
      int deltay = (SCREEN.bottomY-SCREEN.topY)/2;
      ::x = x-Width/2,::y = y-Height/2;   
      cout<<"["<<::x<<","<<::y<<"]\n";
      /*paused = !paused;         // Toggle state
      if (paused) {
         xSpeedSaved = xSpeed;  // Save parameters for restore later
         ySpeedSaved = ySpeed;
         xSpeed = 0;            // Stop movement
         ySpeed = 0;
      } else {
         xSpeed = xSpeedSaved;  // Restore parameters
         ySpeed = ySpeedSaved;
      }*/
   }
}
