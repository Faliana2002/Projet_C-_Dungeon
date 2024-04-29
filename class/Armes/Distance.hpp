// Projet C++ Dungeon
// ROB4 | Polytech Sorbonne
// 29/04/2024

#include <iostream>
#include "Armes.hpp"

#ifndef ARMES_Distance_HPP
#define ARMES_Distance_HPP

// Classe dérivée pour les armes à distance
class Distance : public Armes {
    public:
        // Utiliser le constructeur de la classe de base
        Distance(int degats, int distance, int frequence) : Armes(degats, distance, frequence) {}

        // Implémentation concrète de la méthode d'attaque
        virtual void attaque() const override {
            // Implémentation spécifique de l'attaque à distance
        }
};

#endif // ARMES_Distance_HPP