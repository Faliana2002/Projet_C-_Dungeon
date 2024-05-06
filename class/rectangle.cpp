#include "rectangle.hpp"

bool Rectangle::inrectangle(Point P){
	if (P.getX()<center.getX()+width/2 && P.getX()>center.getX()-width/2 && P.getY()<center.getY()+height/2 && P.getY()>center.getY()-height/2)
		{return true;}
	return false;
}
bool Rectangle::nearrectangle(Point P){
	if ((P.getX()==center.getX()-width/2 -1.0 && (P.getY()<center.getY()+height/2 -64.0 || P.getY()>center.getY()-height/2 +64.0)) || (P.getX()==center.getX()+width/2 +1.0 && (P.getY()<center.getY()+height/2 -64.0 || P.getY()>center.getY()-height/2 +64.0)) || (P.getY()==center.getY()-height/2 -1.0 && (P.getX()<center.getY()+height/2 -64.0 || P.getY()>center.getY()-height/2 +64.0)) || (P.getY()==center.getY()+height/2 +1.0 && (P.getX()<center.getY()+height/2 -64.0 || P.getY()>center.getY()-height/2 +64.0)))
		{return true;}
	return false;
}
