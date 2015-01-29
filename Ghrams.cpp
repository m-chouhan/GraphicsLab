
#include <iostream>
#include <stdlib.h>
#include <vector>
#include <algorithm>

#include "graphics.cpp"

using namespace std;

void Process(vector<Point2D> &Hull,Point2D P)
{
        if(Hull.size() < 2) 
        {
            Hull.push_back(P); 
            return;
        }
        
        Point2D p1,p2;
        Vector2D v1,v2;
        do{
                p1 = Hull.back();
                Hull.pop_back();
                p2 = Hull.back(); //second last element
                v1 = p1 - p2;
                v2 = P - p1;
        
        }while( ( (v1.angleX()) < (v2.angleX()) ) );
        
        //~ if(Hull.size() > 1 ) 
        Hull.push_back(p1);
        Hull.push_back(P);

}


void Ghrahm(vector<Point2D> &array,vector<Point2D> &convexHull,ofstream &out)
{
      vector<Point2D> upperHull,lowerHull;
      upperHull.push_back(array.front());
      lowerHull.push_back(array.front());  
      Vector2D V = array.back() - array.front();
  
      for(std::vector<Point2D>::iterator it = (array.begin()+1);it != array.end();++it)
      {
            cout<<(*it).x<<"\t";
            Vector2D v = *it - array.front();
            //~ if( it == (array.end() - 1) )
            //~ {
                //~ Process(upperHull,*it);
                //~ Process(lowerHull,*it);
            //~ }   
            if( V.angleX() < v.angleX() ) 
            {
                if(upperHull.size() < 2) 
                {
                    upperHull.push_back(*it); continue;
                }
                Point2D p1,p2;
                Vector2D v1,v2;
                do{
                        p1 = upperHull.back();
                        upperHull.pop_back();
                        p2 = upperHull.back(); //second last element
                        v1 = p1 - p2;
                        v2 = *it - p1;
                
                }while( v1.angleX() < v2.angleX());
                
                upperHull.push_back(p1);
                upperHull.push_back(*it);
            }    
            else
            {
                     //lower hull
                    if(lowerHull.size() < 2) 
                    {
                        lowerHull.push_back(*it); continue;
                    }
                    Point2D p1,p2;
                    Vector2D v1,v2;
                    do{
                            p1 = lowerHull.back();
                            lowerHull.pop_back();
                            p2 = lowerHull.back(); //second last element
                            v1 = p1 - p2;
                            v2 = *it - p1;
                    
                    }while( v1.angleX() > v2.angleX());
                    
                    lowerHull.push_back(p1);
                    lowerHull.push_back(*it);                    
            }
      }
      
      std::reverse(lowerHull.begin(),lowerHull.end());
        
      for( std::vector<Point2D>::iterator it = lowerHull.begin();it != (lowerHull.end());++it)
            upperHull.push_back(*it);
            
      //writeLines(upperHull,out);
      //writeLines(lowerHull,out);      
      
      convexHull = upperHull;  
}

void JarvisMarch(vector<Point2D> Hulls[10])
{
        Point2D lowest(1000,1000),infi(-1000,-1000);
        vector<Point2D>::iterator P;
        vector<Point2D> FinalHull;
        
        int I=0;
    //~ Get the lowest point of all hulls
        for(int i = 0;i<3;++i)
        {
            for(vector<Point2D>::iterator it = Hulls[i].begin();
                    it != Hulls[i].end();++it)
            {
                if( lowest.x > (*it).x ) 
                {    
                    lowest = *it;
                    I = i;P = it;
                }
            }        
        }
        
        infi.x = lowest.x;
        Vector2D v = lowest - infi;
        Hulls[I].erase(P);
        //~ erase the lowest point and create vector from infinite y;
        float maxAngle = 0;
        //~ get maximum angle and remove the point 
        for(int j = 0;j<15;++j) // we are assuming 15 hull points
        {
            for(int i = 0;i<3;++i)
            {
                for(vector<Point2D>::iterator it = Hulls[i].begin();
                        it != Hulls[i].end();++it)
                {
                    Vector2D v2 = (*it) - lowest;
                    if ( (v^v2) < maxAngle ) //calculate angle between vectors
                    {
                        maxAngle = (v^v2);
                        P = it;
                        I = i;
                    }
                }
                        
            }
            FinalHull.push_back(*P);
            v = *P - lowest;
            lowest = *P;
            Hulls[I].erase(P);
            maxAngle = 0;
        }
                
}

int main()
{
    srand(time(0));
    ofstream out("geometry.svg");
    out<<"<svg xmlns=\"http://www.w3.org/2000/svg\" version=\"1.1\" height=\"310\" width=\"500\">\n";

    vector<Point2D> array;
    vector<Point2D> lowerHull,upperHull;
    vector<Point2D> Arrays[10],ConvexHulls[10];

    for(int j = 0;j<3;++j)
    {
        for(int i = 0;i<5;++i)
                Arrays[j].push_back(Point2D(rand() % 300,rand() % 300));
        
        std::sort(Arrays[j].begin(),Arrays[j].end());
        writePoints(Arrays[j],out);
        Ghrahm(Arrays[j],ConvexHulls[j],out);
        writeLines(ConvexHulls[j],out);
    }
    //cout<<(Arrays[0][0]^Arrays[0][1]);
    
    //std::sort(array.begin(),array.end());
    //writePoints(array,out);
         
    //Ghrahm(array,convexHull,out);
    //writeLines(convexHull,out);
    
    out<<"</svg>\n";
    out.close();
    
    return 0;
}
