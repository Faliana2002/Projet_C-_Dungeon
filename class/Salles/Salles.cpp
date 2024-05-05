#include "Salles.hpp"

Salles::Salles(const Point& c, float w, float h){
	center=c;
	sect.push_back(Rectangle(c,w,h);
	n=n+1;
}
bool addobst(int width, int height, Point pos){
	 Rectangle k;
	 bool ans=false;
	 for k in sect{
	 	if k.inrectangle(pos)
	 		{ans=true;
	 		obst.push_back(Rectangle(pos,width,height));
	 		}
	 return (ans);
	 } 
}
bool addsect(int width, int height, Point pos){
	Rectangle k;
	for k in sect{
		
	}
}
void setcenter(Point p);
void setdoor(Point p);
Obstacles & getobst(){return obst};
Rectangle & getsect(){return sect};
Point getcenter(){return center};
Point & getdoor(){return door};
int getnbsect(){return n};
