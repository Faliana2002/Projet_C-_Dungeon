#include "Joueurs.hpp"

void Joueur::mouvement(int dx, int dy) {
    position += Point(dx,dy);

    sprite.setPosition(position.getX(), position.getY());
}