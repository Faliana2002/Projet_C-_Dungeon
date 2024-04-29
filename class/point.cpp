#include "point.hpp"

Point & Point::operator=( const Point& p){
	x=p.getX();
	y=p.getY();
	return(* this);
}

Point Point::operator+( const Point& p){
	Point p2;
	x=getX()+p.getX();
	y=getY()+p.getY();
	p2.setX(x);
	p2.setY(y);
	return(p2);
}

Point Point::operator-( const Point& p){
	Point p2;
	x=getX()-p.getX();
	y=getY()-p.getY();
	p2.setX(x);
	p2.setY(y);
	return(p2);
}

Point Point::operator+=( const Point& p){
	Point p2;
	x=getX()+p.getX();
	y=getY()+p.getY();
	this->setX(x);
	this->setY(y);
	return(p2);
}

Point Point::operator-=( const Point& p){
	Point p2;
	x=getX()-p.getX();
	y=getY()-p.getY();
	this->setX(x);
	this->setY(y);
	return(p2);
}
