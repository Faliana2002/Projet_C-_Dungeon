#include "point.hpp"

Point & Point::operator=( const Point& p){
	x=p.getX();
	y=p.getY();
	return(* this);
}

Point Point::operator+( const Point& p){
	Point p2;
	p2.x=getX()+p.getX();
	p2.y=getY()+p.getY();
	return(p2);
}

Point Point::operator-( const Point& p){
	Point p2;
	p2.x=getX()-p.getX();
	p2.y=getY()-p.getY();
	return(p2);
}

void Point::operator+=( const Point& p){
	x=getX()+p.getX();
	y=getY()+p.getY();
}

void Point::operator-=( const Point& p){
	x=getX()-p.getX();
	y=getY()-p.getY();
}
