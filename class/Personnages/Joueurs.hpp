#ifndef JOUEURS
#define JOUEURS

#include "Personnages.hpp"
#include "Ennemi.hpp"

#include <string>

extern int width;
extern int height;

class Joueur : public Personnages {
    public:
        Joueur() {};
        Joueur(int fInt, float x, float y);

        // Attributs
        int nbXp;
        int cpt = 0;
        int maxCpt = 3;
        int etat = 0;
        int maxEtat = 3;

        float speedX = 0;
        float speedY = 0;

        int numjoueur = 1;

        void mouvement(float dx, float dy);
        void mouvement();
        void debug_mvt();
        void hitEnnemis(std::vector<Ennemi*>& lEnnemis, std::vector<Joueur*>& lJoueur);
};

#endif