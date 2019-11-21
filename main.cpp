#include<iostream>
#include<cmath>
using namespace std;
class Point{
public:
	int x,y;
	Point(int a=0,int b=0);
	Point(const Point& P);
};
class Triangle{
public:
	Point* a[3];
	Triangle(int x1=0,int y1=0,int x2=0, int y2=0, int x3=0, int y3=0);
	Triangle(const Triangle& T);
	~Triangle();
};
class Polyangle{
public:
	Point** a;
	int n=-1;
	void SetPoint(int k,int x=0,int y=0);
	Polyangle();
	Polyangle(const Polyangle& P);
	~Polyangle();
private:
	int m;
	void ChangeArr();
};
const int sizeX=91,sizeY=91;
const int n=sizeX*sizeY;
char a[n];
void clear();
void setPixel(int x,int y);
void print();
void drawLine(int x1,int y1,int x2,int y2);
void drawLine(Point P1,Point P2);
void drawTriangle(Triangle t);
void drawPolyangle(Polyangle p);

int main(){
	clear();
	/*Point p(0,0);
	cout<<p.x<<' '<<p.y<<endl;*/
	Polyangle p1;
	p1.SetPoint(0,sizeX/2,0);
	p1.SetPoint(1,sizeX-1,sizeY/3);
	p1.SetPoint(2,sizeX-1,2*sizeY/3);
	p1.SetPoint(3,sizeX/2,sizeY-1);
	p1.SetPoint(4,0,2*sizeY/3);
	p1.SetPoint(5,0,sizeY/3);
	drawPolyangle(p1);
	print();
	return 0;
}

Point::Point(int a,int b){
	x=a; y=b;
}
Point::Point(const Point& P){
	x=P.x; y=P.y;
}
Triangle::Triangle(int x1,int y1,int x2, int y2, int x3, int y3){
	a[0]=new Point(x1,y1);
	a[1]=new Point(x2,y2);
	a[2]=new Point(x3,y3);
}
Triangle::Triangle(const Triangle& T){
	for(int i=0;i<3;i++)		
		a[i]= new Point(*T.a[i]);
}
Triangle::~Triangle(){
	for(int i=0;i<3;i++)
		delete a[i];
}
void Polyangle::SetPoint(int k,int x,int y){
	if(k>n && k-n==1){
		if(n+1>=m) ChangeArr();
		n++;
		a[n]=new Point(x,y);
	}else if(k<=n){
		delete a[k];
		a[k]=new Point(x,y);
	} else cout<<"Error! Number of point "<<k<<" - number of picks"<<n<<">1"<<endl;
}
Polyangle::Polyangle(){
	m=16;
	a=new Point*[m];
}
Polyangle::Polyangle(const Polyangle& P){
	m=P.m;
	a=new Point*[m];
	for(int i=0;i<=P.n;i++)		
		a[i]= new Point(*P.a[i]);
	n=P.n;
}
Polyangle::~Polyangle(){
	for(int i=0;i<=n;i++)
		delete a[i];
	delete[] a;
}
void Polyangle::ChangeArr(){
	Point** b;
	b=new Point*[m*2];
	for(int i=0;i<m;i++)
		b[i]=a[i];
	delete[] a;
	a=b;
	m*=2;
	delete[] b;
}
void clear(){
	for(int i=0;i<n;i++)
		a[i]=' ';
}
void setPixel(int x,int y){
	if(x>=0 && x<sizeX && y>=0 && y<sizeY)
		a[x+y*sizeX]='.';
	else cout<<"Out of frame"<<endl;
}
void print(){
	for(int i=0;i<n;i++){
		cout<<a[i];
		if(!((i+1)%sizeX)) cout<<endl;
	}
}
void drawLine(int x1,int y1,int x2,int y2){
	float dirX=x2-x1;
	float dirY=y2-y1;
	int len=sqrt(dirX*dirX+dirY*dirY);
	dirX/=len;
	dirY/=len;
	for(int i=0;i<=len;i++)
		setPixel(x1+dirX*i,y1+dirY*i);
}
void drawLine(Point P1,Point P2){
	float dirX=P2.x-P1.x;
	float dirY=P2.y-P1.y;
	int len=sqrt(dirX*dirX+dirY*dirY);
	dirX/=len;
	dirY/=len;
	for(int i=0;i<=len;i++)
		setPixel(P1.x+dirX*i,P1.y+dirY*i);
}
void drawTriangle(Triangle t){
	for(int i=0;i<2;i++)
		drawLine(*t.a[i],*t.a[i+1]);
	drawLine(*t.a[2],*t.a[0]);
	//
	int x=0;
	int y=0;
	for(int i=0;i<3;i++){
		x+=t.a[i]->x;
		y+=t.a[i]->y;
	}
	x/=3;
	y/=3;
	if(a[x+y*sizeX]!='.'){
		Triangle t1(t.a[0]->x,t.a[0]->y,t.a[1]->x,t.a[1]->y,x,y);
		Triangle t2(t.a[1]->x,t.a[1]->y,t.a[2]->x,t.a[2]->y,x,y);
		Triangle t3(t.a[0]->x,t.a[0]->y,t.a[2]->x,t.a[2]->y,x,y);
		drawTriangle(t1);
		drawTriangle(t2);
		drawTriangle(t3);
	}
}
void drawPolyangle(Polyangle p){
	if(p.n>=2) for(int i=1;i<p.n;i++){
		Triangle t(p.a[0]->x,p.a[0]->y,p.a[i]->x,p.a[i]->y,p.a[i+1]->x,p.a[i+1]->y);
		drawTriangle(t);
	} else cout<<"Error! Not a Polyangle!"<<endl;
}