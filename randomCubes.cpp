
#include <iostream>
#include <fstream>
#include <stdlib.h>

#include "graphics.cpp"

using namespace std;

struct Specs{
        int length;
        int m;
        float sigX;
        float sigY;
    };
    
Specs getSpecs(ifstream &in)
{
      Specs s;
      in>>s.length>>s.m>>s.sigX>>s.sigY;
      return s;  
}    


int main()
{
    srand(time(NULL));
  
    vector<Cube> World;
    vector<Cube> Cubes;
    
    ofstream out("randomCubes.svg");
    out<<"<svg xmlns=\"http://www.w3.org/2000/svg\" version=\"1.1\" height=\"310\" width=\"500\">\n";
    //write(out);

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
            //~ Check for collision and push the cubes in world 
            for(vector<Cube>::iterator it = Cubes.begin();it != Cubes.end();++it)
            {
                Point3D P = getGaussianDistri(S.sigX,S.sigY,0);
                P.z = S.length/2;    
                (*it).Move(P);
                
                while( CheckCollision(World,*it ) ) 
                {
                    P = getGaussianDistri(S.sigX,S.sigY,0);
                    (*it).Move(P);
                }
                World.push_back(*it);
                (*it).write(out);
                out<<fflush;
                cout<<"writing:("<<P.x<<","<<P.y<<")"<<CheckCollision(World,*it)<<endl;
            }
            Cubes.empty();    
    }
    
    out<<"</svg>\n";
    out.close();
    in.close();            
    return 0;
}
