#include "rectangle.hpp"

bool Rectangle::inrectangle(Point P){
	if (P.getX()<center.getX()+width/2 && P.getX()>center.getX()-width/2 && P.getY()<center.getY()+height/2 && P.getY()>center.getY()-height/2)
		{return true;}
	return false;
}
