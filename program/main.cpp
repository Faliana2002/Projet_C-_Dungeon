#include <SFML/Graphics.hpp>
#include <iostream>
#include <chrono>

#include "../class/Personnages/Joueurs.hpp"
#include "../class/declaration.hpp"
//#include "../class/Gestion.hpp"

using namespace sf;
using namespace std;

extern std::string reference;
extern std::string idle;
extern std::string run;
extern std::string fin_str;
extern std::string listeJoueurs[];
extern int width;
extern int height;

void startManager(Event event, RenderWindow& window, Joueur& j1, Joueur& j2);
void entryManager(Event event, RenderWindow& window, Joueur& j1, Joueur& j2);

int main() {
    RenderWindow window(VideoMode(width,height), "Rungeon!");
    
    // Premier joueur
    Joueur j1(4, 960-16*4/2, 360-28*4/2);
    Joueur j2(18, 320-16*4/2, 360-28*4/2);

    // Background texture
    Texture backgroundTexture;
    if (!backgroundTexture.loadFromFile(reference + "page_acceuil.png")) {
        // Gérer l'échec du chargement de l'image
        std::cerr << "Impossible de charger l'image en arrière-plan !" << std::endl;
        return EXIT_FAILURE;
    }
    Sprite backgroundSprite(backgroundTexture);

    // Gestion du jeu
    //Gestion game(j1, j2);

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
                    startManager(event, window, j1, j2);
                    break;                
                case 1:
                    entryManager(event, window, j1, j2);
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

void entryManager(Event event, RenderWindow& window, Joueur& j1, Joueur& j2) {
    if (event.type == sf::Event::KeyPressed) {
        if (event.key.code == sf::Keyboard::Up)
            // Gérer l'appui sur la touche Haut
            j1.speedY = -2;
        else if (event.key.code == sf::Keyboard::Down)
            // Gérer l'appui sur la touche Bas
            j1.speedY = 2;
        if (event.key.code == sf::Keyboard::Left)
            // Gérer l'appui sur la touche Gauche
            j1.speedX = -2;
        else if (event.key.code == sf::Keyboard::Right)
            // Gérer l'appui sur la touche Droite
            j1.speedX = 2;
        if (event.key.code == sf::Keyboard::Z)
            // Gérer l'appui sur la touche Haut
            j2.speedY = -2;
        else if (event.key.code == sf::Keyboard::S)
            // Gérer l'appui sur la touche Bas
            j2.speedY = 2;
        if (event.key.code == sf::Keyboard::Q)
            // Gérer l'appui sur la touche Gauche
            j2.speedX = -2;
        else if (event.key.code == sf::Keyboard::D)
            // Gérer l'appui sur la touche Droite
            j2.speedX = 2;
    }
    else if (event.type == sf::Event::KeyReleased) {
        // Réinitialisation des vitesses lorsque les touches sont relâchées
        if (event.key.code == sf::Keyboard::Up || event.key.code == sf::Keyboard::Down)
            j1.speedY = 0;
        if (event.key.code == sf::Keyboard::Left || event.key.code == sf::Keyboard::Right)
            j1.speedX = 0;
        if (event.key.code == sf::Keyboard::Z || event.key.code == sf::Keyboard::S)
            j2.speedY = 0;
        if (event.key.code == sf::Keyboard::Q || event.key.code == sf::Keyboard::D)
            j2.speedX = 0;
    }

    if (event.key.code == sf::Keyboard::U) {
            // Gérer l'appui sur la touche Gauche
            j1.rtp = 0;
            j2.rtp = 0;
            j1.position = Point(960-16*4/2, 360-28*4/2);
            j2.position = Point(320-16*4/2, 360-28*4/2);
    }
}

void startManager(Event event, RenderWindow& window, Joueur& j1, Joueur& j2) {
    if (event.type == sf::Event::KeyPressed) {
        if (event.key.code == sf::Keyboard::Up || event.key.code == sf::Keyboard::Down)
            // Gérer l'appui sur la touche Gauche
            j1.rtp = 1;
        if (event.key.code == sf::Keyboard::Left)
            // Gérer l'appui sur la touche Gauche
            j1.numPerso--;
        else if (event.key.code == sf::Keyboard::Right)
            // Gérer l'appui sur la touche Droite
            j1.numPerso++;
        if (event.key.code == sf::Keyboard::Z || event.key.code == sf::Keyboard::S)
            // Gérer l'appui sur la touche Gauche
            j2.rtp = 1;
        if (event.key.code == sf::Keyboard::Q)
            // Gérer l'appui sur la touche Gauche
            j2.numPerso--;
        else if (event.key.code == sf::Keyboard::D)
            // Gérer l'appui sur la touche Droite
            j2.numPerso++;
    } 
    if (j1.numPerso < 0) j1.numPerso++;
    if (j1.numPerso > 24) j1.numPerso--;
    if (j2.numPerso < 0) j2.numPerso++;
    if (j2.numPerso > 24) j2.numPerso--;

}