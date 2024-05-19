#include "Joueurs.hpp"

// Constructeur à partir de la référence dans la liste listeJoueurs et de la position de départ (x,y)
Joueur::Joueur(int textureFileInt, float x, float y) {
    auto now = std::chrono::system_clock::now();
    auto duration = now.time_since_epoch();
    startTimeHR = std::chrono::duration_cast<std::chrono::milliseconds>(duration).count();

    numPerso = textureFileInt;
    // Set grande taille
    textureFile = listeJoueurs[2];
    texture.loadFromFile(reference + textureFile + run + "0" + fin_str);
    
    position.setX(x);
    position.setY(y);

    positionOrigine = position;

    positionVie.setX(x - width_*scale_factor/2);
    positionVie.setY(y - height*(scale_factor+1));

    // Positionnement barre de vie
    barrevie.position_red = positionVie;
    barrevie.position_white.setX(positionVie.getX() + width_*scale_factor);
    barrevie.position_red.setY(positionVie.getY());
    barrevie.draw_life();

    sprite.setTexture(texture);
    sprite.setPosition(position.getX(), position.getY());

    // Redimensionner le sprite
    sprite.scale(scale_factor, scale_factor);
};

// Mouvement en fonction de dx et dy
void Joueur::mouvement(float dx, float dy) {
    position += Point(dx,dy);

    textureFile = listeJoueurs[numPerso];

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
/*
// Mouvement en fonction de dx et dy
void Joueur::mouvement() {
    int dx = speedX;
    int dy = speedY;

    textureFile = listeJoueurs[numPerso];
    
    if (position.getX() + speedX + width_*scale_factor < width && position.getX() + speedX > 0) {
        position += Point(dx, 0);
    }
    else if (vie > 0){
        vie -= 1;
    }

    if (position.getY() + speedY + (height_ -6)*scale_factor < height && position.getY() + speedY + 6 > 0) {
        position += Point(0,dy);
    }
    else if (vie < vieMax){
        vie += 1;
    }

    positionArme.setY(position.getY());

    positionVie.setX(position.getX());
    positionVie.setY(position.getY() + height_*scale_factor);
    barrevie.width_red = (float)vie/(float)vieMax*width_*scale_factor;
    barrevie.width_white = width_*scale_factor - barrevie.width_red;

    // Positionnement barre de vie
    barrevie.position_red = positionVie;
    barrevie.position_white.setX(positionVie.getX() + barrevie.width_red);
    barrevie.position_white.setY(positionVie.getY());
    barrevie.draw_life();

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
            positionArme.setX(position.getX()+width_*scale_factor);
        }
        else if (dx == 0)  {
            sprite.setPosition(position.getX()+width_*scale_factor*mirrored, position.getY());
            positionArme.setX(position.getX()+width_*scale_factor);
        }
        else {
            sprite.setPosition(position.getX(), position.getY());
            sprite.setScale(scale_factor,scale_factor);
            mirrored = 0;
            positionArme.setX(position.getX() - width_*2);
        }

        if (armes != nullptr)  {
            armes->sprite.setPosition(positionArme.getX(), positionArme.getY());
            armes->position = positionArme;
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
}*/

// Mouvement en fonction de dx et dy en fonction de la salle
void Joueur::mouvement(Salles s) {
    int dx = speedX;
    int dy = speedY;

    textureFile = listeJoueurs[numPerso];

    int w = width_*scale_factor;
    int h = height_*scale_factor;

    if (s.isIn(position+Point(dx,0)) && s.isIn(position+Point(dx+w,0)) && s.isIn(position+Point(dx+w,0+h)) && s.isIn(position+Point(dx,0+h))) {
        position += Point(dx,0);
    }
    if (s.isIn(position+Point(0,dy)) && s.isIn(position+Point(0+w,dy)) && s.isIn(position+Point(0+w,dy+h)) && s.isIn(position+Point(0,dy+h))) {
        position += Point(0,dy);
    }

    positionArme.setY(position.getY());

    positionVie.setX(position.getX());
    positionVie.setY(position.getY() + height_*scale_factor);
    barrevie.width_red = (float)vie/(float)vieMax*width_*scale_factor;
    barrevie.width_white = width_*scale_factor - barrevie.width_red;

    // Positionnement barre de vie
    barrevie.position_red = positionVie;
    barrevie.position_white.setX(positionVie.getX() + barrevie.width_red);
    barrevie.position_white.setY(positionVie.getY());
    barrevie.draw_life();

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
            positionArme.setX(position.getX()+width_*scale_factor);
        }
        else if (dx == 0)  {
            sprite.setPosition(position.getX()+width_*scale_factor*mirrored, position.getY());
            positionArme.setX(position.getX()+width_*scale_factor);
        }
        else {
            sprite.setPosition(position.getX(), position.getY());
            sprite.setScale(scale_factor,scale_factor);
            mirrored = 0;
            positionArme.setX(position.getX() - width_*2);
        }

        if (armes != nullptr)  {
            armes->sprite.setPosition(positionArme.getX(), positionArme.getY());
            armes->position = positionArme;
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
void Joueur::debug_mvt() {
    mouvement(speedX,speedY);
            
    if (position.getX() + speedX + width_*scale_factor > width || position.getX() + speedX < 0) {
        speedX *= -1;
    }

    if (position.getY() + speedY + height_*scale_factor > height || position.getY() + speedY < 0) {
        speedY *= -1;
    }

}

// Inflige des dégats à tous les ennemis proches
void Joueur::hitEnnemis(std::vector<Ennemi*>& lEnnemis, std::vector<Joueur*>& lJoueur) {
    auto now = std::chrono::system_clock::now();
    auto duration = now.time_since_epoch();
    currentTimeHR = std::chrono::duration_cast<std::chrono::milliseconds>(duration).count();
    if (currentTimeHR - startTimeHR > 1000/armes->getRate()) {
        startTimeHR = currentTimeHR;

        for (Ennemi* e : lEnnemis) {
            int d_attaque = (int) armes->distance_attaque_;

            int gauche = e->position.getX() - d_attaque;
            int haut = e->position.getY() - d_attaque;

            int droite = gauche + e->width_*e->scale_factor + 2*d_attaque;
            int bas = haut + e->height_*e->scale_factor + 2*d_attaque;

            int jx = position.getX(), jy = position.getY();

            if (jx >= gauche && jx <= droite && jy >= haut && jy <= bas) e->recevoirDegats(armes);
        }
        for (Joueur* j : lJoueur) {
            if(j != this) {
                int d_attaque = (int) armes->distance_attaque_;

                int gauche = j->position.getX() - d_attaque;
                int haut = j->position.getY() - d_attaque;

                int droite = gauche + j->width_*j->scale_factor + 2*d_attaque;
                int bas = haut + j->height_*j->scale_factor + 2*d_attaque;

                int jx = position.getX(), jy = position.getY();

                if (jx >= gauche && jx <= droite && jy >= haut && jy <= bas) j->recevoirDegats(armes);
            }
        }
    }
    else startTimeHR = currentTimeHR;
}