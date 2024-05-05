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

    position.setX(1180);
    position.setY(620);

    sprite.setTexture(texture);
    sprite.setPosition(position.getX(), position.getY());

    // Redimensionner le sprite
    sprite.scale(scale_factor, scale_factor);
}        