
#include "Physics.hpp"
#include <vector>

      void GravityManager(ShapeList &list)
      {
            //reset acc
            for(int i = 0;i<list.size();++i) list[i]->acc = Point3D(0,0,0);
            //~ Acceleration for current time step
            for(int i = 0;i<list.size();++i)
            {
                  for(int j = i+1;j<list.size();++j)
                  {
                        Shape *s1 = list[i],*s2 = list[j];
                        Vector force = GVector(s1,s2);
                        s1->acc = s1->acc + force/s1->mass;
                        s2->acc = s2->acc + (force/s2->mass)*-1;
                  }
            }
            
            //~ Now we have acc and velocity for current time step 
            //~ So apply Approximation
            for(int i = 0;i<list.size();++i)   
            {
                  Vector delta  = EulersApproximation(list[i]->velocity,list[i]->acc);
                  list[i]->Translate(delta);
                  //~ RungeKutta();
            }
      }
