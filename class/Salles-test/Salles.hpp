#ifndef SALLES_TEST
#define SALLES_TEST

#include <iostream>
#include <cmath>
#include <iomanip>

#include "../point.hpp"
#include <vector>
#include <SFML/Graphics.hpp>

class Salles {
    public:
        Salles() {
            getLine();
            voisins.resize(n, std::vector<std::vector<Point>>(m));
            buildListeAvailable();
            buildVoisins();
            std::cout << "Voisins terminés" << std::endl;
        };
        /*~Salles() {
            // Destruct pointers
            for (int i = 0; i < n; i++) {
                delete[] listeAvailable[i];
            }
            delete[] listeAvailable;
        }*/

        int n = 14, m = 26;

        std::vector<Point> contourList = {Point(200,200), Point(400,200), Point(400,100), Point(600,100), Point(600,300), Point(900,300), Point(900,200), Point(1100,200), Point(1100,400), Point(1200,400), Point(1200,600), Point(1100,600), Point(1100,700), Point(200,700), Point(200,200)};
        std::vector<sf::RectangleShape> lineList;
        int thicknessLine = 2;

        std::vector<std::vector<std::vector<Point>>> voisins;
        int** listeAvailable = new int*[n];
        bool isAtteignable(int** ll, Point p, Point f);
        void buildVoisins();
        void buildListeAvailable();
        void printArray(int** ll);

        sf::Color color = sf::Color::White;
        
        void getLine();
        bool isIn(Point p);
};

#endif