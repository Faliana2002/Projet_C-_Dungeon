#ifndef POINT_HPP
#define POINT_HPP

class Point {
public:
	Point(float x, float y): x(x), y(y) {} ;
	Point(): Point(0., 0.) {} ;
	const float& getX() const {return x; };
	const float& getY() const {return y; };
	void setX(float px) { x=px; };
	void setY(float py) { y=py; };
	Point & operator=( const Point& p);
	Point operator+( const Point& p);
	Point operator-( const Point& p);
	void operator+=( const Point& p);
	void operator-=( const Point& p);
	bool operator!=( const Point& p);
	bool operator==( const Point& p);
	bool operator<( const Point& p) const;
private:
        float x;
        float y;

};

#endif // POINT_HPP

