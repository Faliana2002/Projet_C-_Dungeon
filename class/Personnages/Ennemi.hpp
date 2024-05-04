#ifndef ENNEMIS
#define ENNEMIS

#include "Personnages.hpp"

#include <string>
#include <cstdlib>
#include <ctime>

extern int width;
extern int height;
extern float alea_mvt_max;

class Ennemi : public Personnages {
    public:
        Ennemi() {};
        Ennemi(int fInt, float x, float y);
        Ennemi(int fInt);

        // Attributs
        int cpt = 0;
        int maxCpt = 3;
        int etat = 0;
        int maxEtat = 3;
        Point objectif;

        float speedX = 1;
        float speedY = 0.5;

        void mouvement(float dx, float dy);
        void mouvement();
        void debug_mvt();
        void aleatoire_mvt();
};

#endif