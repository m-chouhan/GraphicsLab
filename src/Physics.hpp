#ifndef __PHYSICS__
#define __PHYSICS__

#include "Point3D.h"
#include "Shape.h"
#include "graphics.h"
//#include "Smasher.hpp"

class Physics{
      
      double G;
      public:
      Physics(double g):G(g)  {  }
      
      Point3D GVector(Shape *s1,Shape *s2)
      {
            Vector r = s2->origin - s1->origin;
            float force = G*s1->mass*s2->mass/(r.mod()*r.mod());
            return (r*force)/r.mod();
      }
      
      void Separate(Shape *s1,Shape *s2);
      
      Vector EulersApproximation(Vector &velo,Vector acc,float Tstep)
      {
            Vector delta = velo*Tstep + acc*Tstep*(Tstep/2);
            velo = velo + acc*Tstep;
            return delta;
      }
      
      void GravityManager(ShapeList2 &list);
      void CollisionManager(ShapeList2 &list);
      
      void Update(ShapeList2 &list)
      {
            GravityManager(list);
            CollisionManager(list);
            for(unsigned int i = 0;i<list.size();++i)
                  list[i].second.Push(list[i].first->getOrigin());            
      }
};

#endif
