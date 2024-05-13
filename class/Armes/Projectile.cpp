#include "Projectile.hpp"
Projectile::Projectile(int indice, Vec2 direction) {
    indice_ = indice;

    int k = 100;

    // Extraction des valeurs du tuple pour la configuration initiale
    float rate_min = std::get<1>(listeArmesDistance[indice]) * k;
    float rate_max = std::get<2>(listeArmesDistance[indice]) * k;
    rate_ = static_cast<float>((rand() % static_cast<int>(rate_max - rate_min)) + rate_min) / k;

    float degats_min = std::get<3>(listeArmesDistance[indice]) * k;
    float degats_max = std::get<4>(listeArmesDistance[indice]) * k;
    degats_ = static_cast<float>((rand() % static_cast<int>(degats_max - degats_min)) + degats_min) / k;

    float range_min = std::get<5>(listeArmesDistance[indice]) * k;
    float range_max = std::get<6>(listeArmesDistance[indice]) * k;
    distance_attaque_ = static_cast<float>((rand() % static_cast<int>(range_max - range_min)) + range_min) / k;

    textureFile = arrowFile;
    texture.loadFromFile(textureFile);
    sprite.setTexture(texture);
    sprite.setPosition(position.getX(), position.getY());
    position.setX(640);
    position.setY(360);

    // Direction du projectile
    direction.normalize();
    velocity = direction * rate_;

    // Mise à l'échelle du sprite
    float scale_factor = 0.5; // Facteur d'échelle ajustable
    sprite.scale(scale_factor, scale_factor);
}