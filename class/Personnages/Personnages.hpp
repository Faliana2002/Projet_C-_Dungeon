#ifndef PERSONNAGES
#define PERSONNAGES

#include "../point.hpp"
#include "../Armes/CorpsaCorps.hpp"
#include "../Armes/Armes.hpp"

#include <string>
#include <SFML/Graphics.hpp>

extern std::string reference;
extern std::string idle;
extern std::string run;
extern std::string fin_str;

extern std::string listeJoueurs[];
extern std::string listeEnnemi[];

class Personnages {
    public:
        // Attributs
        std::string nom;
        std::string textureFile;
        Point position;
        Point positionArme;
        int numPerso = 0;
        bool estVivant;
        int vieMax;
        int vie;
        int vitesseDeplacement;
        int width_ = 16;
        int height_ = 28;
        int rtp = 0;
        bool start = true;
        int mirrored = 0;
        //CorpsaCorps arme;
        sf::Texture texture;
        sf::Sprite sprite;

        // Définir le facteur d'agrandissement
        float scale_factor = 4.0f;

        Armes* armes = nullptr;

        // virtual method
        //virtual void attaquer()=0;
        //virtual void prendre()=0;
        virtual void mouvement(float dx, float dy)=0;
};

#endif