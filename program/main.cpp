#include <SFML/Graphics.hpp>
#include <iostream>
#include <chrono>

#include "../class/Personnages/Joueurs.hpp"
#include "../class/declaration.hpp"
#include "../class/Gestion.hpp"
//#include "../class/Gestion.hpp"

using namespace sf;
using namespace std;

extern std::string reference;
extern std::string idle;
extern std::string run;
extern std::string fin_str;
extern std::string listeJoueurs[];
extern std::string listeEnnemi[];
extern int width;
extern int height;

void startManager(Event event, RenderWindow& window, Joueur& j1, Joueur& j2);
void entryManager(Event event, RenderWindow& window, Joueur& j1, Joueur& j2);

int main() {
    RenderWindow window(VideoMode(width,height), "Rungeon!");
    
    // Premier joueur
    Joueur j1(2, 960-16*4/2, 360-28*4/2);
    Joueur j2(2, 320-16*4/2, 360-28*4/2);

    // Background texture
    Texture backgroundTexture;
    if (!backgroundTexture.loadFromFile(reference + "page_acceuil.png")) {
        // Gérer l'échec du chargement de l'image
        std::cerr << "Impossible de charger l'image en arrière-plan !" << std::endl;
        return EXIT_FAILURE;
    }
    Sprite backgroundSprite(backgroundTexture);

    // Gestion du jeu
    Gestion game;

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

    int etatJeu = 0;

    // Main loop
    while (window.isOpen()) {

        // Handle events
        Event event;
        while (window.pollEvent(event)) {
            if (event.type == Event::Closed || event.key.code == sf::Keyboard::Space) {
                window.close();
            }
            switch (etatJeu) {
                case 0:
                    game.startManager(event, window, j1, j2);   // Page choix personnages
                    break;                
                case 1:
                    game.entryManager(event, window, j1, j2);   // Page de jeu
                    break;
                default:
                    break;
            }
        }

        if (j1.rtp > 0 && j2.rtp > 0) etatJeu = 1;
        else etatJeu = 0;
        
        // Gestion du frame rate
        auto now = std::chrono::system_clock::now();
        auto duration = now.time_since_epoch();
        currentTime = std::chrono::duration_cast<std::chrono::milliseconds>(duration).count();
        
        if (currentTime - startTime > 20) { // frame rate 100 Hz (10 ms)
            //j1.debug_mvt();
            //j2.debug_mvt();
            j1.mouvement();
            j2.mouvement();

            startTime = currentTime;
        }

        // Clear the window
        window.clear();

        // Draw background
        if (etatJeu == 0) {
            window.draw(backgroundSprite);
        }

        // Draw the sprite
        window.draw(j1.sprite);
        window.draw(j2.sprite);

        // Display the contents of the window
        window.display();
    }

    return EXIT_SUCCESS;
}