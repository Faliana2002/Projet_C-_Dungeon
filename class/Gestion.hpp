#ifndef GESTION
#define GESTION

#include <SFML/Graphics.hpp>

#include "Personnages/Joueurs.hpp"

class Gestion {
    public:
        Gestion() {};
        
        void entryManager(sf::Event event, sf::RenderWindow& window, std::vector<Joueur*>& lJoueurs, std::vector<Armes*>& lArmes);
        void startManager(sf::Event event, sf::RenderWindow& window, std::vector<Joueur*>& lJoueurs);
};

#endif