// Projet C++ Dungeon
// ROB4 | Polytech Sorbonne
// 29/04/2024

#ifndef ARMES_CorpsaCorps_HPP
#define ARMES_CorpsaCorps_HPP

#include "Armes.hpp"
class Joueur;
class Ennemi;


extern std::vector<std::tuple<std::string, float, float, float, float, float, float>> listeArmesCAC;

// Classe dérivée pour les armes de corps à corps
class CorpsaCorps : public Armes {
    public:
        Armes* arme_a_ramasser; // Attribut représentant l'arme à ramasser
        // Utiliser le constructeur de la classe de base
        CorpsaCorps(int indice, Salles s, int n);

        // Implémentation concrète de la méthode d'attaque
        void attaque(std::vector<Ennemi*>& lEnnemis, std::vector<Joueur*>& lJoueur, const Armes& arme, std::vector<Projectile>& projectiles) const override;
        void infligerDegats(std::vector<Ennemi*>& lEnnemis, std::vector<Joueur*>& lJoueur, const Armes& arme) const;
};

#endif // ARMES_CorpsaCorps_HPP