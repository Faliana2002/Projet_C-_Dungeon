#ifndef SALLES_TEST
#define SALLES_TEST

#include <iostream>

#include "../point.hpp"
#include <vector>
#include <SFML/Graphics.hpp>

class Salles {
    public:
        Salles() {
            getLine();
        };

        std::vector<Point> contourList = {Point(200,200), Point(400,200), Point(400,100), Point(600,100), Point(600,300), Point(900,300), Point(900,200), Point(1100,200), Point(1100,400), Point(1200,400), Point(1200,600), Point(1100,600), Point(1100,700), Point(200,700), Point(200,200)};
        std::vector<sf::RectangleShape> lineList;
        int thicknessLine = 2;

        sf::Color color = sf::Color::White;
        void getLine() {
            for (size_t i = 0; i < contourList.size()-1; i++) {
                std::cout << "ici" << std::endl;
                sf::RectangleShape rectangle;
                rectangle.setPosition(sf::Vector2f(contourList[i].getX(), contourList[i].getY()));
                rectangle.setSize(sf::Vector2f(contourList[i+1].getX() - contourList[i].getX()+thicknessLine, contourList[i+1].getY() - contourList[i].getY()+thicknessLine));
                rectangle.setOutlineColor(color);
                lineList.push_back(rectangle);
            }
            std::cout << lineList.size() << std::endl;
        }

        bool isIn(Point p) {
            int l = contourList.size();
            int cpt1 = 0, cpt2 = 0;
            for (int i=0; i < l-1; i++) {
                if (contourList[i].getX() > p.getX() && contourList[i+1].getX() > p.getX() && ( (contourList[i].getY() < p.getY() && contourList[i+1].getY() >= p.getY()) || (contourList[i+1].getY() < p.getY() && contourList[i].getY() >= p.getY()) ) && contourList[i].getY() != contourList[i+1].getY() ) cpt1++;
            }
            
            for (int i=0; i < l-1; i++) {
                if ( ( (contourList[i].getX() < p.getX() && contourList[i+1].getX() >= p.getX()) || (contourList[i+1].getX() < p.getX() && contourList[i].getX() >= p.getX()) ) && contourList[i].getY() < p.getY() && contourList[i+1].getY() < p.getY() && contourList[i].getX() != contourList[i+1].getX()) cpt2++;
            }
            if (cpt1%2 != 0 && cpt2%2 != 0) return true;
            return false;
        }
};

#endif