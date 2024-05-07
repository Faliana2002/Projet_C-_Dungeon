#ifndef PERSONNAGES
#define PERSONNAGES

#include "../point.hpp"
#include "../Armes/CorpsaCorps.hpp"
#include "../Armes/Armes.hpp"
#include "BarreVie.hpp"

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
        Point positionVie;
        int numPerso = 0;
        bool estVivant;
        int vieMax = 64;
        int vie = 64;
        int vitesseDeplacement;
        int width_ = 16;
        int height_ = 28;
        int rtp = 0;
        bool start = true;
        int mirrored = 0;
        //CorpsaCorps arme;
        sf::Texture texture;
        sf::Sprite sprite;
        BarreVie barrevie;

        // Définir le facteur d'agrandissement
        float scale_factor = 3.0f;

        Armes* armes = nullptr;

        // virtual method
        //virtual void attaquer()=0;
        //virtual void prendre()=0;
        virtual void mouvement(float dx, float dy)=0;
        
        Point getPosition() const {
            return position; // Supposons que la position de l'ennemi est stockée dans un objet de type Point
        }
        void recevoirDegats(const Armes& arme){
            // Soustraire les dégâts des points de vie de l'ennemi en utilisant les dégâts de l'arme
            vie -= arme.getDegats();

            // Vérifier si l'ennemi est toujours en vie
            if (vie <= 0) {
                // L'ennemi est vaincu
                vie = 0; // Éviter les valeurs négatives
                estVivant = false; // Marquer l'ennemi comme étant vaincu
                std::cout << "L'ennemi a été vaincu !" << std::endl;
                // Autres actions à effectuer lorsque l'ennemi est vaincu...
            } else {
                // L'ennemi est toujours en vie
                std::cout << "L'ennemi subit des dégâts mais est toujours en vie." << std::endl;
            }
        }
};

#endif