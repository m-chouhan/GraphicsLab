
#include <iostream>
#include <assert.h>
#include "Simulator.hpp"

int Simulator::Width = 400;
int Simulator::Height = 400;
int Simulator::WorldSize = 200;
bool Simulator::Pause = true;
GLuint Simulator::TextureIds[15]; //The id of the textur

GLUquadric *Simulator:: quad;

//~ ShapeList Simulator::World;
ShapeList2 Simulator::World;
std::vector<Sphere *> Simulator::Stars;

Point3D Simulator::CamVector(0,10,140);
Point3D Simulator::LightPos(0,0,05);
Physics Simulator::PhysicsEngine(20,1.02,0.995,Simulator::WorldSize);

void Simulator::move_light(Point3D pos)
{
      // Create light components 
      GLfloat ambientLight[] = { 0.1f, 0.1f, 0.1f, 1.0f }; 
      GLfloat diffuseLight[] = { 0.8f, 0.8f, 0.8, 1.0f }; 
      GLfloat specularLight[] = { 1.5f, 1.5f, 1.5f, 1.0f }; 
      GLfloat position[] = { pos.x, pos.y, pos.z, 1.0f }; 
      assert(0);
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
      gluPerspective(45.0f, ratio, 0.1f, 1600.0f);
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
      
      ApplyLights();
      
      for(int i = 0;i<World.size();++i)
      {
            World[i].first->Draw();
            if(  Sphere *s = dynamic_cast<Sphere *>(World[i].first) )
            {
                  int size = World[i].second.Q.size();
                  float radius = s->getRad()*0.65;
                  Color color = s->col;
                  color.r = color.r *0.5;
                  color.g = color.g *0.5;
                  color.b = color.b*0.5;
                  
                  color.r = 0.2;
                  color.g = 0.2;
                  color.b = 0.2;
                  /**/
                  for(int j = 0;j<size;j+=1)
                  {
                        drawSphere(World[i].second.Q[j], j*radius/size,color );
                        color.r = color.g = color.b = color.r*1.3;
                  } /**/
            }
      }
      
      glColor3f(0.7,0.7,0.7);      
      glutWireSphere(WorldSize,30,30);
      
      glBindTexture(GL_TEXTURE_2D, TextureIds[Background]);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
      glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
      glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

      gluQuadricTexture(quad,GLU_TRUE);

      gluSphere(quad,WorldSize+450,20,20);

      //~ draw2DFrame();
      //~ glRotatef(90, 1.0f, 0.0f, 0.0f);
      //~ draw2DFrame();

      glEnable(GL_DEPTH_TEST);
	glutSwapBuffers();
      /**/ 
}

void Simulator::drawCube(Cube &c)
{
      glPushMatrix();
      glutWireCube(c.length);
      glPopMatrix();
}

void Simulator::drawSphere(Point3D P,float rad,Color col,bool light)
{
      glPushMatrix();
      glColor3f(col.r,col.g,col.b);
      glTranslatef(P.x,P.y,P.z);
      
      //~ gluQuadricTexture(quad,GLU_TRUE);
      //~ gluSphere(quad,rad,20,20);
      glutSolidSphere(rad,5,5);
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
                                    CamVector = CamVector*0.98f;
                                    break;
                  case 's':   LightPos.z+=0.1;
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
      
      glutInitWindowPosition(100,100);
      glutInitWindowSize(Width,Height);
      glutCreateWindow("So-lLimunation");
      
      glEnable(GL_DEPTH_TEST);
	quad = gluNewQuadric();
      gluQuadricTexture(quad,GLU_TRUE);

	Image* image = loadBMP("Textures/sun1.bmp");
	TextureIds[Sun] = loadTexture(image);
      delete image;
      image = loadBMP("Textures/earth.bmp");
      TextureIds[Earth] = loadTexture(image);
      delete image;
      //~ image = loadBMP("earth.bmp");
      //~ TextureIds[Earth] = loadTexture(image);
      //~ delete image;
      //~ image = loadBMP("universe2.bmp");
      //~ TextureIds[Mars] = loadTexture(image);
      //~ delete image;
      image = loadBMP("Textures/earth3.bmp");
      TextureIds[Earth3] = loadTexture(image);
      delete image;
      //~ image = loadBMP("earth4.bmp");
      //~ TextureIds[Earth4] = loadTexture(image);
      //~ delete image;
      //~ image = loadBMP("mars1.bmp");
      //~ TextureIds[Mars] = loadTexture(image);
      //~ delete image;
      image = loadBMP("Textures/saturn.bmp");
      TextureIds[Moon] = loadTexture(image);
      delete image;
      image = loadBMP("Textures/neptune.bmp");
      TextureIds[Neptune] = loadTexture(image);
      delete image;
      image = loadBMP("Textures/universe3.bmp");
      TextureIds[Background] = loadTexture(image);
      delete image;
      
	glEnable(GL_TEXTURE_2D);

      
      glEnable(GL_LIGHTING);
      
      /*Enable All 8 lights*/
      glEnable(GL_LIGHT0);      
      glEnable(GL_LIGHT1);      
      glEnable(GL_LIGHT2);      
      glEnable(GL_LIGHT3);      
      glEnable(GL_LIGHT4);      
      glEnable(GL_LIGHT5);      
      glEnable(GL_LIGHT6);      
      glEnable(GL_LIGHT7);
            
      glEnable(GL_NORMALIZE);
      glEnable(GL_SMOOTH);
      glEnable(GL_COLOR_MATERIAL);
      //glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);

      float spec[4] = { 0.75, 0.75, 0.75, 1 };
      float diff[4] = { 0.75, 0.75, 0, 1 };
      glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, spec);
      glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, diff);

      glMateriali(GL_FRONT_AND_BACK, GL_SHININESS, 28);
      //~ GLfloat ambientColor[] = {1.2f, 1.2f, 1.2f, 1.0f}; //Color(0.2, 0.2, 0.2)
      //~ glLightModelfv(GL_LIGHT_MODEL_AMBIENT, ambientColor);
      
      // register callbacks
      glutDisplayFunc(Simulator::RenderScene);
      glutReshapeFunc(Simulator::Reshape);
      glutIdleFunc(Simulator::RenderScene);

      glutKeyboardFunc(Simulator::NormalKeyEvent);
      glutSpecialFunc(Simulator::SpecialKeyEvent);
      glutMouseFunc(Simulator::MouseEvent);
}

GLuint Simulator::loadTexture(Image* image) {
	GLuint textureId;
	glGenTextures(1, &textureId); //Make room for our texture
	glBindTexture(GL_TEXTURE_2D, textureId); //Tell OpenGL which texture to edit
	//Map the image to the texture
	glTexImage2D(GL_TEXTURE_2D,                //Always GL_TEXTURE_2D
				 0,                            //0 for now
				 GL_RGB,                       //Format OpenGL uses for image
				 image->width, image->height,  //Width and height
				 0,                            //The border of the image
				 GL_RGB, //GL_RGB, because pixels are stored in RGB format
				 GL_UNSIGNED_BYTE, //GL_UNSIGNED_BYTE, because pixels are stored
				                   //as unsigned numbers
				 image->pixels);               //The actual pixel data
	return textureId; //Returns the id of the texture
}
