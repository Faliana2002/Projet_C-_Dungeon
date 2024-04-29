// Projet C++ Dungeon
// ROB4 | Polytech Sorbonne
// 29/04/2024

#include <iostream>
#include "Armes.hpp"

#ifndef ARMES_CorpsaCorps_HPP
#define ARMES_CorpsaCorps_HPP

// Classe dérivée pour les armes de corps à corps
class CorpsaCorps : public Armes {
    public:
        // Utiliser le constructeur de la classe de base
        CorpsaCorps(int degats, int distance, int frequence) : Armes(degats, distance, frequence) {}

        // Implémentation concrète de la méthode d'attaque
        virtual void attaque() const override {
            // Implémentation spécifique de l'attaque de corps à corps
        }
};

#endif // ARMES_CorpsaCorps_HPP