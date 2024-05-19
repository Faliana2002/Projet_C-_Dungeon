// Projet C++ Dungeon
// ROB4 | Polytech Sorbonne
// 29/04/2024
#ifndef ARMES_HPP
#define ARMES_HPP

#include <iostream>
#include <cstdlib>
#include <ctime>
#include <vector>
#include <SFML/Graphics.hpp>
#include <memory>

#include "../point.hpp"
#include "../Salles-test/Salles.hpp"
// #include "Projectile.hpp"
// #include "../Personnages/Ennemi.hpp"
// #include "../Personnages/Joueurs.hpp"
class Projectile;
class Ennemi;
class Joueur;



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
        int getIndice() const {return indice_;}
        float getRate() const {return rate_;}
        float getSpeed() const {return speed_;}
        virtual void attaque(std::vector<Ennemi*>& lEnnemis, std::vector<Joueur*>& lJoueur, const Armes& arme, std::vector<Projectile>& projectiles) const = 0;
        // virtual void infligerDegats(std::vector<Ennemi*>& lEnnemis, std::vector<Joueur*>& lJoueur, const Armes& arme) const = 0;
        // Méthode pour ajouter une arme à l'inventaire
        virtual void ajouterArmeInventaire(std::shared_ptr<Armes> arme){inventaire.push_back(arme);}

    protected:
        float degats_;               // Dégâts causés par l'arme
        float rate_;   // Fréquence à laquelle l'arme peut émettre des munitions
        int indice_;
        float scale_factor = 1.5;
        float speed_; // Vitesse de lancement des projectiles
    public:
        float distance_attaque_;     // Distance maximale, à laquelle l'arme peut atteindre l'ennemi
        sf::Texture texture;
        sf::Sprite sprite;
        std::string textureFile;
        std::vector<std::shared_ptr<Armes>> inventaire; // Inventaire des armes
        float porteeDetection; //= 10.0; La portée de détection (la moitié de la largeur du rectangle)
        float hauteurDetection; // La moitié de la hauteur du rectangle
        Point position;
        bool portee = false;
};

// Faire un spawner des armes
// Friendly allier

#endif // ARMES_HPP