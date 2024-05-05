#include "CorpsaCorps.hpp"

CorpsaCorps::CorpsaCorps(int indice) {
    indice_ = indice;

    int k = 100;

    int rate_min = static_cast<int>(std::get<1>(listeArmesCAC[indice])*k);
    int rate_max = static_cast<int>(std::get<2>(listeArmesCAC[indice])*k);
    rate_ = ((rand()%(rate_max-rate_min))+rate_min)/k;

    int degats_min = static_cast<int>(std::get<3>(listeArmesCAC[indice])*k);
    int degats_max = static_cast<int>(std::get<4>(listeArmesCAC[indice])*k);            
    degats_ = ((rand()%(degats_max-degats_min))+degats_min)/k;

    int range_min = static_cast<int>(std::get<5>(listeArmesCAC[indice])*k);
    int range_max = static_cast<int>(std::get<6>(listeArmesCAC[indice])*k);
    distance_attaque_ = ((rand()%(range_max-range_min))+range_min)/k;

    // Set grande taille
    textureFile = reference + weapon_str + std::get<0>(listeArmesCAC[indice]) + fin_str;
    texture.loadFromFile(textureFile);

    position.setX(100);
    position.setY(620);

    sprite.setTexture(texture);
    sprite.setPosition(position.getX(), position.getY());

    // Redimensionner le sprite
    sprite.scale(scale_factor, scale_factor);
}        