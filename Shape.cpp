
/* Contains Abstract Shape class and corresponding Rect and cube classes
 * Author:Mahendra Chouhan(14CS60R12)
 */ 
 
#include <iostream>
#include <math.h>
#include <fstream>
#include <stdlib.h>
#include <vector>
#include "Point3D.cpp"

/*Parent Shape class for all shapes
 * any new shape must inherit this
 * Note: All movement must be relative to origin
 * if absolute values are needed than compute using getAbs()
 * */
class Shape
{
      Point3D origin;
      int degX,degY,degZ;
      public:
      //generate absolute values of shape (if required)  
      virtual Shape& getAbsolutes(Shape &) = 0;
      virtual void Rotate(int,int,int)= 0;
      virtual void Scale(float)= 0;
      virtual void Move(Point3D &)= 0;
      virtual bool Collision(Shape &)= 0;
};

class Rect
{
    Point3D origin;
  
    Point3D Points[4];
    //int orientation;
    public:
    friend class Cube;
    Rect(){}
    Rect(Point3D origin,Point3D p0,Point3D p1,Point3D p2,Point3D p3)
    {
        this->origin = origin;
            Points[0] = p0;Points[1] = p1;
        Points[2] = p2;Points[3] = p3;
    }
    //~ not implemented
    //~ Rect(Point3D origin,int orientation,int length,int breadth)
    //~ {
	//~ float deg = Rad(orientation);
	//~ this->origin = origin;
        //~ 
    //~ }
    void write(Point3D origin,std::ofstream &out)
    {
        for(int i = 0;i<3;++i)
                writeLine(Points[i]+origin,Points[i+1]+origin,out);
	   writeLine(Points[0]+ origin,Points[3]+origin,out); 
    }
    bool isAbove(Rect &R2)
    {
        return (R2.origin.z < origin.z);
    }
    //Not implemented
    void Rotate(int Degx,int Degy,int Degz);
    void Scale(int S);
    bool CheckCollision(Rect &R2)
    {   
        bool flag = false;
        for(int i = 0;i<4;++i)
        {
		flag = check_inside(R2.Points[i]) or 
			R2.check_inside(Points[i]) or flag;
        }
        return flag;
    }
    
    void Translate(Point3D &P)
    {
        for(int i = 0;i<4;++i) Points[i] = Points[i] + P;
    }
    
    bool check_inside(Point3D q)
    {
        Vector prev;
        for(int i = 0;i<4;++i)
        {
            Vector V = Points[(i+1)%4] - Points[i],
                   Q = q - Points[i];
            Vector R = V.X(Q);//cross product
            
            if( i == 0) prev = R;
            
            if( (prev.z > 0 && R.z > 0) or
                (prev.z < 0 && R.z < 0) or (!prev.z ^ !R.z)) 
                prev = R;
            else return false;
        }	
        return true;
    }
};

class Cube
{
	Point3D origin;
      Rect Faces[6];

      public:
      friend bool CheckCollision(std::vector<Cube> world,Cube c);
      //int length,breadth,depth;
	//length - along x axis
	//bredth - along y axis , depth - along z axis
	Cube(Point3D orig,int length,int breadth,int depth)
	{	
		Point3D temp;
            Point3D Points[8];
	
		origin = orig;
		temp.y -= breadth/2;temp.x -= length/2;temp.z += depth/2;
		
		Points[0] = temp;
		temp.x += length;Points[1] = temp;
		temp.y += breadth;Points[2] = temp;
		temp.x -= length;Points[3] = temp;
		temp.z -= depth;Points[4] = temp;
		temp.y -= breadth;Points[5] = temp;
		temp.x += length;Points[6] = temp;
		temp.y += breadth;Points[7] =temp;
		
		temp = Point3D(0,0,depth/2);
		Faces[0] = Rect(temp,
				Points[0],Points[1],Points[2],Points[3]);                
		temp = Point3D(0,0,-depth/2);
		Faces[1] = Rect(temp,
				Points[4],Points[5],Points[6],Points[7]);
		temp = Point3D(0,breadth/2,0);
		Faces[2] = Rect(temp,
				Points[2],Points[3],Points[4],Points[7]);
		temp = Point3D(0,-breadth/2,0);
		Faces[3] = Rect(temp,
				Points[0],Points[1],Points[6],Points[5]);
		temp = Point3D(length/2,0,0);
		Faces[4] = Rect(temp,
				Points[1],Points[2],Points[7],Points[6]);
		temp = Point3D(-length/2,0,0);
		Faces[5] = Rect(temp,
				Points[0],Points[3],Points[4],Points[5]);		
	}
	Cube(const char *objfile)
      {
            std::ifstream in(objfile);
            int x=0,y=0,z=0;
            int l=0,b=0,h=0;
            in>>l>>b>>h>>x>>y>>z;
            std::cout<<"\nCube{"<<l<<b<<h<<x<<y<<z<<"}\n";

            *this = Cube(Point3D(x,y,z),l,b,h);
            in.close();	
      }
	Cube(int l)
      {
            *this = Cube(Point3D(),l,l,l);
      }
      Cube()
      {
            *this = Cube(Point3D(),0,0,0);
      }
	void Scale(float S);
	void Rotate(int Degx,int Degy,int Degz);
	void write(const char *svgFile);
	//projects hidden faces
	void writeHidden(const char*svgFile);
      void getAbsolutes(Cube &c)
      {
            c.origin = origin;
            for(int i = 0;i<6;++i)
                  for(int j = 0;j<4;++j)
                  {
                        c.Faces[i].Points[j] = 
                        Faces[i].Points[j] + origin;
                        c.Faces[i].origin = Faces[i].origin+origin;
                  }      
      }
      //~ A relative movement
      void Translate(Point3D &P)
      {
            origin = origin + P;
        //@for(int i = 0;i<6;++i)
            //@Faces[i].Translate(P);
        //@for(int i = 0;i<8;++i)
            //@Points[i] = Points[i]+P;
      }
      //~ Absolute movement of cube to that point
      void Move(Point3D &P)
      {
        //@Point3D movement = P - origin;
        //@for(int i = 0;i<6;++i)
            //@Faces[i].Translate(movement);
        //@for(int i = 0;i<8;++i)
            //@Points[i] = Points[i]+movement;            
        origin = P;    
      }
      //@doesnot projects hidden space
      void write(std::ofstream &out);
};

void Cube::Scale(float S)
{
      float MatS[4][4] = { S, 0, 0,  0,
                         0, S, 0,  0,
                         0, 0, S,  0,
                         0, 0, 0,  1 };
	//@for(int i = 0;i<8;++i)
		//@Points[i].Multiply(MatS);
	for(int i = 0;i<6;++i)
      {
            for(int j = 0;j<4;++j)
            {
                Faces[i].Points[j].Multiply(MatS);
                Faces[i].origin.Multiply(MatS);
            }
      }    
}

void Cube::Rotate(int Degx,int Degy,int Degz)
{
    float   radx = Rad(Degx),
            rady = Rad(Degy),
            radz = Rad(Degz);
	
    float MatZ[4][4] = { cosf(radz), -sinf(radz), 0,  0,
                         sinf(radz), cosf(radz),  0,  0,
                         0       ,  0      ,    1,  0,
                         0       ,  0      ,    0,  1 };
                         
    float MatY[4][4] = { cosf(rady), 0,    sinf(rady),0,
                         0       , 1,       0    ,0,
                         -sinf(rady), 0,   cosf(rady),0,
                         0       ,  0      ,  0  ,1 };
                         
	float MatX[4][4] = { 1       ,  0      ,  0     ,0,
                         0,     cosf(radx), -sinf(radx) ,0,
                         0,     sinf(radx), cosf(radx)  ,0,
                         0,         0   ,       0   ,1 };

	//@for(int i = 0;i<8;++i)
		//@Points[i].Multiply(MatX)->Multiply(MatY)->Multiply(MatZ);
	for(int i = 0;i<6;++i)
      {
            for(int j = 0;j<4;++j)
            Faces[i].Points[j].Multiply(MatX)->
                               Multiply(MatY)->
                               Multiply(MatZ);
            Faces[i].origin.Multiply(MatX)->
                            Multiply(MatY)->
                            Multiply(MatZ);                   
      }
}

void Cube::writeHidden(const char *svgFile)
{
	std::ofstream out(svgFile);
    
	out<<"<svg xmlns=\"http://www.w3.org/2000/svg\" version=\"1.1\" height=\"310\" width=\"500\">\n";

      for(int i = 0;i<6;++i)
      {
        Faces[i].write(origin,out);
      }
      out<<"</svg>\n";
    
	out.close();
}

void Cube::write(std::ofstream &out)
{
    for(int i = 0;i<6;++i)
    {
        bool collision = false;
        for(int j = 0;j<6;++j)
        {
            if(Faces[i].CheckCollision(Faces[j]))
            {
                collision = true;
                if(Faces[i].isAbove(Faces[j]))
                    Faces[i].write(origin,out);
                break;
            }
        
        }
        if(!collision)
            Faces[i].write(origin,out);
    }
        
}

void Cube::write(const char *svgFile)
{
	std::ofstream out(svgFile);    
	out<<"<svg xmlns=\"http://www.w3.org/2000/svg\" version=\"1.1\" height=\"310\" width=\"500\">\n";
      write(out);
      out<<"</svg>\n";
    	out.close();
}

