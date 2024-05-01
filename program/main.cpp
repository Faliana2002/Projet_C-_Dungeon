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

int main() {
    RenderWindow window(VideoMode(width,height), "Rungeon!");
    
    // Premier joueur
    Joueur j1(listeJoueurs[4], 20, 80);
    Joueur j2(listeJoueurs[18], 400, 300);


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

    void entryManager(Event event, RenderWindow& window, Joueur& j1, Joueur& j2);

    // Main loop
    while (window.isOpen()) {

        // Handle events
        Event event;
        while (window.pollEvent(event)) {
            entryManager(event, window, j1, j2);
        }
        
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

        // Draw the sprite
        window.draw(j1.sprite);
        window.draw(j2.sprite);

        // Display the contents of the window
        window.display();
    }

    return EXIT_SUCCESS;
}

void entryManager(Event event, RenderWindow& window, Joueur& j1, Joueur& j2) {
    if (event.type == Event::Closed) {
        window.close();
    }
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
}