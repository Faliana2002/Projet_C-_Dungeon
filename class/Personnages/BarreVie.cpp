#include "BarreVie.hpp"

void BarreVie::draw_life() {
    // Créer un rectangle de couleur
    rectangle_red.setSize(sf::Vector2f(width_red, height_)); // Taille du rectangle
    rectangle_red.setFillColor(sf::Color::Red); // Couleur du rectangle
    rectangle_red.setPosition(position_red.getX(), position_red.getY());

    // Créer un rectangle de couleur
    rectangle_white.setSize(sf::Vector2f(width_white, height_)); // Taille du rectangle
    rectangle_white.setFillColor(sf::Color::White); // Couleur du rectangle
    rectangle_white.setPosition(position_white.getX(), position_white.getY());
}