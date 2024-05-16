// Projet C++ Dungeon
// ROB4 | Polytech Sorbonne
// 29/04/2024

#ifndef PROJECTILE_HPP
#define PROJECTILE_HPP

#include <iostream>
#include <cmath> // Pour utiliser sin et cos pour les directions
#include "../Personnages/Personnages.hpp"
#include "../Personnages/Joueurs.hpp"
#include "../Personnages/Ennemi.hpp"
// class Joueur; // Déclaration anticipée
// class Personnages;
#include "Armes.hpp" // Inclure seulement si nécessaire

extern std::string arrowFile;
extern std::vector<std::tuple<std::string, float, float, float, float, float, float>> listeArmesDistance;

// Structure Vec2 avec une méthode normalize correctement définie
struct Vec2 {
    float x, y;

    Vec2(float x = 0.0, float y = 0.0) : x(x), y(y) {}

    void set(float newX, float newY) {
        x = newX;
        y = newY;
    }

    float length() const {
        return std::sqrt(x * x + y * y);
    }

    Vec2 normalize() const {
        float len = length();
        if (len == 0) return Vec2(0, 0);
        return Vec2(x / len, y / len);
    }

    Vec2 operator*(float scalar) const {
        return Vec2(x * scalar, y * scalar);
    }

    // Soustraction de deux vecteurs
    Vec2 operator-(const Vec2& other) const {
        return Vec2(x - other.x, y - other.y);
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


        // Constructeur par défaut
        Projectile(){};
        void attaque(std::vector<Ennemi*>& lEnnemis, std::vector<Joueur*>& lJoueur, const Armes& arme, Projectile& munition) const {};

        Projectile(int indice, Vec2 direction) {
            // std::string arrowFile = "arrow";
            indice_ = indice;

            int k = 100;

            // Extraction des valeurs du tuple pour la configuration initiale
            float rate_min = std::get<1>(listeArmesDistance[indice]) * k;
            float rate_max = std::get<2>(listeArmesDistance[indice]) * k;
            rate_ = static_cast<float>((rand() % static_cast<int>(rate_max - rate_min)) + rate_min) / k;

            float degats_min = std::get<3>(listeArmesDistance[indice]) * k;
            float degats_max = std::get<4>(listeArmesDistance[indice]) * k;
            degats_ = static_cast<float>((rand() % static_cast<int>(degats_max - degats_min)) + degats_min) / k;

            float range_min = std::get<5>(listeArmesDistance[indice]) * k;
            float range_max = std::get<6>(listeArmesDistance[indice]) * k;
            distance_attaque_ = static_cast<float>((rand() % static_cast<int>(range_max - range_min)) + range_min) / k;

            textureFile = reference + weapon_str + arrowFile + fin_str;
            texture.loadFromFile(textureFile);
            sprite.setTexture(texture);
            sprite.setPosition(position.getX(), position.getY());
            position.setX(640);
            position.setY(360);

            // Direction du projectile
            direction.normalize();
            velocity = direction * rate_;

            // Mise à l'échelle du sprite
            float scale_factor = 0.5; // Facteur d'échelle ajustable
            sprite.scale(scale_factor, scale_factor);
        }

        // Fonction qui genere les points pour la direction
        Point calculPoint_Ennemi(Armes& arme, Ennemi& ennemi) {
            Point point_direct = ennemi.getPosition() - arme.position;
            return point_direct;
        }

        Point calculPoint_Joueur(Armes& arme, Joueur& joueur){
            Point point_direct = joueur.getPosition() - arme.position;
            return point_direct;
        }

        // Fonction qui génère la direction du projectile à partir d'un point
        Vec2 calculDirection(const Point& point) {
            // Création d'un Vec2 à partir du Point
            Vec2 vector(point.getX(), point.getY());
            // Normalisation de ce vecteur pour obtenir la direction
            return vector.normalize();
        }

};


#endif // PROJECTILE_HPP