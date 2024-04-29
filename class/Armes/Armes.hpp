// Projet C++ Dungeon
// ROB4 | Polytech Sorbonne
// 29/04/2024

#include <iostream>

#ifndef ARMES_HPP
#define ARMES_HPP

// Classe abstraite de base pour les armes
class Armes {
    public:
        // Constructeur avec initialisation des attributs
        Armes(int degats, int distance, int frequence)
            : degats_(degats), distance_attaque_(distance), frequence_emission_(frequence) {}

        // Destructeur virtuel pour une bonne gestion de la mémoire avec l'héritage
        virtual ~Armes() {}

        // Méthode virtuelle pure pour attaquer qui sera implémentée par les classes dérivées
        virtual void attaque() const = 0;

    protected:
        int degats;               // Dégâts causés par l'arme
        int distance_attaque;     // Distance maximale, à laquelle l'arme peut atteindre l'ennemi
        int frequence_emission;   // Fréquence à laquelle l'arme peut émettre des munitions
};


#endif // ARMES_HPP