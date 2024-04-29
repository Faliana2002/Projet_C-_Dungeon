#ifndef JOUEURS
#define JOUEURS

#include "Personnages.hpp"

class Joueur : public Personnages {
    Joueur();

    // Attributs
    int nbXp;
    string nomFichier;
};

#endif