#include "Ennemi.hpp"

// Initialisation sur les zones définies
Ennemi::Ennemi(int textureFileInt, Salles s, int n) {
    auto now = std::chrono::system_clock::now();
    auto duration = now.time_since_epoch();
    startTimeHR = std::chrono::duration_cast<std::chrono::milliseconds>(duration).count();

    vieMax = 16;
    vie = vieMax;
    int l;
    if (n == -1) {
        // Initialisation du générateur de nombres pseudo-aléatoires
        static std::mt19937 generator(static_cast<unsigned int>(std::time(nullptr)));

        // Création d'une distribution uniforme pour choisir un index de la liste des positions spawnables
        std::uniform_int_distribution<int> distribution(0, s.spawnable.size() - 1);

        l = distribution(generator);
    }
    else {
        if (n >= (int) s.spawnable.size()) n = s.spawnable.size();
        l = n; 
    }
            
    int x = s.spawnable[l].getX();
    int y = s.spawnable[l].getY();
    
    numPerso = textureFileInt;
    // Set grande taille
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
}

// Initialisation sur un point donné
Ennemi::Ennemi(int textureFileInt, float x, float y) {
    vieMax = 16;
    vie = vieMax;
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
    //std::cout << "Dans mouvement dx dy" << std::endl;
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

void Ennemi::mouvement(float dx, float dy, Salles s) {
    //std::cout << "Dans mouvement dx dy" << std::endl;
    //position += Point(dx,dy);

    int w = width_*scale_factor;
    int h = height_*scale_factor;
    
    if (s.isIn(position+Point(dx,0)) && s.isIn(position+Point(dx+w,0)) && s.isIn(position+Point(dx+w,0+h)) && s.isIn(position+Point(dx,0+h))) {
        position += Point(dx,0);
    }
    if (s.isIn(position+Point(0,dy)) && s.isIn(position+Point(0+w,dy)) && s.isIn(position+Point(0+w,dy+h)) && s.isIn(position+Point(0,dy+h))) {
        position += Point(0,dy);
    }

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

/*
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
*/

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

/*
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
*/

/*
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
*/

// Prise en compte de la salle et de la présence des joueurs
void Ennemi::aleatoire_mvt_2(const std::vector<Joueur*>& lJoueurs, Salles s) {
    //std::cout << "Dans alea mvt 2" << std::endl;

    //Point positionJoueur = detecteJoueur(lJoueurs, s);
    if ((abs(objectif.getX() - position.getX()) < 30 && abs(objectif.getY() - position.getY()) < 30) || detecteJoueur(lJoueurs, s) != Point(-1,-1)) {
        //std::cout << "Change d'objectif" << std::endl;
        if (detecteJoueur(lJoueurs, s) != Point(-1,-1)) {
            //std::cout << "Vers le joueur" << std::endl;
            objectif = detecteJoueur(lJoueurs, s);
            objectif.setX(objectif.getX() - width_/2);
            objectif.setY(objectif.getY() - height_/2);

            //std::cout << "Joueur vu (" << objectif.getX() << "," << objectif.getY() << ")" << std::endl;
            //std::cout << "Distance (" << abs(objectif.getX() - position.getX()) << "," << abs(objectif.getY() - position.getY()) << ")" << std::endl;
        }
        else {
            //std::cout << "Vers un point" << std::endl;
            int j = (int) (position.getX()/48);
            int i = (int) (position.getY()/48);
            //std::cout << i << " " << j << std::endl;

            int l = static_cast<int>(s.voisins[i][j].size());
            //std::cout << "nombre de points accessible : " << l << std::endl;
            std::map<Point, int> listeChoix;
            for (int dx = 0; dx <= 1; dx++) {
                for (int dy = 0; dy <= 1; dy++) {
                    for (Point p : s.voisins[i+dx][j+dy]) {
                        listeChoix[p]++;
                    }
                }
            }/*
            for (int x = 0; x < 720/48; x++) {
                for (int y = 0; y < 1280/48; y++) {
                    if (x == i && y == j) std::cout << "8 ";
                    else std::cout << listeChoix[Point(x,y)] << " ";
                }
                std::cout << std::endl;
            }
            std::cout << std::endl;*/
            if (l > 0) {
                bool test_choose = false;
                while (!test_choose) {
                    int k = rand() % l;
                    if (listeChoix[s.voisins[i][j][k]] == 4) test_choose = true;
                    objectif.setX(s.voisins[i][j][k].getY()*48);
                    objectif.setY(s.voisins[i][j][k].getX()*48);
                }
                
            }
            
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
    bool test = true;
    for (int dx = 0; dx <= 48; dx += 48) {
        for (int dy = 0; dy <= 48; dy += 48) {
            if (!s.isIn(Point(position.getX() + speedX + dx, position.getY() + speedY + dy))) test = false;
        }
    }

    if (test) mouvement(speedX,speedY, s);
    else {
        std::cout << "l'enemi est bloqué l'enemi est bloqué l'enemi est bloqué l'enemi est bloqué" << std::endl;
        objectif = position;
    }
}

// Suivi d'un joueur donné
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
    float distance = 5;
    for (Joueur* j : lJoueurs) {
        if (j->estVivant) {
            int jx = (j->position.getX()+24) / 48;
            int jy = (j->position.getY()+24) / 48;
            int ex = (position.getX()+24) / 48;
            int ey = (position.getY()+24) / 48;
            for (Point p : s.voisins[ey][ex]) {
                if (p == Point(jy, jx) && sqrt(pow(jy - ey,2) + pow(jx - ex, 2)) <= distance) {
                    obj = Point(p.getY()*48, p.getX()*48);
                    distance = sqrt(pow(jy - ey,2) + pow(jx - ex, 2));
                } 
            }
        }
    }
    return obj;
}

bool Ennemi::detecterEnnemi(std::vector<Joueur*>& lJoueur, const Armes& arme){
    // Vous devez vérifier chaque joueur individuellement.
    // Assumons que la position de l'ennemi est stockée dans cette classe Ennemi.
    float x = this->position.getX();
    float y = this->position.getY();

    float gauche = x - arme.porteeDetection;
    float droite = x + arme.porteeDetection;
    float haut = y + arme.hauteurDetection;
    float bas = y - arme.hauteurDetection;

    for (const auto& joueur : lJoueur) {
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
    auto now = std::chrono::system_clock::now();
    auto duration = now.time_since_epoch();
    currentTimeHR = std::chrono::duration_cast<std::chrono::milliseconds>(duration).count();
    if (currentTimeHR - startTimeHR > 1000/armes->getRate()) {
        startTimeHR = currentTimeHR;
        
        for (Joueur* j : lJoueur) {
            int d_attaque = (int) armes->distance_attaque_;

            int gauche = j->position.getX() - d_attaque;
            int haut = j->position.getY() - d_attaque;

            int droite = gauche + j->width_*j->scale_factor + 2*d_attaque;
            int bas = haut + j->height_*j->scale_factor + 2*d_attaque;

            int ex = position.getX(), ey = position.getY();

            if (ex >= gauche && ex <= droite && ey >= haut && ey <= bas) j->recevoirDegats(armes);
        }
    }
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