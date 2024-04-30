#include <SFML/Graphics.hpp>
#include <iostream>

#include "../class/Personnages/Joueurs.hpp"
#include "../class/declaration.hpp"

using namespace sf;
using namespace std;

extern std::string reference;
extern std::string idle;
extern std::string run;
extern std::string fin_str;

extern std::string listeJoueurs[];

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