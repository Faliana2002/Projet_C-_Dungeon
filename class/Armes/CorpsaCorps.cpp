#include "CorpsaCorps.hpp"
#include "../Personnages/Ennemi.hpp"

CorpsaCorps::CorpsaCorps(int indice) {
    indice_ = indice;

    int k = 100;

    int rate_min = static_cast<int>(std::get<1>(listeArmesCAC[indice])*k);
    int rate_max = static_cast<int>(std::get<2>(listeArmesCAC[indice])*k);
    rate_ = ((rand()%(rate_max-rate_min))+rate_min)/k;  // Fréquence d'utilisation de l'arme

    int degats_min = static_cast<int>(std::get<3>(listeArmesCAC[indice])*k);
    int degats_max = static_cast<int>(std::get<4>(listeArmesCAC[indice])*k);            
    degats_ = ((rand()%(degats_max-degats_min))+degats_min)/k;  // Determination des degats

    int range_min = static_cast<int>(std::get<5>(listeArmesCAC[indice])*k);
    int range_max = static_cast<int>(std::get<6>(listeArmesCAC[indice])*k);
    distance_attaque_ = ((rand()%(range_max-range_min))+range_min)/k;   

    // Set grande taille
    textureFile = reference + weapon_str + std::get<0>(listeArmesCAC[indice]) + fin_str;
    texture.loadFromFile(textureFile);

    // Positionnement de l'arme sur le monde du jeu
    position.setX(640);
    position.setY(360);

    sprite.setTexture(texture);
    sprite.setPosition(position.getX(), position.getY());

    // Redimensionner le sprite
    sprite.scale(scale_factor, scale_factor);
}

void CorpsaCorps::infligerDegats(const std::vector<std::shared_ptr<Joueur>>& joueurs, const std::vector<std::shared_ptr<Ennemi>>& listenn, const Armes& arme) const {
    std::cout << "Inflige " << degats_ << " points de dégâts à l'ennemi." << std::endl;

    bool ennemiDetecte = false;

    // Parcourir chaque ennemi pour voir s'il détecte un joueur
    for (const auto& joueur : joueurs){
        for (const auto& ennemi : listenn) {
            if (joueur == joueur) {}
            // Vérifiez que l'ennemi existe bien avant de tenter d'accéder à ses méthodes
            if (ennemi && ennemi->detecterEnnemi(joueurs, arme)) {
                ennemiDetecte = true;

                // Appliquer les dégâts à l'ennemi détecté
                //ennemi->recevoirDegats(&arme);  // Assurez-vous que recevoirDegats attend une référence à Armes

                // // Optionnel : Jouer une animation d'attaque
                // sprite.playAnimation("attaque");

                // Optionnel : Jouer un effet sonore
                // jouerSon("sonAttaque");

                // Un ennemi a été touché, donc sortie de la boucle
                break;
            }
        }
    }
    

    // Vérifier si aucun ennemi n'a été détecté et touché
    if (!ennemiDetecte) {
        std::cout << "Aucun ennemi à portée." << std::endl;
    }
}

// A modifier, sans specification de touche
void CorpsaCorps::attaque(const std::vector<std::shared_ptr<Joueur>>& joueurs, const std::vector<std::shared_ptr<Ennemi>>& listenn, const Armes& arme) const {
    infligerDegats(joueurs, listenn, arme);
}
