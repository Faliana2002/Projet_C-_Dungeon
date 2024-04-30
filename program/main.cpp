#include <SFML/Graphics.hpp>
#include <iostream>
#include <chrono>

#include "../class/Personnages/Joueurs.hpp"
#include "../class/declaration.hpp"

using namespace sf;
using namespace std;

extern std::string reference;
extern std::string idle;
extern std::string run;
extern std::string fin_str;
extern std::string listeJoueurs[];
extern int width;
extern int height;

int main() {
    RenderWindow window(VideoMode(width,height), "Rungeon!");
    
    // Premier joueur
    Joueur j1(listeJoueurs[4], 20, 80);
    Joueur j2(listeJoueurs[18], 400, 300);
    Joueur j3(listeJoueurs[23], 250, 500);
    Joueur j4(listeJoueurs[17], 800, 600);

    // Load a texture from a PNG file
    Texture texture;
    if (!texture.loadFromFile("../assets/players/img_64.png")) {
        return EXIT_FAILURE;
    }

    // Gestion du frame rate
    auto now = std::chrono::system_clock::now();
    auto duration = now.time_since_epoch();
    long startTime = std::chrono::duration_cast<std::chrono::milliseconds>(duration).count();
    long currentTime;

    // Main loop
    while (window.isOpen()) {
        
        // Gestion du frame rate
        auto now = std::chrono::system_clock::now();
        auto duration = now.time_since_epoch();
        currentTime = std::chrono::duration_cast<std::chrono::milliseconds>(duration).count();
        
        if (currentTime - startTime > 10) { // frame rate 100 Hz (10 ms)
            j1.debug_mvt();
            j2.debug_mvt();
            j3.debug_mvt();
            j4.debug_mvt();

            startTime = currentTime;
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
        window.draw(j2.sprite);
        window.draw(j3.sprite);
        window.draw(j4.sprite);

        // Display the contents of the window
        window.display();
    }

    return EXIT_SUCCESS;
}