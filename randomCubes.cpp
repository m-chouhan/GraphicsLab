/*
 * Compile and run this file to generate random cubes
 * input: from text file specs.txt
 *        format: #no of entries \n
 *                length1 m1 sigmaX1 sigmaY1\n
 *                .
 *                .
 * output:randomcubes.svg - contains 2d floor map of cubes
 *        randomcubes.obj - obj file created using the floor map
 * Author:Mahendra Chouhan(14CS60R12)
 * */

#include <iostream>
#include <fstream>
#include <stdlib.h>

#include "src/graphics.cpp"

using namespace std;

struct Specs{
        int length;
        int m;
        float sigX;
        float sigY;
    };
/*extracts cube specification from input stream*/     
Specs getSpecs(ifstream &in)
{
      Specs s;
      in>>s.length>>s.m>>s.sigX>>s.sigY;
      return s;  
}    


int main()
{
      srand(time(NULL));
      
      
      vector<Cube> World;//Cubes are added to world after placment :P
      vector<Cube> Cubes;
      vector<Cube> conflicts;//stores the current conflicts i.e collisions
      
      Point2D Mean(250,250);
      ofstream out("randomCubes.svg");
      out<<"<svg xmlns=\"http://www.w3.org/2000/svg\" version=\"1.1\" height=\"1000\" width=\"1000\">\n";

      ifstream in("specs.txt");
      int size = 0;
      in>>size;
    
    //~ for all different cube specs
      for(int i = 0;i<size;++i)
      {
            Specs S = getSpecs(in); //Get Specs
            for(int j = 0;j<S.m;++j)
                Cubes.push_back(Cube(S.length));
            //~ Generate Cubes
            //~ Check for collision and push the cubes in world :D
            for(vector<Cube>::iterator it = Cubes.begin();it != Cubes.end();++it)
            {
                  Point3D P = getGaussianDistri(S.sigX,S.sigY,Mean);
                  P.z = S.length/2;    
                  (*it).Move(P);
                  (*it).Rotate(0,0,rand()%180);
                  cout<<"writing:("<<P.x<<","<<P.y<<")"<<endl;
                  int counter = 0;
                  while( CheckCollision(World,*it,conflicts ) ) 
                  {
                        P = HandleCollision(World,*it,conflicts);  
                        P.z = S.length/2;
                        (*it).Rotate(0,0,rand()%180);
                        (*it).Move(P);
                        cout<<"!!Collision Detected!!["<<conflicts.size()<<"]\tRelocating Using Handler("<<P.x<<","
                        <<P.y<<")"<<endl;
                        if(counter++ > 5) break;
                  }
                  while( CheckCollision(World,*it,conflicts ) )
                  {
                        P = getGaussianDistri(S.sigX,S.sigY,Point2D(250,250));
                        P.z = S.length/2;
                        (*it).Rotate(0,0,rand()%180);
                        (*it).Move(P);
                        cout<<"!!Collision Detected!!["<<conflicts.size()<<"]\tRelocating Using Gaussian("<<P.x<<","
                        <<P.y<<")"<<endl;
                  }

                  World.push_back(*it);
                  (*it).write(out);
                  out<<fflush;
                  cout<<"written:("<<P.x<<","<<P.y<<")"<<endl;
            }
            Cubes.clear();    
      }
    
      out<<"</svg>\n";
      out.close();
      in.close();            
      
      int ID = 1;
      out.open("randomCubes.obj");
      for(vector<Cube>::iterator it = World.begin();it != World.end();++it)
      {
          (*it).writeObj(out,ID);
          ID += 8;
      }
      out.close();
      return 0;
}
