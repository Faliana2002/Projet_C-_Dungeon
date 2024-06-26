#ifndef ENNEMIS
#define ENNEMIS

#include "../Salles-test/Salles.hpp"

#include "Personnages.hpp"
#include "Joueurs.hpp"

#include <string>
#include <cstdlib>
#include <ctime>
#include <algorithm>
#include <random>

extern int width;
extern int height;
extern float alea_mvt_max;

class Ennemi : public Personnages {
    public:
        Ennemi() {};
        Ennemi(int fInt, float x, float y);
        Ennemi(int fInt, Salles s, int n);

        // Attributs
        int cpt = 0;
        int maxCpt = 3;
        int etat = 0;
        int maxEtat = 3;
        int pointsDeVie; // Points de vie de l'ennemi
        
        Point objectif;

        float speedX = 1;
        float speedY = 0.5;

        void mouvement(float dx, float dy);
        void mouvement(float dx, float dy, Salles s);
        //void mouvement();
        void debug_mvt();
        //void aleatoire_mvt();
        //void aleatoire_mvt(Salles s);
        void aleatoire_mvt_2(const std::vector<Joueur*>& lJoueurs, Salles s);
        void suivi(Joueur& j);
        bool detecterEnnemi(std::vector<Joueur*>& lJoueur, const Armes& arme);
        Point detecteJoueur(const std::vector<Joueur*>& lJoueurs, Salles s);
        void hitEnnemis(std::vector<Joueur*>& lJoueur);
        void respawn(Salles s);
};

#endif