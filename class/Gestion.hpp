#ifndef GESTION
#define GESTION

#include <ncurses.h>

#include "Personnages/Joueurs.hpp"

class Gestion {
    public:
        Gestion(Joueur& j1, Joueur& j2);
        //Gestion(Joueur j1);

        //void addJoueur(Joueur j);
        int getNbJoueur() {return nbJoueur;};
        //void echangeJoueur();   // Pour échanger les contrôles
        void entreeUtilisateur(int key);

    private:
        //Joueur* listeJoueurs[2];
        Joueur j1;
        Joueur j2;

        int nbJoueur = 0;
};

#endif