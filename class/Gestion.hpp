#ifndef GESTION
#define GESTION

#include <SFML/Graphics.hpp>

#include "Personnages/Joueurs.hpp"

extern int nbJoueur;
extern int nbLJoueur;
extern int nbLEnnemi;
extern int toucheJoueur[3][6];

class Gestion {
    public:
        Gestion() {};
        
        void entryManager(sf::Event event, sf::RenderWindow& window, std::vector<Joueur*>& lJoueurs, std::vector<Armes*>& lArmes, std::vector<Ennemi*>& lEnnemis);
        void startManager(sf::Event event, sf::RenderWindow& window, std::vector<Joueur*>& lJoueurs);
};

#endif