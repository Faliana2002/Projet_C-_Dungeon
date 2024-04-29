#include <SFML/Graphics.hpp>
#include <iostream>

#include "../class/Personnages/Joueurs.hpp"

using namespace sf;
using namespace std;

std::string reference  = "../0x72_DungeonTilesetII_v1.7/0x72_DungeonTilesetII_v1.7/frames/";

int main() {
    RenderWindow window(VideoMode(200,200), "SFML works!");
    
    // Premier joueur
    Joueur j1("elf_f_hit_anim_f0.png", 20, 80);

    // Load a texture from a PNG file
    Texture texture;
    if (!texture.loadFromFile("../assets/players/img_64.png")) {
        return EXIT_FAILURE;
    }

    int k = 0;
    int speedX = 1;
    int speedY = 1;

    // Main loop
    while (window.isOpen()) {

        k++;
        if (k == 250) {
            j1.mouvement(speedX,speedY);
            k = 0;
        }

        if (j1.position.getX() + speedX + 16 > 200 || j1.position.getX() + speedX < 0) {
            speedX *= -1;
        }

        if (j1.position.getY() + speedY + 28 > 200 || j1.position.getY() + speedY < 0) {
            speedY *= -1;
        }

        // Handle events
        Event event;
        while (window.pollEvent(event)) {
            if (event.type == Event::Closed) {
                window.close();
            }
        }

        // Clear the window
        window.clear();

        // Draw the sprite
        window.draw(j1.sprite);

        // Display the contents of the window
        window.display();
    }

    return EXIT_SUCCESS;
}