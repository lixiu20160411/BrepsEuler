
#include "stdafx.h" 

class EULER_BREPS
{
public:
	EULER_BREPS()
	{
		s=NULL;
		faceList.clear();
		loopList.clear();
		vertexList.clear();
	} 
	void addSolid(Point *p,int num);
	void addInLoop(Point *p,int num);
	void sweeping(Direction dir,int dis);
	bool writeToFile(FILE *fp);

private:
	Solid *s;
	std::vector<Vertex *> vertexList;
	std::vector<Loop *> loopList;
	std::vector<Face *> faceList;
	unsigned num_V,num_E,num_F,num_S,num_H,num_R;

	Solid *mvfs(Point p);
	HalfEdge *mev(Vertex *start_v,Point p,Loop *loop);
	Loop *mef(Vertex *start_v,Vertex *end_v,Loop *loop);
	Loop *kemr(Vertex *start_v,Vertex *end_v,HalfEdge *half_R);
	void kfmrh(Face *face,Face *face_to_remove);
	void sweeping(Face *face,Direction direction,int distanse); 
}; 

