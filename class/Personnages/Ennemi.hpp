#ifndef ENNEMIS
#define ENNEMIS

#include "../Salles-test/Salles.hpp"

#include "Personnages.hpp"
#include "Joueurs.hpp"

#include <string>
#include <cstdlib>
#include <ctime>
#include <algorithm>

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
        int pointsDeVie; // Points de vie de l'ennemi
        
        Point objectif;

        float speedX = 1;
        float speedY = 0.5;

        void mouvement(float dx, float dy);
        void mouvement();
        void debug_mvt();
        void aleatoire_mvt();
        void aleatoire_mvt(Salles s);
        void aleatoire_mvt_2(const std::vector<Joueur*>& lJoueurs, Salles s);
        void suivi(Joueur& j);
        bool detecterEnnemi(const std::vector<std::shared_ptr<Joueur>>& joueurs, const Armes& arme);
        Point detecteJoueur(const std::vector<Joueur*>& lJoueurs, Salles s);
        void hitEnnemis(std::vector<Joueur*>& lJoueur);
};

#endif