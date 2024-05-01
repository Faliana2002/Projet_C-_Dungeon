#include "../point.hpp"
class Obstacles {
private:
	Point center;
	Rectangle & contour;
public:
    bool on_obstacle =0;
    void setcenter(Point c);
    void setcontour(Point & contour);
