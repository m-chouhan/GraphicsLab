
#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <time.h>
#include <vector>
#include <algorithm>
#include "Avl.cpp"

using namespace std;

struct Line
{     
      Point2D UP;
      Point2D Down;
      Line(Point2D u,Point2D d)
      {
            UP = u;Down = d;
      }
      bool intersect(Line &L2,Point2D &P)
      {
            P = get_line_intersection(UP.x,UP.y,Down.x,Down.y,
                  L2.UP.x,L2.UP.y,L2.Down.x,L2.Down.y);
            if ( P.x == 0 && P.y == 0 )
                  return false;
            return true;
      }
      Point2D get_line_intersection(float p0_x, float p0_y, float p1_x, float p1_y, 
            float p2_x, float p2_y, float p3_x, float p3_y)
      {
            Point2D P;
            float s1_x, s1_y, s2_x, s2_y;
            s1_x = p1_x - p0_x;     s1_y = p1_y - p0_y;
            s2_x = p3_x - p2_x;     s2_y = p3_y - p2_y;

            float s, t;
            s = (-s1_y * (p0_x - p2_x) + s1_x * (p0_y - p2_y)) / (-s2_x * s1_y + s1_x * s2_y);
            t = ( s2_x * (p0_y - p2_y) - s2_y * (p0_x - p2_x)) / (-s2_x * s1_y + s1_x * s2_y);

            if (s >= 0 && s <= 1 && t >= 0 && t <= 1)
            {
              // Collision detected
                  P.x = p0_x + (t * s1_x);
                  P.y = p0_y + (t * s1_y);
            }

            return P; // No collision
      }
};

void Grahm(vector<Point2D> &array,vector<Point2D> &convexHull,ofstream &out)
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

//Using BruteForce
void  ProcessSegmentsFromQ(vector<Line> &lines,BinaryTree &eventQ,vector<Point2D> &points)
{
      for(int i = 0; i<lines.size();++i)
      {
            Point2D P;
            for(int j = i+1;j<lines.size();++j)
            {      
                  if( lines[i].intersect(lines[j],P) )
                        points.push_back(P);
            }
      }
}

int main()
{
      srand(time(NULL));
	BinaryTree Bt;
      ofstream out("line.svg");
      out<<"<svg xmlns=\"http://www.w3.org/2000/svg\" version=\"1.1\" height=\"310\" width=\"500\">\n";

      std::vector<Point2D> points,Hull;
      std::vector<Line> Segment;
      
	cout<<"Inserting.."<<endl;
	for(int i = 0;i<20;++i)
	{
		Point2D UP(rand()%500+1,rand()%500+1);
            Point2D Down(rand()%500+1,rand()%500+1);
            Line L(UP,Down);
            writeLine(UP,Down,out,GREEN);
            Segment.push_back(L); 
		//cout<<var<<"->";
		Bt.insert(UP,UPPER);
            Bt.insert(UP,LOWER);      
	}
      
      ProcessSegmentsFromQ(Segment,Bt,points);
      
      std::sort(points.begin(),points.end());
      
      writePoints(points,out);
      
      Grahm(points,Hull,out);            
      
      writeLines(Hull,out,BLUE);
	//@cout<<endl<<"Contents of Binary tree inorder traversal .."<<endl;
	//@Bt.print();
      //@Bt.BalanceTree(Bt.root);
      //@cout<<"After Balancing"<<endl;
	//@Bt.print();
      //@Bt.printInorder(Bt.root);
	cout<<endl;
      
      out<<"</svg>\n";
      out.close();

      return 0;
}
