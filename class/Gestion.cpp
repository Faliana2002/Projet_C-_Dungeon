#include "Gestion.hpp"

Gestion::Gestion(Joueur& j1, Joueur& j2) {
    //listeJoueurs[0] = &j1;
    //listeJoueurs[1] = &j2;
    this->j1 = j1;
    this->j2 = j2;
    nbJoueur = 2;
}
/*
Gestion::Gestion(Joueur j1) {
    listeJoueurs[0] = &j1;
    nbJoueur = 1;
}

void Gestion::addJoueur(Joueur j) {
    if (nbJoueur < 2) {
        nbJoueur++;
        listeJoueurs[nbJoueur] = &j;
    }
}

// Echanger les joueurs dans la liste pour échanger les contrôles
void Gestion::echangeJoueur() {
    Joueur* mem = listeJoueurs[0];
    listeJoueurs[0] = listeJoueurs[1];
    listeJoueurs[1] = mem;
}*/

void Gestion::entreeUtilisateur(int key) {
    int d1x = 0, d1y = 0;//, d2x = 0, d2y = 0;
    switch (key) {
        case KEY_UP:
            d1y = -1;
            break;
        case 0:
            d1y = 1;
            break;
        case KEY_LEFT:
            d1x = -1;
            break;
        case KEY_RIGHT:
            d1x = 1;
            break;
    }
    std::cout << d1y << std::endl;
    //if (nbJoueur >= 2) listeJoueurs[0]->mouvement(d1x, d1y); // On met à jour le premier joueur
    if (nbJoueur >= 2) j1.mouvement(d1x, d1y); // On met à jour le premier joueur

}