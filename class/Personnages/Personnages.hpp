#ifndef PERSONNAGES
#define PERSONNAGES

#include "../point.hpp"
#include "../Armes/CorpsaCorps.hpp"

#include <string>
#include <SFML/Graphics.hpp>

extern std::string reference;
extern std::string idle;
extern std::string run;
extern std::string fin_str;

extern std::string listeJoueurs[];

class Personnages {
    public:
        Personnages(std::string textureFile, int x, int y) {
            this->textureFile = textureFile;
            texture.loadFromFile(reference + textureFile + run + "0" + fin_str);
            
            position.setX(x);
            position.setY(y);

            sprite.setTexture(texture);
            sprite.setPosition(position.getX(), position.getY());
        };

        // Attributs
        std::string nom;
        std::string textureFile;
        Point position;
        bool estVivant;
        int vieMax;
        int vie;
        int vitesseDeplacement;
        //int width = 16;
        //int height = 16;
        //CorpsaCorps arme;
        sf::Texture texture;
        sf::Sprite sprite;

        // virtual method
        //virtual void attaquer()=0;
        //virtual void prendre()=0;
        virtual void mouvement(int dx, int dy)=0;
};

#endif