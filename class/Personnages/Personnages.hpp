#ifndef PERSONNAGES
#define PERSONNAGES

#include "../point.hpp"

#include <string>
using namespace std;

class Armes {};

class Personnages {
    Personnages();

    // Attributs
    string nom;
    Point position;
    bool estVivant;
    int vieMax;
    int vie;
    int vitesseDeplacement;
    Armes arme;

    // virtual method
    virtual void attaquer()=0;
    virtual void prendre()=0;
    virtual void seDeplacer(int dx, int dy)=0;
    
};

#endif