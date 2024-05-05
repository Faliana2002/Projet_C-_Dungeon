// Projet C++ Dungeon
// ROB4 | Polytech Sorbonne
// 29/04/2024

#include <iostream>
#include "Armes.hpp"

#ifndef ARMES_Distance_HPP
#define ARMES_Distance_HPP

extern std::vector<std::tuple<std::string, float, float, float, float, float, float>> listeArmesDistance;

// Classe dérivée pour les armes à distance
class Distance : public Armes {
    public:
        // Utiliser le constructeur de la classe de base
        Distance(int indice);

        // Implémentation concrète de la méthode d'attaque
        virtual void attaque() const override {
            // Implémentation spécifique de l'attaque à distance
        }
};

#endif // ARMES_Distance_HPP