// Projet C++ Dungeon
// ROB4 | Polytech Sorbonne
// 29/04/2024

#include <iostream>
#include "Armes.hpp"
#include <cmath> // Pour utiliser sin et cos pour les directions
class Joueur;
class Ennemi;

#ifndef PROJECTILE_HPP
#define PROJECTILE_HPP

extern std::string arrowFile = "arrow";
extern std::vector<std::tuple<std::string, float, float, float, float, float, float>> listeArmesDistance;

// Prototype supposé pour la direction
struct Vec2 {
    float x, y;

    Vec2(float x = 0.0, float y = 0.0) : x(x), y(y) {}

    void set(float newX, float newY) {
        x = newX;
        y = newY;
    }

    void normalize() {
        float len = std::sqrt(x * x + y * y);
        if (len != 0) {
            x /= len;
            y /= len;
        }
    }

    Vec2 operator*(float scalar) const {
        return Vec2(x * scalar, y * scalar);
    }
};

// Classe generant les projectiles
class Projectile : public Armes {
    public:
        Vec2 velocity; // Nouveau membre pour stocker la vitesse et la direction
        sf::Texture texture; // Texture du projectile
        sf::Sprite sprite; // Sprite associé à la texture
        float rate_; // Taux de déplacement
        float degats_; // Dommages causés par le projectile
        float distance_attaque_; // Portée de l'attaque
        std::string textureFile; // Chemin vers le fichier de texture
        // Utiliser le constructeur de la classe de base
        Projectile(int indice, Vec2 direction);

};


#endif // PROJECTILE_HPP