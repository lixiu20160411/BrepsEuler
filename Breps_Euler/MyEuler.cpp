
#include "stdafx.h" 
#define Euler(v,e,f,s,h,r) ((v-e+f==2*(s-h)+r)?(true):(false))

Solid* EULER_BREPS::mvfs(Point p)
{
	Solid *newSolid=new Solid;
	Face *newFace=new Face(newSolid);
	Loop *newLoop=new Loop(newFace);
	Vertex *newVertex=new Vertex(p);
	newVertex->id=vertexList.size();
	vertexList.push_back(newVertex);

	newSolid->id=0;
	newSolid->sFace=newFace;
	 
	newLoop->nextL=newLoop;
	newLoop->id=loopList.size();
	loopList.push_back(newLoop);

	newFace->fLoop=newLoop;
	newFace->nextF=newFace;
	newFace->id=faceList.size();
	faceList.push_back(newFace);

	return newSolid;
}

HalfEdge* EULER_BREPS::mev(Vertex *sv, Point p, Loop *lp)
{
	Vertex *ev=new Vertex(p);
	ev->id=vertexList.size();
	vertexList.push_back(ev);

	HalfEdge *half_L=new HalfEdge(lp);
	HalfEdge *half_R=new HalfEdge(lp);
	Edge *newEdge = new Edge(half_L,half_R);

	half_R->startV=sv,half_R->fatherEdge=newEdge; 
	half_L->startV=ev,half_L->fatherEdge=newEdge; 

	half_R->next=half_L;
	if(lp->lEdge==NULL){
		lp->lEdge=half_R;
		half_L->next=half_R;
	}
	else{
		HalfEdge *he=lp->lEdge;
		while(he->next->startV!=sv) he=he->next;
		half_L->next=he->next;
		he->next=half_R;
	}

	return half_R;
}

Loop* EULER_BREPS::mef(Vertex *sv, Vertex *ev, Loop *lp)
{
	Solid *s=lp->lFace->fSolid;
	Face *newFace=new Face(s);
	Loop *newLoop=new Loop(newFace);
	HalfEdge *half_R=new HalfEdge(newLoop);
	HalfEdge *half_L=new HalfEdge(lp);
	Edge *newEdge=new Edge(half_L,half_R);

	half_R->fatherEdge=newEdge;
	half_L->fatherEdge=newEdge;
	half_R->startV=sv;
	half_L->startV=ev;

	HalfEdge *he_from_sv=lp->lEdge,*he_from_ev=lp->lEdge;
	while(he_from_sv->next->startV!=sv) he_from_sv=he_from_sv->next;
	while(he_from_ev->next->startV!=ev) he_from_ev=he_from_ev->next;

	half_R->next=he_from_ev->next;
	half_L->next=he_from_sv->next;

	he_from_sv->next=half_R;
	he_from_ev->next=half_L;

	lp->lEdge=half_L; 
	HalfEdge *he=half_L->next;
	while(he!=half_L)
		he->wLoop=lp,he=he->next;

	newLoop->lEdge=half_R; 
	he=half_R->next;
	while(he!=half_R) 
		he->wLoop=newLoop,he=he->next;
	 
	newFace->nextF=s->sFace->nextF;
	s->sFace->nextF=newFace;	 
	newFace->fLoop=newLoop;
	newFace->id=faceList.size();
	faceList.push_back(newFace);

	newLoop->nextL=newLoop;
	newLoop->id=loopList.size();
	loopList.push_back(newLoop);
	return newLoop;
}

Loop* EULER_BREPS::kemr(Vertex *sv, Vertex *ev, HalfEdge *half_R)
{
	Edge *e=half_R->fatherEdge;
	Loop *lp=half_R->wLoop;
	Face *face=lp->lFace;
	Loop *inLoop=new Loop(face);

	HalfEdge *he_from_sv=lp->lEdge;
	while(he_from_sv->next->startV!=sv)
		he_from_sv=he_from_sv->next;

	HalfEdge *he_from_ev=lp->lEdge;
	while(he_from_ev->next->startV!=ev)
		he_from_ev=he_from_ev->next;

	he_from_sv->next=e->half_L->next;
	he_from_ev->next=e->half_R->next;
	lp->lEdge=he_from_sv;

	if(he_from_ev==e->half_R)
		inLoop->lEdge=NULL;
	else
		inLoop->lEdge=he_from_ev;	 
	inLoop->nextL=face->fLoop->nextL;
	face->fLoop->nextL=inLoop;
	inLoop->id=loopList.size();
	loopList.push_back(inLoop);

	delete e;
	return inLoop;
}

void EULER_BREPS::kfmrh(Face *f1, Face *f2)
{
	f2->fLoop->nextL=f1->fLoop->nextL;
	f1->fLoop->nextL=f2->fLoop;
	f2->fSolid->sFace->nextF=f2->nextF;

	vector<Face *>::iterator it_f=faceList.begin();
	while (it_f!=faceList.end())
	{
		if(*it_f==f2)
		{
			faceList.erase(it_f);
			delete f2;
			break;
		}
		else
			it_f++;
	}
	for(int i=0;i<faceList.size();i++)
		faceList[i]->id=i;
}

void EULER_BREPS::sweeping(Face *f,Direction dir,int dis)
{
	Face *top_face;
	HalfEdge *first_he,*end_he,*first_new_R,*new_he_R;
	Vertex *start_v,*next_v,*up_v,*up_pre_v;
	Point up_point;
	 
	for (Loop *lp=f->fLoop;;)
	{
		first_he=lp->lEdge->GetBrother();
		end_he=first_he->next;
		while(end_he->next!=first_he)
			end_he=end_he->next;
 
		start_v=first_he->startV;
		up_point=start_v->point+dir*dis;
		first_new_R=mev(start_v,up_point,first_he->wLoop);
  
		HalfEdge *he=first_he->next;
		up_pre_v=first_new_R->GetBrother()->startV;
		while(he!=first_new_R)
		{
			next_v=he->startV;
			up_point=next_v->point+dir*dis;
			new_he_R=mev(next_v,up_point,he->wLoop);

			up_v=new_he_R->GetBrother()->startV;
			mef(up_v,up_pre_v,he->wLoop);
			up_pre_v=up_v;
			 
			he=he->next;
		}
		Loop *top_lp=mef(up_pre_v,first_new_R->GetBrother()->startV,end_he->wLoop);
		if(lp==f->fLoop)
			top_face=top_lp->lFace;
		else
			kfmrh(top_face,top_lp->lFace);
		if(lp->nextL==f->fLoop)
			break;

		lp=lp->nextL;
	}
}


void EULER_BREPS::addSolid(Point *p,int num)
{
	if (s!=NULL)
	{
		delete s;
		s=NULL;
	}
	s=mvfs(p[0]);
	Loop *loop1=s->sFace->fLoop; 
	for (int i=1;i<num;i++) 
		mev(vertexList[vertexList.size()-1], p[i], loop1);
	mef(vertexList[vertexList.size()-1], vertexList[0], loop1);
};

void EULER_BREPS::addInLoop(Point *p,int num)
{
	HalfEdge *he=mev(vertexList[0], p[0], s->sFace->fLoop); 
	int VertexStart=vertexList.size()-1;
	Loop *inloop=kemr(vertexList[0], vertexList[vertexList.size()-1], he);
	for (int i=1;i<num;i++) 
		mev(vertexList[vertexList.size()-1], p[i], inloop);  
	mef(vertexList[vertexList.size()-1], vertexList[VertexStart], inloop);
};

void EULER_BREPS::sweeping(Direction dir,int dis)
{
	sweeping(s->sFace,dir, dis);
}; 

bool EULER_BREPS::writeToFile(FILE *fp)
{
	if (fp==NULL) return false;

	fprintf(fp,"BRP\n");
	fprintf(fp,"%lu %lu %lu %lu\n", vertexList.size(), loopList.size(), faceList.size(), 1);
	for (int i=0; i<vertexList.size(); ++i) {
		fprintf(fp, "%d %d %d\n",(int) (vertexList[i]->point[0]), (int)(vertexList[i]->point[1]), (int)(vertexList[i]->point[2]));
	}

	for(int i=0; i<loopList.size(); ++i)
	{
		Loop *lp=loopList[i];
		vector<Vertex *> hev;
		HalfEdge *firsthe=lp->lEdge, *he;
		hev.push_back(firsthe->startV);
		for(he=firsthe->next;he!=firsthe;he=he->next)
		{
			hev.push_back(he->startV);
		}
		fprintf(fp, "%d", hev.size());
		for(int i=0;i<hev.size();i++)
		{
			fprintf(fp, " %d", hev[i]->id);
		}
		fprintf(fp, "\n");
	}

	for(int i=0; i<faceList.size(); ++i)
	{
		Face *f=faceList[i];
		vector<Loop *> lpv;
		Loop *firstlp=f->fLoop, *hf;
		lpv.push_back(firstlp);
		for (hf=firstlp->nextL; hf!=firstlp; hf=hf->nextL)
		{
			lpv.push_back(hf);
		}
		fprintf(fp, "%d %d", firstlp->id, lpv.size()-1);
		for(int i=1; i<lpv.size(); ++i)
		{
			fprintf(fp, " %d", lpv[i]->id);
		}
		fprintf(fp, " %d\n", f->fSolid->id);
	}
	return true;
}

