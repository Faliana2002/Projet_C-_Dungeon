// Projet C++ Dungeon
// ROB4 | Polytech Sorbonne
// 29/04/2024

#include <iostream>
#include <cstdlib>
#include <ctime>
#include <vector>
#include <SFML/Graphics.hpp>

#include "../point.hpp"

#ifndef ARMES_HPP
#define ARMES_HPP

extern std::vector<std::tuple<std::string, float, float, float, float, float, float>> listeArmesCAC;
extern std::string reference;
extern std::string fin_str;
extern std::string weapon_str;

// Classe abstraite de base pour les armes
class Armes {
    public:
        // Destructeur virtuel pour une bonne gestion de la mémoire avec l'héritage
        virtual ~Armes() {}

        // Méthode virtuelle pure pour attaquer qui sera implémentée par les classes dérivées
        virtual void attaque() const = 0;

    protected:
        float degats_;               // Dégâts causés par l'arme
        float distance_attaque_;     // Distance maximale, à laquelle l'arme peut atteindre l'ennemi
        float rate_;   // Fréquence à laquelle l'arme peut émettre des munitions
        int indice_;
        Point position;
        float scale_factor = 1.0;
    public:
        sf::Texture texture;
        sf::Sprite sprite;
        std::string textureFile;
};


#endif // ARMES_HPP