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

    position.setX(640);
    position.setY(360);

    sprite.setTexture(texture);
    sprite.setPosition(position.getX(), position.getY());

    // Redimensionner le sprite
    sprite.scale(scale_factor, scale_factor);
}

// // Méthode pour calculer la distance entre deux points
// float distanceEntreDeuxPoints(const Point& point1, const Point& point2) const{
//     float dx = point2.x - point1.x;
//     float dy = point2.y - point1.y;
//     return std::sqrt(dx * dx + dy * dy); // Utilisation de la formule de distance euclidienne
// }


// bool estDansZoneDetection(const Point& ennemiPosition, const Point& armePosition, float porteeDetection) const{
//     // Calculer la distance entre l'ennemi et l'arme
//     float distance = distanceEntreDeuxPoints(ennemiPosition, armePosition);

//     // Vérifier si la distance est inférieure ou égale à la portée de détection de l'arme
//     return distance <= porteeDetection;
// }

// void Distance::infligerDegats(const std::vector<std::shared_ptr<Joueur>>& joueurs, const std::vector<std::shared_ptr<Ennemi>>& listenn, const Armes& arme) const {
//     std::cout << "Inflige " << degats_ << " points de dégâts à l'ennemi." << std::endl;

//     bool ennemiDetecte = false;

//     // Parcourir chaque ennemi
//     for (const auto& ennemi : listenn) {
//         // Vérifier si l'ennemi est dans la zone de détection de l'arme
//         // Vous devez implémenter la logique pour vérifier si l'ennemi est dans la zone de détection de l'arme
//         if (estDansZoneDetection(ennemi->getPosition(), arme.position, arme.porteeDetection)) {
//             ennemiDetecte = true;

//             // Déterminez la probabilité de toucher l'ennemi
//             float probabiliteToucher = calculerProbabiliteToucher(ennemi->getPosition(), arme.position, arme.precision);

//             // Générez un nombre aléatoire pour déterminer si le tir touche ou non
//             float random = static_cast<float>(rand()) / static_cast<float>(RAND_MAX);
            
//             // Si le nombre aléatoire est inférieur à la probabilité de toucher, infligez des dégâts
//             if (random < probabiliteToucher) {
//                 ennemi->recevoirDegats(*this);
//             } else {
//                 std::cout << "L'attaque a raté." << std::endl;
//             }

//             // Sortez de la boucle une fois que l'ennemi a été touché ou que l'attaque a raté
//             break;
//         }
//     }

//     // Si aucun ennemi n'a été détecté
//     if (!ennemiDetecte) {
//         std::cout << "Aucun ennemi à portée." << std::endl;
//     }
// }

// // A modifier, sans specification de touche
// void Distance::attaque(const std::vector<std::shared_ptr<Joueur>>& joueurs, const std::vector<std::shared_ptr<Ennemi>>& listenn, const Armes& arme) const {
//     infligerDegats(joueurs, listenn, arme);
// }