// Projet C++ Dungeon
// ROB4 | Polytech Sorbonne
// 29/04/2024

#include <iostream>
#include "Armes.hpp"
#include "Projectile.cpp"
#include "../Personnages/Ennemi.hpp"
#include "../Personnages/Joueurs.hpp"
// class Joueur;
// class Ennemi;

#ifndef ARMES_Distance_HPP
#define ARMES_Distance_HPP

extern std::vector<std::tuple<std::string, float, float, float, float, float, float>> listeArmesDistance;

// Classe dérivée pour les armes à distance
class Distance : public Armes {
    public:

        Distance() {}
        // Utiliser le constructeur de la classe de base
        Distance(int indice, Salles s, int n);

        // Implémentation concrète de la méthode d'attaque
        virtual void attaque(std::vector<Ennemi*>& lEnnemis, std::vector<Joueur*>& lJoueur, const Armes& arme, std::vector<Projectile>& projectiles) const override;
        // void attaque_distance(std::vector<Ennemi*>& lEnnemis, std::vector<Joueur*>& lJoueur, Projectile& munition);
        //void simulateKeyPress(std::vector<Joueur*>& lJoueurs, std::vector<Ennemi*>& lEnnemis, Projectile& munition);
        void respawn(Salles s);
};

#endif // ARMES_Distance_HPP