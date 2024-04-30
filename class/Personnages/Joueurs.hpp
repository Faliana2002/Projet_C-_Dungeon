#ifndef JOUEURS
#define JOUEURS

#include "Personnages.hpp"

#include <string>

extern int width;
extern int height;

class Joueur : public Personnages {
    public:
        Joueur(std::string f, int x, int y) : Personnages(f, x, y) {}

        // Attributs
        int nbXp;
        int cpt = 0;
        int maxCpt = 3;
        int etat = 0;
        int maxEtat = 3;

        int speedX = 1;
        int speedY = 1;

        int numjoueur = 1;

        void mouvement(int dx, int dy);
        void debug_mvt();
};

#endif