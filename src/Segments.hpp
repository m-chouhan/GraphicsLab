#ifndef __SEGMENTS__
#define __SEGMENTS__

#include "Point3D.h"
#include "Dcel.hpp"

struct Line
{     
      Point2D UP;
      Point2D Down;
      Line(Point2D u,Point2D d)
      {
            UP = u;Down = d;
      }
      Line(Vertex v1,Vertex v2)
      {
            UP = v1.origin;Down = v2.origin;
      }
      //returns the point of intersection in P if true
      bool intersect(Line &L2,Point2D &P);
      Point2D get_line_intersection(float p0_x, float p0_y, float p1_x, float p1_y, 
            float p2_x, float p2_y, float p3_x, float p3_y);
};

#endif
