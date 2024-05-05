#include "Salles.hpp"

Salles(const Point& c, float w, float h);
bool addobst(int width, int height, Point pos);
bool addsect(int width, int height, Point pos);
void setcenter(Point p);
void setdoor(Point p);
Obstacles & getobst(){return obst};
Rectangle & getsect(){return sect};
Point getcenter(){return center};
Point & getdoor(){return door};
int getnbsect(){return n};
