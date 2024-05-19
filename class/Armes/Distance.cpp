#include "Distance.hpp"

Distance::Distance(int indice, Salles s, int n) {
    indice_ = indice;

    int k = 100;

    int rate_min = static_cast<int>(std::get<1>(listeArmesDistance[indice])*k);
    int rate_max = static_cast<int>(std::get<2>(listeArmesDistance[indice])*k);
    rate_ = ((rand()%(rate_max-rate_min))+rate_min)/k;

    int degats_min = static_cast<int>(std::get<3>(listeArmesDistance[indice])*k);
    int degats_max = static_cast<int>(std::get<4>(listeArmesDistance[indice])*k);            
    degats_ = ((rand()%(degats_max-degats_min))+degats_min)/k;

    int range_min = static_cast<int>(std::get<5>(listeArmesDistance[indice])*k);
    int range_max = static_cast<int>(std::get<6>(listeArmesDistance[indice])*k);
    distance_attaque_ = ((rand()%(range_max-range_min))+range_min)/k;

    // Set grande taille
    textureFile = reference + weapon_str + std::get<0>(listeArmesDistance[indice]) + fin_str;
    texture.loadFromFile(textureFile);

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

    // Positionnement de l'arme sur le monde du jeu
    position.setX(x);
    position.setY(y);

    sprite.setTexture(texture);
    sprite.setPosition(position.getX(), position.getY());

    // Redimensionner le sprite
    sprite.scale(scale_factor, scale_factor);
}


// void Distance::attaque(std::vector<Ennemi*>& lEnnemis, std::vector<Joueur*>& lJoueur, const Armes& arme, Projectile& munition) const {
//     // Pour chaque ennemi dans la liste
//     for (Ennemi* ennemi : lEnnemis) {
//         Point pointDirect = munition.calculPoint_Ennemi(*ennemi->armes, *ennemi);
//         Vec2 directionProjectile = munition.calculDirection(pointDirect);

//         Vec2 directVersEnnemi = Vec2(ennemi->position.getX() - this->position.getX(), ennemi->position.getY() - this->position.getY()).normalize();

//         // Vérification si le projectile est bien dirigé vers l'ennemi
//         if (directionProjectile.x == directVersEnnemi.x && directionProjectile.y == directVersEnnemi.y) {
//             ennemi->recevoirDegats(ennemi->armes);
//         }
//     }

//     Joueur* joueurPrecedent = nullptr; // Pointeur vers le joueur précédent

//     for (Joueur* joueur : lJoueur) {
//         if (joueur != joueurPrecedent) { // Vérifie si le joueur actuel est différent du précédent
//             Point pointDirect = munition.calculPoint_Joueur(*joueur->armes, *joueur);
//             Vec2 directionProjectile = munition.calculDirection(pointDirect);

//             Vec2 directionVersJoueur = Vec2(joueur->position.getX() - this->position.getX(), joueur->position.getY() - this->position.getY()).normalize();

//             // Vérification si le projectile est bien dirigé vers ce joueur
//             if (directionProjectile.x == directionVersJoueur.x && directionProjectile.y == directionVersJoueur.y) {
//                 joueur->recevoirDegats(joueur->armes);
//             }
//         }
//         joueurPrecedent = joueur; // Mettre à jour le joueur précédent avec le joueur actuel
//     }
// }


// void Distance::attaque(std::vector<Ennemi*>& lEnnemis, std::vector<Joueur*>& lJoueur, const Armes& arme, Projectile& munition) const {
//     const float ANGLE_TOLERANCE = 0.1; // Tolérance en radians pour l'angle

//     // Pour chaque ennemi dans la liste
//     for (Ennemi* ennemi : lEnnemis) {
//         Point pointDirect = munition.calculPoint_Ennemi(*ennemi->armes, *ennemi);
//         Vec2 directionProjectile = munition.calculDirection(pointDirect);

//         Vec2 directVersEnnemi = Vec2(ennemi->position.getX() - this->position.getX(), ennemi->position.getY() - this->position.getY()).normalize();

//         // Calcul de l'angle entre les deux vecteurs
//         float dotProduct = directionProjectile.x * directVersEnnemi.x + directionProjectile.y * directVersEnnemi.y;
//         float magnitudes = sqrt(directionProjectile.x * directionProjectile.x + directionProjectile.y * directionProjectile.y) *
//                            sqrt(directVersEnnemi.x * directVersEnnemi.x + directVersEnnemi.y * directVersEnnemi.y);
//         float angle = acos(dotProduct / magnitudes); // angle en radians

//         // Vérification si le projectile est suffisamment bien dirigé vers l'ennemi
//         if (fabs(angle) < ANGLE_TOLERANCE) {
//             ennemi->recevoirDegats(ennemi->armes);
//         }
//     }

//     Joueur* joueurPrecedent = nullptr; // Pointeur vers le joueur précédent

//     for (Joueur* joueur : lJoueur) {
//         if (joueur != joueurPrecedent) { // Vérifie si le joueur actuel est différent du précédent
//             Point pointDirect = munition.calculPoint_Joueur(*joueur->armes, *joueur);
//             Vec2 directionProjectile = munition.calculDirection(pointDirect);

//             Vec2 directionVersJoueur = Vec2(joueur->position.getX() - this->position.getX(), joueur->position.getY() - this->position.getY()).normalize();

//             // Calcul de l'angle entre les deux vecteurs
//             float dotProduct = directionProjectile.x * directionVersJoueur.x + directionProjectile.y * directionVersJoueur.y;
//             float magnitudes = sqrt(directionProjectile.x * directionProjectile.x + directionProjectile.y * directionProjectile.y) *
//                          sqrt(directionVersJoueur.x * directionVersJoueur.x + directionVersJoueur.y * directionVersJoueur.y);
//             float angle = acos(dotProduct / magnitudes); // angle en radians

//             // Vérification si le projectile est suffisamment bien dirigé vers ce joueur
//             if (fabs(angle) < ANGLE_TOLERANCE) {
//                 joueur->recevoirDegats(joueur->armes);
//             }
//         }
//         joueurPrecedent = joueur; // Mettre à jour le joueur précédent avec le joueur actuel
//     }
// }

void Distance::attaque(std::vector<Ennemi*>& lEnnemis, std::vector<Joueur*>& lJoueur, const Armes& arme, std::vector<Projectile>& projectiles) const {
    // Lancer un projectile vers chaque ennemi
    for (auto& ennemi : lEnnemis) {
        Vec2 directionVersEnnemi = Vec2(ennemi->position.getX() - this->position.getX(), ennemi->position.getY() - this->position.getY()).normalize();
        projectiles.emplace_back(this->position, directionVersEnnemi * arme.getSpeed(), &arme);
    }

    // Lancer un projectile vers chaque joueur
    for (auto& joueur : lJoueur) {
        Vec2 directionVersJoueur = Vec2(joueur->position.getX() - this->position.getX(), joueur->position.getY() - this->position.getY()).normalize();
        projectiles.emplace_back(this->position, directionVersJoueur * arme.getSpeed(), &arme);
    }
}