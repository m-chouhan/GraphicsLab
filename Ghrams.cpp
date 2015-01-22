
#include <iostream>
#include <stdlib.h>
#include <vector>

#include "graphics.cpp"

using namespace std;

int main()
{
    srand(time(0));
    
    vector<Point2D> array;
    
    for(int i = 0;i<20;++i)
    {
            array.push_back(Point2D(rand() % 100,rand() % 100));
            
    }
    
    return 0;
}
