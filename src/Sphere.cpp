

#include "Sphere.hpp"
#include "Smasher.hpp"
#include "Cube.hpp"
#include "Simulator.hpp"

void Sphere::Draw()
{  
      //Simulator::drawSphere(origin,radius,col,light); 
      glPushMatrix();

      glColor3f(col.r,col.g,col.b);
      glTranslatef(origin.x,origin.y,origin.z);
      
      glBindTexture(GL_TEXTURE_2D, TextureID);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
      gluQuadricTexture(Quad,GLU_TRUE);

      if(light)
      {
            
            //~ glEnable (GL_BLEND);
            //~ glBlendFunc (GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
            //~ glColor4f(0.1,0,0,0);
            //Material properties
            GLfloat emissiveLight[] = { 8.8f, 4.4f, 0.f}; 
            glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, emissiveLight);
            //~ glutSolidSphere(radius,20,20);
            gluSphere(Quad,radius,20,20);
            
            emissiveLight[0] = emissiveLight[1] = emissiveLight[2]  = 0;
            glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, emissiveLight);
      }

      else gluSphere(Quad,radius,20,20);
      //~  glutSolidSphere(radius,20,20);
      glPopMatrix(); /**/
}

bool Sphere::Collision(Shape &S)
{
      if( Cube *c = dynamic_cast<Cube *>(&S))
            return Smasher::Smash(*this,*c);
      if(Sphere *s = dynamic_cast<Sphere*>(&S) )
            return CollisionSelf(*s);
      return false;
}

bool Sphere::CollisionSelf(Sphere &S)
{
      Point3D dist = S.origin - origin;
      //std::cout<<"Collision Self:\tS:"<<S.origin<<"\tthis:"<<origin<<std::endl;
      return dist.mod() < (S.radius + radius);
}

void Sphere::Write(std::ofstream &out)
{
      
}
