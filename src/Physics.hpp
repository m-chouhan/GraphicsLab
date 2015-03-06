#ifndef __PHYSICS__
#define __PHYSICS__

#inlcude "Point3D.h"
#include "Shape.h"
#include "Smahser.hpp"

class Physics{
      
      double G;

      Point3D GVector(Shape *s1,Shape *s2)
      {
            Vector r = s2->origin - s1->origin;
            float force = G*s1->mass*s2->mass/(r.mod()*r.mod());
            return (r*force)/r.mod();
      }
      
      Vector EulersApproximation(Vector &velo,Vector acc)
      {
            float Tstep = 0.1;
            Vector delta = velo*Tstep + acc*Tstep*(Tstep/2);
            velo = velo + acc*Tstep;
            return delta;
      }
      
      void CollisionManager(ShapeList &list)
      {
            for(int i = 0;i<list.size();++i)
            {
                  for(int j = i+1;j<list.size();++j)
                  {
                        Shape *s1 = list[i],s2 = list[j];
                        if( s1->Collision(s2))
                        {
                              //~ reset pos and velocites ( note that acc will be same )
                        }
                  }
            }
      }
      void Update(ShapeList &list)
      {
            GravityManager(list);
            CollisionManager(list);
      }
};

#endif
