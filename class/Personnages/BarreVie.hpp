#ifndef BARREVIE
#define BARREVIE

#include <SFML/Graphics.hpp>

#include "../point.hpp"
//#include "Joueurs.hpp"

class BarreVie {
    public:
        Point position_red;
        Point position_white;
        int width_ = 64, height_ = 8;
        int width_red = width_, width_white = 0;

        sf::RectangleShape rectangle_red;
        sf::RectangleShape rectangle_white;

        void draw_life();
};

#endif