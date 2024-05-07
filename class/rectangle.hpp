#ifndef RECTANGLE_HPP
#define RECTANGLE_HPP
// Miranda Coninx
// ISIR - Sorbonne Universite / CNRS
// 07/04/2022

#include "point.hpp"


#include <cmath> 


class Rectangle{
public:
    Rectangle(const Point& center, float w, float h) : center(center), width(w), height(h) {} ;
    Rectangle(float x1, float y1, float x2, float y2) : center((x1+x2)/2,(y1+y2)/2), width(std::abs(x2-x1)), height(std::abs(y2-y1)) {} ;
    
    
    const float& getWidth() const {return width; } ;
    const float& getHeight() const {return height; } ;
    const Point& getCenter() const {return center; } ;
    const float& getX() const {return center.getX(); } ; // X of center
    const float& getY() const {return center.getY(); } ; // Y of center
    //la fonction inrectangle va m'aider a savoir si le joueur est dans la salle ou pas, en composant la salle de plein de rectangle
    bool inrectangle(Point P);
    bool nearrectangle(Point P);
    void setcenter (Point p){center=p;};
    void setwidth (float w){width=w;};
    void setheight (float h){height=h;};
    

private:
    Point center;
    float width;
    float height;
};

#endif
