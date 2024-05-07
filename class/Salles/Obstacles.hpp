#ifndef OBSTACLES_HPP
#define OBSTACLES_HPP

#include "../point.hpp"
#include "../rectangle.hpp"
class Obstacles: public Rectangle {
public:
	Obstacles(const Point& c, float w, float h) : Rectangle(c,w,h) {} ;
	bool inobstacles(Point p);
};
#endif
