// Projet C++ Dungeon
// ROB4 | Polytech Sorbonne
// 29/04/2024

#include <iostream>
#include "Armes.hpp"
// #include "../Personnages/Ennemi.hpp"
// #include "../Personnages/Joueurs.hpp"
class Joueur;
class Ennemi;

#ifndef ARMES_Distance_HPP
#define ARMES_Distance_HPP

extern std::vector<std::tuple<std::string, float, float, float, float, float, float>> listeArmesDistance;

// Classe dérivée pour les armes à distance
class Distance : public Armes {
    public:
        // Utiliser le constructeur de la classe de base
        Distance(int indice);

        // Implémentation concrète de la méthode d'attaque
        // virtual void attaque(const std::vector<std::shared_ptr<Joueur>>& joueurs, const std::vector<std::shared_ptr<Ennemi>>& listenn, const Armes& arme) const override {
        //     // Implémentation spécifique de l'attaque à distance
        // }
        // Implémentation concrète de la méthode d'attaque
        void attaque(const std::vector<std::shared_ptr<Joueur>>& joueurs, const std::vector<std::shared_ptr<Ennemi>>& listenn, const Armes& arme) const override{};
        void infligerDegats(const std::vector<std::shared_ptr<Joueur>>& joueurs, const std::vector<std::shared_ptr<Ennemi>>& listenn, const Armes& arme) const override{};
        // Méthode pour vérifier si un ennemi est dans la zone de détection de l'arme
        float distanceEntreDeuxPoints(const Point& point1, const Point& point2) const;
        bool estDansZoneDetection(const Point& ennemiPosition, const Point& armePosition, float porteeDetection) const;

};

#endif // ARMES_Distance_HPP