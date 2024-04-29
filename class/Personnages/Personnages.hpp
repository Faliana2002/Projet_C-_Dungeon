#ifndef PERSONNAGES
#define PERSONNAGES

#include "../point.hpp"
#include "../Armes/CorpsaCorps.hpp"

#include <string>
#include <SFML/Graphics.hpp>

extern std::string reference;

class Personnages {
    public:
        Personnages(std::string textureFile, int x, int y) {
            texture.loadFromFile(reference + textureFile);
            
            position.setX(x);
            position.setY(y);

            sprite.setTexture(texture);
            sprite.setPosition(position.getX(), position.getY());
        };

        // Attributs
        std::string nom;
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