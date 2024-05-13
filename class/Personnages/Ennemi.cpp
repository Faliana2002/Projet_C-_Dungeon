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
    textureFile = listeEnnemi[7];
    texture.loadFromFile(reference + textureFile + run + "0" + fin_str);
    
    position.setX(x);
    position.setY(y);
    objectif.setX(x);
    objectif.setY(y);

    sprite.setTexture(texture);
    sprite.setPosition(position.getX(), position.getY());

    // Redimensionner le sprite
    if (numPerso != 14) sprite.scale(scale_factor, scale_factor);
    else sprite.scale(scale_factor/4,scale_factor/4);
}

Ennemi::Ennemi(int textureFileInt, float x, float y) {
    //if (textureFileInt == 14) scale_factor = 1.0;

    numPerso = textureFileInt;
    // Set grande taille
    if (textureFileInt != 14) textureFile = listeEnnemi[10];
    else textureFile = listeEnnemi[14];
    texture.loadFromFile(reference + textureFile + run + "0" + fin_str);
    
    position.setX(x);
    position.setY(y);
    objectif.setX(x);
    objectif.setY(y);

    sprite.setTexture(texture);
    sprite.setPosition(position.getX(), position.getY());

    // Redimensionner le sprite
    if (numPerso != 14) sprite.scale(scale_factor, scale_factor);
    else sprite.scale(scale_factor/4,scale_factor/4);

    // Initialisation du générateur de nombres pseudo-aléatoires
    std::srand(static_cast<unsigned int>(std::time(nullptr)));
};

void Ennemi::mouvement(float dx, float dy) {
    position += Point(dx,dy);

    textureFile = listeEnnemi[numPerso];

    if (dx != 0 && dy != 0) texture.loadFromFile(reference + textureFile + run + std::to_string(etat) + fin_str);
    else texture.loadFromFile(reference + textureFile + idle + std::to_string(etat) + fin_str);

    positionArme.setY(position.getY());

    positionVie.setX(position.getX());
    if (numPerso != 14) positionVie.setY(position.getY() + height_*scale_factor);
    else positionVie.setY(position.getY() + height_*(scale_factor-1));
    barrevie.width_red = (float)vie/(float)vieMax*width_*scale_factor;
    barrevie.width_white = width_*scale_factor - barrevie.width_red;

    // Positionnement barre de vie
    barrevie.position_red = positionVie;
    barrevie.position_white.setX(positionVie.getX() + barrevie.width_red);
    barrevie.position_white.setY(positionVie.getY());
    barrevie.draw_life();

    //sprite.setTexture(texture);
    // Redimensionner le sprite
    //sprite.scale(scale_factor, scale_factor);

    if (dx != 0 || dy != 0 || start) {
        if (dx < 0) {
            sprite.setPosition(position.getX()+width_*scale_factor, position.getY());
            //sprite.setScale(-scale_factor,scale_factor);
            mirrored = 1;
            positionArme.setX(position.getX()+width_*scale_factor);
        }
        else if (dx == 0)  {
            sprite.setPosition(position.getX()+width_*scale_factor*mirrored, position.getY());
            positionArme.setX(position.getX()+width_*scale_factor);
        }
        else {
            sprite.setPosition(position.getX(), position.getY());
            //sprite.setScale(scale_factor,scale_factor);
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
            if (numPerso != 14) sprite.setScale(-scale_factor,scale_factor);
            else sprite.setScale(-scale_factor/4,scale_factor/4);
            mirrored = 1;
        }
        else if (dx == 0)  {
            sprite.setPosition(position.getX()+width_*scale_factor*mirrored, position.getY());
        }
        else {
            sprite.setPosition(position.getX(), position.getY());
            if (numPerso != 14) sprite.setScale(scale_factor,scale_factor);
            else sprite.setScale(scale_factor/4,scale_factor/4);
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

        if (numPerso != 14) {
            if (speedX > 0) sprite.setScale(scale_factor,scale_factor);
            else if (speedX < 0) sprite.setScale(-scale_factor,scale_factor);
        }
        else {
            if (speedX > 0) sprite.setScale(scale_factor/4,scale_factor/4);
            else if (speedX < 0) sprite.setScale(-scale_factor/4,scale_factor/4);
        }
    }

    mouvement(speedX,speedY);
}

// Prise en compte de la salle
void Ennemi::aleatoire_mvt(Salles s) {
    if (abs(objectif.getX() - position.getX()) < 30 && abs(objectif.getY() - position.getY()) < 30) {
        int maxX = static_cast<int>(width);
        int maxY = static_cast<int>(height);

        int w = width_*scale_factor;
        int h = height_*scale_factor;
        
        objectif = Point(0,0);
        while (!s.isIn(objectif) || !s.isIn(objectif + Point(w,0)) || !s.isIn(objectif + Point(0,h)) || !s.isIn(objectif + Point(w,h))) {
            objectif.setX(rand()%maxX);
            objectif.setY(rand()%maxY);
        }

        float tx = objectif.getX() - position.getX();
        float ty = objectif.getY() - position.getY();
        float tmax;
        if (abs(tx) > abs(ty)) tmax = abs(tx);
        else tmax = abs(ty);

        speedX = tx/tmax;
        speedY = ty/tmax;

        if (numPerso != 14) {
            if (speedX > 0) sprite.setScale(scale_factor,scale_factor);
            else if (speedX < 0) sprite.setScale(-scale_factor,scale_factor);
        }
        else {
            if (speedX > 0) sprite.setScale(scale_factor/4,scale_factor/4);
            else if (speedX < 0) sprite.setScale(-scale_factor/4,scale_factor/4);
        }
    }

    mouvement(speedX,speedY);
}

void Ennemi::aleatoire_mvt_2(const std::vector<Joueur*>& lJoueurs, Salles s) {
    //Point positionJoueur = detecteJoueur(lJoueurs, s);
    if ((abs(objectif.getX() - position.getX()) < 30 && abs(objectif.getY() - position.getY()) < 30) || detecteJoueur(lJoueurs, s) != Point(-1,-1)) {
        if (detecteJoueur(lJoueurs, s) != Point(-1,-1)) {
            objectif = detecteJoueur(lJoueurs, s);
            //std::cout << "Joueur vu (" << objectif.getX() << "," << objectif.getY() << ")" << std::endl;
            //std::cout << "Distance (" << abs(objectif.getX() - position.getX()) << "," << abs(objectif.getY() - position.getY()) << ")" << std::endl;
        }
        else {
            int j = (int) (position.getX()/48);
            int i = (int) (position.getY()/48);
            //std::cout << i << " " << j << std::endl;

            int l = static_cast<int>(s.voisins[i][j].size());
            int k = rand() % l;

            objectif.setX(s.voisins[i][j][k].getY()*48);
            objectif.setY(s.voisins[i][j][k].getX()*48);
        }
        //std::cout << "Objectif : " << objectif.getX() << " " << objectif.getY() << std::endl;

        float tx = objectif.getX() - position.getX();
        float ty = objectif.getY() - position.getY();
        float tmax;
        if (abs(tx) > abs(ty)) tmax = abs(tx);
        else tmax = abs(ty);

        if ((abs(objectif.getX() - position.getX()) > 30 || abs(objectif.getY() - position.getY()) > 30)) {
            speedX = tx/tmax;
            speedY = ty/tmax;    
        }
        else {
            speedX = 0;
            speedY = 0;
        }
        

        if (numPerso != 14) {
            if (speedX > 0) sprite.setScale(scale_factor,scale_factor);
            else if (speedX < 0) sprite.setScale(-scale_factor,scale_factor);
        }
        else {
            if (speedX > 0) sprite.setScale(scale_factor/4,scale_factor/4);
            else if (speedX < 0) sprite.setScale(-scale_factor/4,scale_factor/4);
        }
    }

    mouvement(speedX,speedY);
}

void Ennemi::suivi(Joueur& j) {
    objectif.setX(j.position.getX());
    objectif.setY(j.position.getY());

    float tx = objectif.getX() - position.getX();
    float ty = objectif.getY() - position.getY();
    float tmax;
    if (abs(tx) > abs(ty)) tmax = abs(tx);
    else tmax = abs(ty);

    speedX = tx/tmax;
    speedY = ty/tmax;

    if (numPerso != 14) {
        if (speedX > 0) sprite.setScale(scale_factor,scale_factor);
        else if (speedX < 0) sprite.setScale(-scale_factor,scale_factor);
    }
    else {
        if (speedX > 0) sprite.setScale(scale_factor/4,scale_factor/4);
        else if (speedX < 0) sprite.setScale(-scale_factor/4,scale_factor/4);
    } 
    
    mouvement(speedX,speedY);
}

Point Ennemi::detecteJoueur(const std::vector<Joueur*>& lJoueurs, Salles s) {
    Point obj(-1,-1);
    float distance = width;
    for (Joueur* j : lJoueurs) {
        if (j->estVivant) {
            int jx = j->position.getX() / 48;
            int jy = j->position.getY() / 48;
            int ex = position.getX() / 48;
            int ey = position.getY() / 48;
            for (Point p : s.voisins[ey][ex]) {
                if (p == Point(jy, jx) && distance >= sqrt(pow(p.getX() - ey,2) + pow(p.getY() - ex, 2))) {
                    obj = Point(p.getY()*48, p.getX()*48);
                    distance = sqrt(pow(obj.getX()/48 - ey,2) + pow(obj.getY()/48 - ex, 2));
                } 
            }
        }
    }
    return obj;
}

bool Ennemi::detecterEnnemi(const std::vector<std::shared_ptr<Joueur>>& joueurs, const Armes& arme){
    // // Calcul de la distance entre l'ennemi et le joueur
    // float distance = sqrt(pow((j.getX() - getX()), 2) + pow((j.getY() - getY()), 2));

    // // Si la distance est inférieure ou égale à la portée de détection
    // // alors on considère que l'ennemi a détecté le joueur
    // if (distance <= arme.porteeDetection) {
    //     return true;
    // } else {
    //     return false;
    // }

    // Vous devez vérifier chaque joueur individuellement.
    // Assumons que la position de l'ennemi est stockée dans cette classe Ennemi.
    float x = this->position.getX();
    float y = this->position.getY();

    float gauche = x - arme.porteeDetection;
    float droite = x + arme.porteeDetection;
    float haut = y + arme.hauteurDetection;
    float bas = y - arme.hauteurDetection;

    for (const auto& joueur : joueurs) {
        // Déréférencement correct du shared_ptr pour accéder à l'objet Joueur et ensuite à sa position.
        if (joueur) {  // Vérifiez toujours la validité du pointeur
            float jx = joueur->position.getX();
            float jy = joueur->position.getY();

            if (jx >= gauche && jx <= droite && jy <= haut && jy >= bas) {
                return true; // Le joueur est détecté dans le rectangle
            }
        }
    }
    return false; // Aucun joueur détecté dans le rectangle
}

void Ennemi::hitEnnemis(std::vector<Joueur*>& lJoueur) {
    if (etatHitRate > 1000/20/armes->rate_) {
        for (Joueur* j : lJoueur) {
            int d_attaque = (int) armes->distance_attaque_;

            int gauche = j->position.getX() - d_attaque;
            int haut = j->position.getY() - d_attaque;

            int droite = gauche + j->width_*j->scale_factor + 2*d_attaque;
            int bas = haut + j->height_*j->scale_factor + 2*d_attaque;

            int ex = position.getX(), ey = position.getY();

            if (ex >= gauche && ex <= droite && ey >= haut && ey <= bas) j->recevoirDegats(armes);
        }
        etatHitRate = 0;
    }
    etatHitRate++;
}

// bool Ennemi::detecterEnnemi(const std::vector<std::shared_ptr<Joueur>>& joueurs, const Armes& arme) {
//     // Vous devez vérifier chaque joueur individuellement.
//     // Assumons que la position de l'ennemi est stockée dans cette classe Ennemi.
//     float x = this->position.getX();
//     float y = this->position.getY();

//     float gauche = x - arme.porteeDetection;
//     float droite = x + arme.porteeDetection;
//     float haut = y + arme.hauteurDetection;
//     float bas = y - arme.hauteurDetection;

//     for (const auto& joueur : joueurs) {
//         // Déréférencement correct du shared_ptr pour accéder à l'objet Joueur et ensuite à sa position.
//         if (joueur) {  // Vérifiez toujours la validité du pointeur
//             float jx = joueur->position.getX();
//             float jy = joueur->position.getY();

//             if (jx >= gauche && jx <= droite && jy <= haut && jy >= bas) {
//                 return true; // Le joueur est détecté dans le rectangle
//             }
//         }
//     }
//     return false; // Aucun joueur détecté dans le rectangle
// }