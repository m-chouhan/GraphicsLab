/*
 * Following program reads input from cube.obj file
 * and then scales and rotates the cube according to input
 * and generates .svg file
 * Author: Mahendra Chouhan (14CS60R12)
 * */
 
#include <iostream>
#include <math.h>
#include <fstream>
#include <stdlib.h>

#include "src/graphics.h"
#include "src/Cube.hpp"

using namespace std;

int  main(int argc,char *argv[])
{ 
      Cube c("cube.txt");
	if(argc < 6)
      { 
            //c.Rotate(210,30,30);
            c.Scale(3.2);
            c = c.Project(Point3D(600,600,100));
            c.writeHidden("projectHidden.svg");	
      }
      
      else
      {
            //float S = atof(argv[1]);
            Point3D orig(atof(argv[1]),atof(argv[2]),atof(argv[3]));
            
            float degx = atoi(argv[4]);
            float degy = atoi(argv[5]);
            float degz = atoi(argv[6]);
            
            c.Rotate(degx,degy,degz);
            c.Move(orig);
            //c.Scale();
            //c.ProjectHidden("projectHidden.svg",Point3D(600,600,100));
            c = c.Project(Point3D(600,600,100));
            c.Scale(2);
            c.writeHidden("projectHidden.svg");            
            c.write("project.svg");
      }        
      
      //c.write("cube.svg");
      //ofstream out("single_cube.obj");

      //~ if( fork() == 0)
            //~ system("eog cube.svg");
      //system("eog projectHidden.svg");
            
      return 0;
}

