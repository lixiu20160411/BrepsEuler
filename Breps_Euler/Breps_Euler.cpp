// Breps_Euler.cpp : 定义控制台应用程序的入口点。
//Asin
//2015.11.23

#include "stdafx.h"
 
char *subString(char *dst,char *src, int ibegin,int iend)  
{
	char *p = src+ibegin;
	char *q = dst; 
	int n=iend-ibegin+1; 
	while(n--) *(q++) = *(p++);
	*(q++)='\0';
	return dst;
}

int line2PointArry(char* LineTxt,Point *p) {

	int iBegin = 0;
	int iEnd = 0;
	int pointCount = 0; 
	int istr=0; 
	char temp[BUFSIZ];
	double x=0,y=0,z=0; 
	while (LineTxt!=NULL && LineTxt[istr]>0)
	{ 
		while(LineTxt[istr]==' '||LineTxt[istr]=='#') istr++;
		if(LineTxt[istr]!='(') 
			break;
		else
			iEnd=iBegin=istr+1;

		while(LineTxt[iEnd]!=',') iEnd++; 		
		subString(temp,LineTxt,iBegin,iEnd-1);
		x=atol(temp);

		iBegin=iEnd=iEnd+1; 
		while(LineTxt[iEnd]!=',') iEnd++; 
		subString(temp,LineTxt,iBegin,iEnd-1);
		y=atol(temp);

		iBegin=iEnd=iEnd+1; 
		while(LineTxt[iEnd]!=')') iEnd++; 
		subString(temp,LineTxt,iBegin,iEnd-1);
		z=atol(temp); 

		p[pointCount]=Point(x,y,z);
		pointCount++;

		istr=iEnd+1;  
	}   

	return pointCount;
}

int main(int argc, const char * argv[]) {
	EULER_BREPS Breps;

	FILE *fp;
	//const char *filename_read="C:\\Users\\Asin\\Desktop\\CAD\\brep.txt";
	const char *filename_read="..\\brp\\breps.txt";
	const char *mode_read="r";
	fp=fopen(filename_read,mode_read);
	if(fp==NULL)
	{
		printf("Error\n");
		return 1;
	}

	int num=0; 
	Point p[100]; 
	char line[BUFSIZ];  
	fgets(line,BUFSIZ,fp);//int j=strlen(fgets(line,BUFSIZ,fp));
	num=line2PointArry(line,p);
	Breps.addSolid(p,num);

	  
	while (fgets(line,BUFSIZ,fp) && line[0]!='#')
	{
		num=line2PointArry(line,p);
		Breps.addInLoop(p,num);
	}

	num=line2PointArry(line,p); 
	Breps.sweeping(p[0],(int)p[1][0]);
	fclose(fp);
	

	//const char *filename_write="C:\\Users\\Asin\\Desktop\\CAD\\breps.brp";
	const char *filename_write="..\\brp\\breps.brp";
	const char *mode_write="w";
	fp=fopen(filename_write,mode_write); 
	if(fp==NULL)
	{
		printf("Error\n");
		return 1;
	}
	 
	if (Breps.writeToFile(fp))
		printf("Write Success\n");
	else
	{
		printf("Failed to Write\n");
		return 1;
	}
	fclose(fp);

	return 0;
}