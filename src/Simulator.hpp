#ifndef __SIMULATION__
#define __SIMULATION__

class Simulator{
            
            int Width,Height;
            void Reshape(int w, int h) ;
            void RenderScene();
            void NormalKeyEvent(unsigned char key, int x, int y) 
            void SpecialKeyEvent(unsigned char key, int x, int y) ;
            void MouseEvent(int button, int state, int x, int y);
            
            public:
            Simulator(int argc, char *argv[],int Width,int Height):Width(Width),Height(Height)
            {
                  // init GLUT and create window
                  glutInit(&argc, argv);
                  glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
                  glutInitWindowPosition(100,100);
                  glutInitWindowSize(Width,Height);
                  glutCreateWindow("SolaIumation");

                  // register callbacks
                  glutDisplayFunc(Simulator::RenderScene);
                  glutReshapeFunc(Simulator::Reshape);
                  glutIdleFunc(Simulator::RenderScene);

                  // here are the new entries
                  glutKeyboardFunc(Simulator::NormalKeyEvent);
                  glutSpecialFunc(Simulator::SpecialKeyEvent);
                  glutMouseFunc(Simulator::MouseEvent);
            }
            
            void StartSimulation()
            {                  
                  glutMainLoop();
            }
};

#endif
