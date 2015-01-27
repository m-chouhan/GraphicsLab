
#include <iostream>
#include <stdlib.h>
#include <vector>
#include <algorithm>

#include "graphics.cpp"

using namespace std;

int main()
{
    srand(time(0));
    ofstream out("geometry.svg");
    out<<"<svg xmlns=\"http://www.w3.org/2000/svg\" version=\"1.1\" height=\"310\" width=\"500\">\n";

    vector<Point2D> array;
    vector<Point2D> lowerHull,upperHull,convexHull;
    
    for(int i = 0;i<20;++i)
    {
            array.push_back(Point2D(rand() % 100,rand() % 100));
    }
    
    //cout<<(array[0] < array[1]);
    std::sort(array.begin(),array.end());
    writePoints(array,out);
    convexHull.push_back(array.front());
    upperHull = lowerHull = convexHull;  
      
    convexHull.push_back(array.back());
    
    Vector2D V = (*array.end() - *array.begin());
    
    for(std::vector<Point2D>::iterator it = (array.begin()+1);it != array.end();++it)
    {
            cout<<(*it).x<<"\t";
            Vector2D v = *it - *array.begin();    
            if( V.angleX() < v.angleX() ) 
            {
                    Point2D p1,p2;
                    Vector2D v1,v2;
                    //~ upper hull
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
                    //~  lower hull
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
    
    //~ merge upper and lower hulls
    std::vector<Point2D> tmp;
    tmp.reserve(upperHull.size() + lowerHull.size()); // commenters are probably right about this
    std::merge(upperHull.begin(), upperHull.end(), lowerHull.begin(), lowerHull.end(), std::back_inserter(tmp));
    //~ src.swap(tmp);
    
    out<<"</svg>\n";
    out.close();
    
    return 0;
}
