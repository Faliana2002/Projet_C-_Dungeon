#ifndef JOUEURS
#define JOUEURS

#include "Personnages.hpp"

#include <string>

class Joueur : public Personnages {
    public:
        Joueur(std::string f, int x, int y) : Personnages(f, x, y) {}

        // Attributs
        int nbXp;

        void mouvement(int dx, int dy);
};

#endif