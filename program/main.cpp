#include <SFML/Graphics.hpp>
#include <iostream>

#include "../class/Personnages/Joueurs.hpp"

using namespace sf;
using namespace std;

std::string reference  = "../0x72_DungeonTilesetII_v1.7/0x72_DungeonTilesetII_v1.7/frames/";
std::string idle = "_idle_anim_f";
std::string run = "_run_anim_f";
std::string fin_str = ".png";

std::string listeJoueurs[] = {"angel",
                            "big_demon",
                            "big_zombie",
                            "chort",
                            "doc",
                            "dwarf_f",
                            "dwarf_m",
                            "elf_f",
                            "elf_m",
                            "goblin",
                            "imp",
                            "knight_f",
                            "knight_m",
                            "lizard_f",
                            "lizard_m",
                            "masked_orc",
                            "ogre",
                            "orc_shaman",
                            "orc_warrior",
                            "pumpkin_dude",
                            "skelet",
                            "tiny_zombie",
                            "wizzard_f",
                            "wizzard_m",
                            "wogol"};       //25
// Par 4 (au lieu de 8) : zombie/slug/tiny_slug/ice_zombie/muddy/necromancer/swampy/

int main() {
    RenderWindow window(VideoMode(200,200), "Rungeon!");
    
    // Premier joueur
    Joueur j1(listeJoueurs[24], 20, 80);

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
        //cout << j1.etat << endl;
        
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