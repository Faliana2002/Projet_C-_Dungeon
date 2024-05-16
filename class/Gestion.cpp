#include "Gestion.hpp"

void Gestion::entryManager(sf::Event event, sf::RenderWindow& window, std::vector<Joueur*>& lJoueurs, std::vector<Armes*>& lArmes, std::vector<Ennemi*>& lEnnemis) {
    if (event.type == sf::Event::KeyPressed) {
        for (int i = 0; i < nbJoueur; i++) {
            if (lJoueurs[i]->estVivant) {
                // Haut-bas
                if (event.key.code == toucheJoueur[i][0]) lJoueurs[i]->speedY = -2;
                else if (event.key.code == toucheJoueur[i][1]) lJoueurs[i]->speedY = 2;
                // Gauche-droite
                if (event.key.code == toucheJoueur[i][2]) lJoueurs[i]->speedX = -2;
                else if (event.key.code == toucheJoueur[i][3]) lJoueurs[i]->speedX = 2;
                // Ramasser-jeter
                if (event.key.code == toucheJoueur[i][4]) {
                    if (lJoueurs[i]->armes == nullptr) {
                        for (Armes* a : lArmes) {
                            if ( abs(a->position.getX() - lJoueurs[i]->position.getX()) < 50 && abs(a->position.getY() - lJoueurs[i]->position.getY()) < 150 && a->portee == false && lJoueurs[i]->armes == nullptr) {
                                lJoueurs[i]->armes = a;
                                a->sprite.setPosition(lJoueurs[i]->positionArme.getX(), lJoueurs[i]->positionArme.getY());
                                a->portee = true;
                            }
                        }    
                    }
                    else {
                        lJoueurs[i]->armes->portee = false;
                        lJoueurs[i]->armes = nullptr;
                    }
                }

                if (event.key.code == toucheJoueur[i][5]) {
                    if(lJoueurs[i]->armes != nullptr) lJoueurs[i]->hitEnnemis(lEnnemis, lJoueurs);
                    // Test attaque_distance
                    /*
                    if (lJoueurs[i]->armes != nullptr && lJoueurs[i]->armes->getIndice() == 0) { // Vérifiez ici si l'indice 0 correspond bien aux armes à distance
                        Projectile munition(0, Vec2(1, 0)); // Exemple avec un vecteur directionnel prédéfini
                        Distance distanceObj;
                        distanceObj.attaque(lEnnemis, lJoueurs, *lJoueurs[i]->armes, munition);
                    }
                    //*/
                }
            }
        }
    }
    
    else if (event.type == sf::Event::KeyReleased) {
        for (int i = 0; i < nbJoueur; i++) {
            if (event.key.code == toucheJoueur[i][0] || event.key.code == toucheJoueur[i][1]) lJoueurs[i]->speedY = 0;
            if (event.key.code == toucheJoueur[i][2] || event.key.code == toucheJoueur[i][3]) lJoueurs[i]->speedX = 0;
        }
    }

    if (event.key.code == sf::Keyboard::T) {
        for (int i = 0; i < nbJoueur; i++) {
            lJoueurs[i]->rtp = 0;   // rpt : Ready To Play
            lJoueurs[i]->position = lJoueurs[i]->positionOrigine;
            lJoueurs[i]->start = true;
        }
    }
}

void Gestion::startManager(sf::Event event, sf::RenderWindow& window, std::vector<Joueur*>& lJoueurs) {
    if (event.type == sf::Event::KeyPressed) {
        for (int i = 0; i < nbJoueur; i++) {
            if (event.key.code == toucheJoueur[i][0] || event.key.code == toucheJoueur[i][0]) {
                lJoueurs[i]->rtp = 1;   // Ready To Play
                lJoueurs[i]->start = false; // N'est plus dans l'état de start
            }
            if (event.key.code == toucheJoueur[i][2] && lJoueurs[i]->numPerso > 0) lJoueurs[i]->numPerso--;
            else if (event.key.code == toucheJoueur[i][3] && lJoueurs[i]->numPerso < nbLJoueur-1) lJoueurs[i]->numPerso++;            
        }
    }
}