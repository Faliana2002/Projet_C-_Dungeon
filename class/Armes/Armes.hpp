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

// 3 variables globales définies dans un fichier source externe
extern std::string reference;
extern std::string fin_str;
extern std::string weapon_str;

// Classe abstraite de base pour les armes
class Armes {
    public:
        // Destructeur virtuel pour une bonne gestion de la mémoire avec l'héritage
        virtual ~Armes() {}

        // Méthode virtuelle pure pour attaquer qui sera implémentée par les classes dérivées
        // Méthode pour obtenir les dégâts de l'arme
        float getDegats() const {return degats_;}
        virtual void attaque() const = 0;
        virtual void infligerDegats() const = 0;
        virtual void ramasserArme() const = 0;
        // Méthode pour ajouter une arme à l'inventaire
        virtual void ajouterArmeInventaire(const Armes& arme){inventaire.push_back(arme);}

    protected:
        float degats_;               // Dégâts causés par l'arme
        float distance_attaque_;     // Distance maximale, à laquelle l'arme peut atteindre l'ennemi
        float rate_;   // Fréquence à laquelle l'arme peut émettre des munitions
        int indice_;
        float scale_factor = 2.0;
    public:
        sf::Texture texture;
        sf::Sprite sprite;
        std::string textureFile;
        std::vector<Armes> inventaire; // Inventaire des armes
        Point position;
        bool portee = false;
};


#endif // ARMES_HPP