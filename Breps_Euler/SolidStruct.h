
#include "stdafx.h" 

struct Solid;
struct Face;
struct Loop;
struct Edge;
struct HalfEdge;
struct Vertex; 
typedef Vec3d Direction;

struct Vertex
{
	int id;
	Point point;
	Vertex *nextV,*preV;

	Vertex(Point p):id(0),nextV(NULL),preV(NULL)
	{
		point=p;
	}
};


struct Edge
{
	HalfEdge *half_L,*half_R;

	Edge(HalfEdge *half_l,HalfEdge *half_r)
	{
		half_L=half_l;
		half_R=half_r;
	}
};

struct HalfEdge
{
	Loop *wLoop;
	Vertex *startV;
	HalfEdge *next,*pre;
	Edge *fatherEdge;

	HalfEdge(Loop *lp):fatherEdge(NULL),next(NULL),pre(NULL),startV(NULL)
	{
		wLoop=lp;
	}

	HalfEdge* GetBrother()
	{
		if(this==fatherEdge->half_L)
			return fatherEdge->half_R;
		else
			return fatherEdge->half_L;
	}
};

struct Loop
{
	int id;
	Face *lFace;
	HalfEdge *lEdge;
	Loop *nextL,*preL;

	Loop(Face *f):id(0),nextL(NULL),preL(NULL), lEdge(NULL)
	{
		lFace=f;
	}
};

struct Face
{
	int id; 
	Solid *fSolid;
	Loop *fLoop; 
	Face *nextF,*preF;

	Face(Solid *s):id(0),nextF(NULL),preF(NULL),fLoop(NULL)
	{
		fSolid=s;
	}
};

struct Solid
{
	int id;
	Face *sFace;
	Solid *nextS,*preS;

	Solid():id(0),sFace(NULL),nextS(NULL),preS(NULL){}
};


// 
// struct Point
// {
// 	double X;
// 	double Y;
// 	double Z;
// 
// 	Point(double x,double y,double z)
// 	{
// 		X=x;
// 		Y=y;
// 		Z=z;
// 	}
// };
// 
// struct Vector3D
// {
// 	double point[3]; 
// 
// 	Vector3D(double *p)
// 	{
// 		point[0]=p[0];
// 		point[1]=p[1];
// 		point[2]=p[2]; 
// 	};
// 
// 	void plus(double a,double b,double c)
// 	{
// 		point[0]+=a;
// 		point[1]+=b;
// 		point[2]+=c; 
// 	}
// 	void multiply(double a,double b,double c)
// 	{
// 		point[0]*=a;
// 		point[1]*=b;
// 		point[2]*=c; 
// 	}
// 	void multiply(double a)
// 	{
// 		point[0]*=a;
// 		point[1]*=a;
// 		point[2]*=a; 
// 	}
// };
// typedef Vector3D Direction;