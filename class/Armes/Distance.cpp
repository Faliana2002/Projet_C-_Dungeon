#include "Distance.hpp"

Distance::Distance(int indice) {
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

    position.setX(500); //640
    position.setY(360);

    sprite.setTexture(texture);
    sprite.setPosition(position.getX(), position.getY());

    // Redimensionner le sprite
    sprite.scale(scale_factor, scale_factor);
}


void Distance::attaque(std::vector<Ennemi*>& lEnnemis, std::vector<Joueur*>& lJoueur, const Armes& arme, Projectile& munition) const {
    // Pour chaque ennemi dans la liste
    for (Ennemi* ennemi : lEnnemis) {
        Point pointDirect = munition.calculPoint_Ennemi(*ennemi->armes, *ennemi);
        Vec2 directionProjectile = munition.calculDirection(pointDirect);

        Vec2 directVersEnnemi = Vec2(ennemi->position.getX() - this->position.getX(), ennemi->position.getY() - this->position.getY()).normalize();

        // Vérification si le projectile est bien dirigé vers l'ennemi
        if (directionProjectile.x == directVersEnnemi.x && directionProjectile.y == directVersEnnemi.y) {
            ennemi->recevoirDegats(ennemi->armes);
        }
    }

    Joueur* joueurPrecedent = nullptr; // Pointeur vers le joueur précédent

    for (Joueur* joueur : lJoueur) {
        if (joueur != joueurPrecedent) { // Vérifie si le joueur actuel est différent du précédent
            Point pointDirect = munition.calculPoint_Joueur(*joueur->armes, *joueur);
            Vec2 directionProjectile = munition.calculDirection(pointDirect);

            Vec2 directionVersJoueur = Vec2(joueur->position.getX() - this->position.getX(), joueur->position.getY() - this->position.getY()).normalize();

            // Vérification si le projectile est bien dirigé vers ce joueur
            if (directionProjectile.x == directionVersJoueur.x && directionProjectile.y == directionVersJoueur.y) {
                joueur->recevoirDegats(joueur->armes);
            }
        }
        joueurPrecedent = joueur; // Mettre à jour le joueur précédent avec le joueur actuel
    }
}

void Distance::simulateKeyPress(std::vector<Joueur*>& lJoueurs, std::vector<Ennemi*>& lEnnemis, Projectile& munition) {
    for (size_t i = 0; i < lJoueurs.size(); ++i) {
        if (lJoueurs[i]->armes != nullptr && lJoueurs[i]->armes->getIndice() == 0) {
            this->attaque(lEnnemis, lJoueurs, *lJoueurs[i]->armes, munition);
        }
    }
}