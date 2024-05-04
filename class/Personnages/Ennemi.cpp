#include "Ennemi.hpp"

Ennemi::Ennemi(int textureFileInt) {
    // Initialisation du générateur de nombres pseudo-aléatoires
    std::srand(static_cast<unsigned int>(std::time(nullptr)));

    int maxX = static_cast<int>(width);
    int maxY = static_cast<int>(height);
        
    int x = rand()%maxX;
    int y = rand()%maxY;
    
    numPerso = textureFileInt;
    // Set grande taille
    textureFile = listeEnnemi[10];
    texture.loadFromFile(reference + textureFile + run + "0" + fin_str);
    
    position.setX(x);
    position.setY(y);
    objectif.setX(x);
    objectif.setY(y);

    sprite.setTexture(texture);
    sprite.setPosition(position.getX(), position.getY());

    // Redimensionner le sprite
    sprite.scale(scale_factor, scale_factor);
}

Ennemi::Ennemi(int textureFileInt, float x, float y) {
    numPerso = textureFileInt;
    // Set grande taille
    textureFile = listeEnnemi[10];
    texture.loadFromFile(reference + textureFile + run + "0" + fin_str);
    
    position.setX(x);
    position.setY(y);
    objectif.setX(x);
    objectif.setY(y);

    sprite.setTexture(texture);
    sprite.setPosition(position.getX(), position.getY());

    // Redimensionner le sprite
    sprite.scale(scale_factor, scale_factor);

    // Initialisation du générateur de nombres pseudo-aléatoires
    std::srand(static_cast<unsigned int>(std::time(nullptr)));
};

void Ennemi::mouvement(float dx, float dy) {
    position += Point(dx,dy);

    textureFile = listeEnnemi[numPerso];

    if (dx != 0 && dy != 0) texture.loadFromFile(reference + textureFile + run + std::to_string(etat) + fin_str);
    else texture.loadFromFile(reference + textureFile + idle + std::to_string(etat) + fin_str);

    //sprite.setTexture(texture);
    // Redimensionner le sprite
    //sprite.scale(scale_factor, scale_factor);

    sprite.setPosition(position.getX(), position.getY());

    cpt++;

    if (cpt > maxCpt) {
        etat++;
        cpt = 0;
    }
    
    if (etat > maxEtat) etat = 0;
}

void Ennemi::mouvement() {
    int dx = speedX;
    int dy = speedY;

    textureFile = listeEnnemi[numPerso];
    
    if (position.getX() + speedX + width_*scale_factor < width && position.getX() + speedX > 0) {
        position += Point(dx, 0);
    }

    if (position.getY() + speedY + (height_ -6)*scale_factor < height && position.getY() + speedY + 6 > 0) {
        position += Point(0,dy);
    }

    //position += Point(dx,dy);

    if (dx != 0 || dy != 0) texture.loadFromFile(reference + textureFile + run + std::to_string(etat) + fin_str);
    else texture.loadFromFile(reference + textureFile + idle + std::to_string(etat) + fin_str);

    //sprite.setTexture(texture);
    // Redimensionner le sprite
    //sprite.scale(scale_factor, scale_factor);

    if (dx != 0 || dy != 0 || start) {
        if (dx < 0) {
            sprite.setPosition(position.getX()+width_*scale_factor, position.getY());
            sprite.setScale(-scale_factor,scale_factor);
            mirrored = 1;
        }
        else if (dx == 0)  {
            sprite.setPosition(position.getX()+width_*scale_factor*mirrored, position.getY());
        }
        else {
            sprite.setPosition(position.getX(), position.getY());
            sprite.setScale(scale_factor,scale_factor);
            mirrored = 0;
        }
    }

    cpt++;

    if (cpt > maxCpt) {
        etat++;
        cpt = 0;
    }
    
    if (etat > maxEtat) etat = 0;

    //speedX = 0;
    //speedY = 0;
}

// Vitesse 1 sur les deux axes pour des tests
void Ennemi::debug_mvt() {
    mouvement(speedX,speedY);
            
    if (position.getX() + speedX + width_*scale_factor > width || position.getX() + speedX < 0) {
        speedX *= -1;
    }

    if (position.getY() + speedY + height_*scale_factor > height || position.getY() + speedY < 0) {
        speedY *= -1;
    }

}

void Ennemi::aleatoire_mvt() {
    if (abs(objectif.getX() - position.getX()) < 30 && abs(objectif.getY() - position.getY()) < 30) {
        int maxX = static_cast<int>(width);
        int maxY = static_cast<int>(height);
            
        objectif.setX(rand()%maxX);
        objectif.setY(rand()%maxY);

        float tx = objectif.getX() - position.getX();
        float ty = objectif.getY() - position.getY();
        float tmax;
        if (abs(tx) > abs(ty)) tmax = abs(tx);
        else tmax = abs(ty);

        speedX = tx/tmax;
        speedY = ty/tmax;

        if (speedX > 0) sprite.setScale(scale_factor,scale_factor);
        else if (speedX < 0) sprite.setScale(-scale_factor,scale_factor);    
    }

    mouvement(speedX,speedY);
}