#ifndef GESTION
#define GESTION

#include <SFML/Graphics.hpp>

#include "Personnages/Joueurs.hpp"

class Gestion {
    public:
        Gestion() {};
        
        void entryManager(sf::Event event, sf::RenderWindow& window, Joueur& j1, Joueur& j2);
        void startManager(sf::Event event, sf::RenderWindow& window, Joueur& j1, Joueur& j2);
};

#endif