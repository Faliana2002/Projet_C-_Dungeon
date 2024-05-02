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
        Personnages();
        Personnages(int textureFileInt, int x, int y) {
            numPerso = textureFileInt;
            textureFile = listeJoueurs[textureFileInt];
            texture.loadFromFile(reference + textureFile + run + "0" + fin_str);
            
            position.setX(x);
            position.setY(y);

            sprite.setTexture(texture);
            sprite.setPosition(position.getX(), position.getY());

            // Redimensionner le sprite
            sprite.scale(scale_factor, scale_factor);
        };

        // Attributs
        std::string nom;
        std::string textureFile;
        Point position;
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

        // virtual method
        //virtual void attaquer()=0;
        //virtual void prendre()=0;
        virtual void mouvement(int dx, int dy)=0;
};

#endif