#include "../point.hpp"
#include "../rectangle.hpp"
class Obstacles: public Rectangles {
public:
	Obstacles(const Point& center, float w, float h) : center(center), width(w), height(h) {} ;
	bool inobstacles(Point p);
