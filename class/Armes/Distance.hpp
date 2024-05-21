// Projet C++ Dungeon
// ROB4 | Polytech Sorbonne
// 29/04/2024

#include <iostream>
#include "Armes.hpp"
#include "Projectile.cpp"
#include "../Personnages/Ennemi.hpp"
#include "../Personnages/Joueurs.hpp"

#ifndef ARMES_Distance_HPP
#define ARMES_Distance_HPP

// Liste stockée dans le fichier "declaration.hpp" regroupant l'ensemble des armes qui attaquent à distance
extern std::vector<std::tuple<std::string, float, float, float, float, float, float>> listeArmesDistance;

// Classe dérivée de la classe Armes pour les armes à distance
class Distance : public Armes {
    public:
        // Constructeur par défaut
        Distance() {}

        // Constructeur dépendant des salles
        Distance(int indice, Salles s, int n);

        // Implémentation concrète de la méthode d'attaque
        virtual void attaque(std::vector<Ennemi*>& lEnnemis, std::vector<Joueur*>& lJoueur, const Armes& arme, std::vector<Projectile>& projectiles) const override;
};

#endif // ARMES_Distance_HPP