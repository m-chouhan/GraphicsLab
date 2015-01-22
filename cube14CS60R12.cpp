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

#include "graphics.cpp"

using namespace std;

int  main(int argc,char *argv[])
{ 
    Cube c("cube.obj");
    
	if(argc != 5)
    { 
        c.Rotate(20,30,30);
        c.Scale(1.5);
    }
    else
    {
            float S = atof(argv[1]);
            float degx = atoi(argv[2]);
            float degy = atoi(argv[3]);
            float degz = atoi(argv[4]);
            c.Rotate(degx,degy,degz);
            c.Scale(S);
    }        
	c.write("svgfile.svg");	
	return 0;
}

