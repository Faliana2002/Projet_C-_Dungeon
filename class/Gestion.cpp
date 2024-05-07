#include "Gestion.hpp"

extern int nbLJoueur;
extern int nbLEnnemi;

void Gestion::entryManager(sf::Event event, sf::RenderWindow& window, Joueur& j1, Joueur& j2, std::vector<Armes*>& lArmes) {
    if (event.type == sf::Event::KeyPressed) {
        if (event.key.code == sf::Keyboard::Up)
            // Gérer l'appui sur la touche Haut
            j1.speedY = -2;
        else if (event.key.code == sf::Keyboard::Down)
            // Gérer l'appui sur la touche Bas
            j1.speedY = 2;
        if (event.key.code == sf::Keyboard::Left)
            // Gérer l'appui sur la touche Gauche
            j1.speedX = -2;
        else if (event.key.code == sf::Keyboard::Right)
            // Gérer l'appui sur la touche Droite
            j1.speedX = 2;
        if (event.key.code == sf::Keyboard::Z)
            // Gérer l'appui sur la touche Haut
            j2.speedY = -2;
        else if (event.key.code == sf::Keyboard::S)
            // Gérer l'appui sur la touche Bas
            j2.speedY = 2;
        if (event.key.code == sf::Keyboard::Q)
            // Gérer l'appui sur la touche Gauche
            j2.speedX = -2;
        else if (event.key.code == sf::Keyboard::D)
            // Gérer l'appui sur la touche Droite
            j2.speedX = 2;
        if (event.key.code == sf::Keyboard::RShift) {
            if (j1.armes == nullptr) {
                for (Armes* a : lArmes) {
                    if ( abs(a->position.getX() - j1.position.getX()) < 50 && abs(a->position.getY() - j1.position.getY()) < 150 && a->portee == false && j1.armes == nullptr) {
                        j1.armes = a;
                        a->sprite.setPosition(j1.positionArme.getX(), j1.positionArme.getY());
                        a->portee = true;
                    }
                }
            } 
            else {
                j1.armes->portee = false;
                j1.armes = nullptr;
            }
        }
        if (event.key.code == sf::Keyboard::E) {
            if (j2.armes == nullptr) {
                for (Armes* a : lArmes) {
                    if ( abs(a->position.getX() - j2.position.getX()) < 50 && abs(a->position.getY() - j2.position.getY()) < 150 && a->portee == false && j2.armes == nullptr) {
                        j2.armes = a;
                        a->sprite.setPosition(j2.positionArme.getX(), j2.positionArme.getY());
                        a->portee = true;
                    }
                }
            } 
            else {
                j2.armes->portee = false;
                j2.armes = nullptr;
            }
        }
    }
    else if (event.type == sf::Event::KeyReleased) {
        // Réinitialisation des vitesses lorsque les touches sont relâchées
        if (event.key.code == sf::Keyboard::Up || event.key.code == sf::Keyboard::Down)
            j1.speedY = 0;
        if (event.key.code == sf::Keyboard::Left || event.key.code == sf::Keyboard::Right)
            j1.speedX = 0;
        if (event.key.code == sf::Keyboard::Z || event.key.code == sf::Keyboard::S)
            j2.speedY = 0;
        if (event.key.code == sf::Keyboard::Q || event.key.code == sf::Keyboard::D)
            j2.speedX = 0;
    }

    if (event.key.code == sf::Keyboard::U) {
            // Gérer l'appui sur la touche Gauche
            j1.rtp = 0;
            j2.rtp = 0;
            j1.position = Point(960-16*4/2, 360-28*4/2);
            j2.position = Point(320-16*4/2, 360-28*4/2);
            j1.start = true;
            j2.start = true;
    }
}

void Gestion::startManager(sf::Event event, sf::RenderWindow& window, Joueur& j1, Joueur& j2) {
    if (event.type == sf::Event::KeyPressed) {
        if (event.key.code == sf::Keyboard::Up || event.key.code == sf::Keyboard::Down) {
            // Gérer l'appui sur la touche Gauche
            j1.rtp = 1;
            j1.start = false;
        }
        if (event.key.code == sf::Keyboard::Left)
            // Gérer l'appui sur la touche Gauche
            j1.numPerso--;
        else if (event.key.code == sf::Keyboard::Right)
            // Gérer l'appui sur la touche Droite
            j1.numPerso++;
        if (event.key.code == sf::Keyboard::Z || event.key.code == sf::Keyboard::S) {
            // Gérer l'appui sur la touche Gauche
            j2.rtp = 1;
            j2.start = false;
        }
        if (event.key.code == sf::Keyboard::Q)
            // Gérer l'appui sur la touche Gauche
            j2.numPerso--;
        else if (event.key.code == sf::Keyboard::D)
            // Gérer l'appui sur la touche Droite
            j2.numPerso++;
    } 
    if (j1.numPerso < 0) j1.numPerso++;
    if (j1.numPerso >= nbLJoueur) j1.numPerso--;
    if (j2.numPerso < 0) j2.numPerso++;
    if (j2.numPerso >= nbLJoueur) j2.numPerso--;

}