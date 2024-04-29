#ifndef POINT_HPP
#define POINT_HPP

class Point {
public:
	Point(float x, float y): x(x), y(y) {} ;
	Point(): Point(0., 0.) {} ;
	const float& getX() const {return x; };
	const float& getY() const {return y; };
	const float& setX(float px) const { x=px; };
	const float& setY(float py) const { y=py; };
	Point & operator=( const Point& p);
	Point operator+( const Point& p);
	Point operator-( const Point& p);
	Point operator+=( const Point& p);
	Point operator-=( const Point& p);
private:
        float x;
        float y;

};

#endif // POINT_HPP

