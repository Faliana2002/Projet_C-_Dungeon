#include "CorpsaCorps.hpp"
#include "../Personnages/Ennemi.hpp"

// Définition du constructeur
CorpsaCorps::CorpsaCorps(int indice, Salles s, int n) {
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

    int l;
    if (n == -1) {
        // Initialisation du générateur de nombres pseudo-aléatoires
        static std::mt19937 generator(static_cast<unsigned int>(std::time(nullptr)));

        // Création d'une distribution uniforme pour choisir un index de la liste des positions spawnables
        std::uniform_int_distribution<int> distribution(0, s.planSpawnable[s.planID].size() - 1);

        l = distribution(generator);
    }
    else {
        if (n >= (int) s.planSpawnable[s.planID].size()) n = s.planSpawnable[s.planID].size();
        l = n; 
    }
            
    int x = s.planSpawnable[s.planID][l].getX();
    int y = s.planSpawnable[s.planID][l].getY();

    // Positionnement de l'arme sur le monde du jeu
    position.setX(x);
    position.setY(y);

    sprite.setTexture(texture);
    sprite.setPosition(position.getX(), position.getY());

    // Redimensionner le sprite
    sprite.scale(scale_factor, scale_factor);
}

void CorpsaCorps::infligerDegats(std::vector<Ennemi*>& lEnnemis, std::vector<Joueur*>& lJoueur, const Armes& arme) const {
    std::cout << "Inflige " << degats_ << " points de dégâts à l'ennemi." << std::endl;

    bool ennemiDetecte = false;

    // Parcourir chaque ennemi pour voir s'il détecte un joueur
    for (const auto& joueur : lJoueur){
        for (const auto& ennemi : lEnnemis) {
            // if (joueur == joueur) {}
            // // Vérifiez que l'ennemi existe bien avant de tenter d'accéder à ses méthodes
            if (ennemi && ennemi->detecterEnnemi(lJoueur, arme)) {
                ennemiDetecte = true;

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

// Méthode attaque
void CorpsaCorps::attaque(std::vector<Ennemi*>& lEnnemis, std::vector<Joueur*>& lJoueur, const Armes& arme, std::vector<Projectile>& projectiles) const {
    infligerDegats(lEnnemis, lJoueur, arme);
}
