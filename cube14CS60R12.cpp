/*
 * Following program reads input from cube.obj file
 * and then scales and rotates the cube according to input
 * and generates .svg file
 * Author: Mahendra Chouhan (14CS60R12)
 * */
#include <iostream>
#include <math.h>
#include <fstream>
#include <stdlib.h>

double Rad(float Deg) 
{
	return (3.14*Deg/180);
}

using namespace std;

typedef struct Point3D Vector;

struct Point3D
{
	float x;
	float y;
	float z;
	Point3D() { x = y = z = 0; }
	Point3D(int X,int Y,int Z) { x = X;y = Y;z = Z;}
	Point3D * Multiply(float Matrix[][4]);
	Point3D  Cross(Point3D p1);
	Point3D add(Point3D p1,Point3D p2)
	{
		return Point3D(p1.x+p2.x,p1.y+p2.y,p1.z+p2.z);
	}
	Point3D add(Point3D p1)
	{
		return Point3D(p1.x+x,p1.y+y,p1.z+z);
	}
    	Point3D add(int X,int Y,int Z)
    	{
        	return Point3D(x+X,y+Y,z+Z);
    	}
    	Point3D& addse(int X,int Y,int Z)
    	{
       	 	x+=X;y+=Y;z+=Z;
        	return *this;
    	}
	Point3D sub(Point3D p)
	{
		return Point3D(x-p.x,y-p.y,z-p.z);
	}

};

Point3D Point3D::Cross(Point3D p)
{
	float X = y*p.z - p.y*z,
	      Y = -x*p.z + p.x*z,
	      Z = x*p.y - p.x*y;
	return Point3D(X,Y,Z);
}

Point3D * Point3D::Multiply(float  Matrix[][4])
{
	float temp[4] = {0};
	for(int i = 0;i<4;++i)
		temp[i] = x*Matrix[i][0] + y*Matrix[i][1] + z*Matrix[i][2];
	
    x = temp[0];y = temp[1]; z = temp[2];
    return this;
}

void writeLine(Point3D p1,Point3D p2,ofstream &out)
{	
	out<<"\n\t<line x1 = \""<<p1.x
	<<"\" y1 = \""<<p1.y 
	<<"\" x2 = \""<<p2.x
	<<"\" y2 = \""<<p2.y
	<<"\" style=\"stroke:rgb(255,0,0);stroke-width:2\" />\n";
}

struct Rect
{
    Point3D Points[4];
    Point3D origin;
    //int orientation;
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
    void write(Point3D origin,ofstream &out)
    {
        for(int i = 0;i<3;++i)
                writeLine(Points[i].add(origin),Points[i+1].add(origin),out);
	   writeLine(Points[0].add(origin),Points[3].add(origin),out); 
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
    bool check_inside(Point3D q)
    {
	Vector prev;
	for(int i = 0;i<4;++i)
	{
		Vector V = Points[(i+1)%4].sub(Points[i]),
		       Q = q.sub(Points[i]);
		Vector R = V.Cross(Q);
		
		if( i == 0) prev = R;
		
		if( (prev.z > 0 && R.z > 0) or
		    (prev.z < 0 && R.z < 0) or (!prev.z ^ !R.z)) 
			prev = R;
		else return false;
	}	
	return true;
    }
};

struct Cube
{
	Point3D Points[8];
    Rect Faces[6];
	Point3D origin;
	//length - along x axis
	//bredth - along y axis , depth - along z axis
	Cube(Point3D orig,int length,int breadth,int depth)
	{	
		Point3D temp;	
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
		temp = Point3D(0,breadth/4,0);
		Faces[2] = Rect(temp,
				Points[2],Points[3],Points[4],Points[7]);
		temp = Point3D(0,-breadth/4,0);
		Faces[3] = Rect(temp,
				Points[0],Points[1],Points[6],Points[5]);
		temp = Point3D(length/4,0,0);
		Faces[4] = Rect(temp,
				Points[1],Points[2],Points[7],Points[6]);
		temp = Point3D(-length/4,0,0);
		Faces[5] = Rect(temp,
				Points[0],Points[3],Points[4],Points[5]);		
	}
	Cube(const char *objfile)
    {
        ifstream in(objfile);
        int x=0,y=0,z=0;
        int l=0,b=0,h=0;
        in>>l>>b>>h>>x>>y>>z;
        cout<<"\nCube{"<<l<<b<<h<<x<<y<<z<<"}\n";
        
        *this = Cube(Point3D(x,y,z),l,b,h);
        in.close();	
    }
	void Scale(float S);
	void Rotate(int Degx,int Degy,int Degz);
	void write(const char *svgFile);
	//projects hidden faces
	void writeHidden(const char*svgFile);
};

void Cube::Scale(float S)
{
    float MatS[4][4] = { S, 0, 0,  0,
                         0, S, 0,  0,
                         0, 0, S,  0,
                         0, 0, 0,  1 };
	for(int i = 0;i<8;++i)
		Points[i].Multiply(MatS);
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

	for(int i = 0;i<8;++i)
		Points[i].Multiply(MatX)->Multiply(MatY)->Multiply(MatZ);
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
	ofstream out(svgFile);
    
	out<<"<svg xmlns=\"http://www.w3.org/2000/svg\" version=\"1.1\" height=\"310\" width=\"500\">\n";

	//~ for(int i = 0;i<7;++i)
	//~ {
		//~ writeLine(Points[i].add(origin),Points[i+1].add(origin),out);
	//~ }
    //~ writeLine(Points[0].add(origin),Points[3].add(origin),out);    
    //~ writeLine(Points[0].add(origin),Points[5].add(origin),out);    
    //~ writeLine(Points[7].add(origin),Points[2].add(origin),out);    
    //~ writeLine(Points[4].add(origin),Points[7].add(origin),out);    
    //~ writeLine(Points[1].add(origin),Points[6].add(origin),out);    

    for(int i = 0;i<5;++i)
    {
        Faces[i].write(origin,out);
    }
    out<<"</svg>\n";
    
	out.close();
}

void Cube::write(const char *svgFile)
{

	ofstream out(svgFile);
    
	out<<"<svg xmlns=\"http://www.w3.org/2000/svg\" version=\"1.1\" height=\"310\" width=\"500\">\n";

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
    out<<"</svg>\n";
    
	out.close();
}

int  main(int argc,char *argv[])
{ 
    Cube c("cube.obj");
    
	if(argc != 5)
        { 
            c.Rotate(20,30,30);
            c.Scale(1.5);
        }
    else
    {
            float S = atof(argv[1]);
            float degx = atoi(argv[2]);
            float degy = atoi(argv[3]);
            float degz = atoi(argv[4]);
            c.Rotate(degx,degy,degz);
            c.Scale(S);
    }        
	c.write("svgfile.svg");	
	return 0;
}

