#ifndef SALLES_TEST
#define SALLES_TEST

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
        Salles() {
            getLine();
            voisins.resize(n, std::vector<std::vector<Point>>(m));
            buildListeAvailable();
            buildVoisins();
            std::cout << "Voisins terminés" << std::endl;

            init_texture();
            std::cout << "Init texture terminé" << std::endl;
        };

        void init_texture() {
            texture.loadFromFile(reference + "salle.png");
            sprite.setTexture(texture);
            sprite.setScale(1,1);
            sprite.setPosition(0,0);
        }

        int n = 14, m = 26;

        std::vector<Point> contourList = {Point(0,96),Point(96,96),Point(96,48),Point(288,48),Point(288,144),Point(432,144),Point(432,192),Point(672,192),Point(672,48),Point(720,48),Point(720,0),Point(864,0),Point(864,96),Point(912,96),Point(912,144),Point(960,144),Point(960,192),Point(1056,192),Point(1056,96),Point(1152,96),Point(1152,480),Point(1008,480),Point(1008,576),Point(624,576),Point(624,624),Point(288,624),Point(288,480),Point(192,480),Point(192,384),Point(48,384),Point(48,240),Point(0,240),Point(0,96)};
        std::vector<Rectangle> obstacleList = {Rectangle(Point(624+240/2, 336+144/2), 240, 144), Rectangle(Point(288+48, 288+48), 96, 96)};
        std::vector<sf::RectangleShape> lineList;
        std::vector<sf::RectangleShape> lineObstacle;
        std::vector<Point> spawnable = {Point(208,64), Point(226,368), Point(334,476), Point(534,382), Point(592,222), Point(734,102), Point(916,232), Point(1016,338), Point(892,458)};
        int thicknessLine = 2;

        std::vector<std::vector<std::vector<Point>>> voisins;
        int** listeAvailable = new int*[n];
        bool isAtteignable(int** ll, Point p, Point f);
        void buildVoisins();
        void buildListeAvailable();
        void printArray(int** ll);
        sf::Texture texture;
        sf::Sprite sprite;

        sf::Color color = sf::Color::White;
        
        void getLine();
        bool isIn(Point p);
};

#endif
