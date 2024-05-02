#ifndef JOUEURS
#define JOUEURS

#include "Personnages.hpp"

#include <string>

extern int width;
extern int height;

class Joueur : public Personnages {
    public:
        Joueur() {};
        Joueur(int fInt, int x, int y) : Personnages(fInt, x, y) {}

        // Attributs
        int nbXp;
        int cpt = 0;
        int maxCpt = 3;
        int etat = 0;
        int maxEtat = 3;

        int speedX = 0;
        int speedY = 0;

        int numjoueur = 1;

        void mouvement(int dx, int dy);
        void mouvement();
        void debug_mvt();
};

#endif