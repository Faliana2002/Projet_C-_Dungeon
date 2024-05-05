#include "CorpsaCorps.hpp"
#include "Ennemi.hpp"
#include "Armes.hpp"
#include <SFML/Window.hpp> // Nécessaire pour gérer les entrées clavier avec SFML
#include <iostream> // Pour l'affichage dans la console

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
    position.setX(100);
    position.setY(620);

    sprite.setTexture(texture);
    sprite.setPosition(position.getX(), position.getY());

    // Redimensionner le sprite
    sprite.scale(scale_factor, scale_factor);
}

void CorpsaCorps::infligerDegats() const {
    // Affichage des dégâts infligés
    std::cout << "Inflige " << degats_ << " points de dégâts à l'ennemi." << std::endl;

    // Détecter si un ennemi est à portée
    bool ennemiDetecte = false;
    for (const auto& ennemi : listeEnnemis) {
        if (ennemi.detecterEnnemi(joueur)) {
            ennemiDetecte = true;
            // Appliquer les dégâts à l'ennemi
            ennemi.recevoirDegats(degats_);

            // Optionnel : Jouer une animation d'attaque
            sprite.playAnimation("attaque");

            // Optionnel : Jouer un effet sonore
            // jouerSon("sonAttaque");

            // Sortir de la boucle car un ennemi a été touché
            break;
        }
    }

    // Vérifier si aucun ennemi n'a été détecté
    if (!ennemiDetecte) {
        std::cout << "Aucun ennemi à portée." << std::endl;
    }
}


void CorpsaCorps::ramasserArme(const Armes& arme) const {
    std::cout << "Arme ramassée." << std::endl;
    // Implémenter la logique pour ajouter l'arme à l'inventaire du joueur ou changer son état dans le jeu.
    if (arme_a_ramasser != nullptr) {
        joueur->ajouterArmeInventaire(*arme_a_ramasser);
    } else {
        std::cerr << "Erreur : Aucune arme à ramasser." << std::endl;
    }
}

void CorpsaCorps::attaque() const {
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
        // Lorsque la touche 'Haut' est pressée, l'arme inflige des dégâts
        infligerDegats();
    } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
        // Lorsque la touche 'Bas' est pressée, le joueur peut ramasser l'arme
        ramasserArme();
    }
}
