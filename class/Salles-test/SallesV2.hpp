#ifndef SALLES_TEST2
#define SALLES_TEST2

#include <iostream>
#include <cmath>
#include <iomanip>

#include "../point.hpp"
#include <vector>
#include <SFML/Graphics.hpp>
#include "../rectangle.hpp"

extern std::string reference;

class Salles {
    public:
        Salles(Point p, int w, int h, int porte1, int porte2);

        void init_texture() {
            texture.loadFromFile(reference + "salle.png");
            sprite.setTexture(texture);
            sprite.setScale(1,1);
            sprite.setPosition(0,0);
        }

        int n = 14, m = 26;
        
        std::map<Point, int> pointMap;          // Map pour stocker les points avec leurs occurrences (l'entier associé)
        std::map<Point, int> pointMapInverted;  // Map inversée pour stocker les points avec leurs occurrences

        std::vector<Point> contourList;
        //std::vector<Rectangle> obstacleList;
        std::vector<sf::RectangleShape> lineList;
        //std::vector<sf::RectangleShape> lineObstacle;
        std::vector<Point> spawnable = {Point(640,320)};
        int thicknessLine = 2;

        std::vector<Point> positionPortes = {Point(0, 464), Point(0, 280), Point(394, 0), Point(896, 0), Point(1232, 280), Point(1232, 464), Point(896, 672), Point(394, 672)};
        void contour(); // Calculer les contours

        std::vector<std::vector<std::vector<Point>>> voisins;
        int** listeAvailable = new int*[n];
        bool isAtteignable(int** ll, Point p, Point f);
        void buildVoisins();
        void buildListeAvailable();
        void printArray(int** ll);
        void printPoints();
        void printContour();
        sf::Texture texture;
        sf::Sprite sprite;

        sf::Color color = sf::Color::White;
        
        void getLine();
        bool isIn(Point p);
};

#endif
