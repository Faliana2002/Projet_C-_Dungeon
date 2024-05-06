#include <SFML/Graphics.hpp>
#include <iostream>
#include <chrono>

#include "../class/Personnages/Joueurs.hpp"
#include "../class/Personnages/Ennemi.hpp"
#include "../class/declaration.hpp"
#include "../class/Gestion.hpp"
#include "../class/Armes/CorpsaCorps.hpp"
#include "../class/Armes/Distance.hpp"

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

//void startManager(Event event, RenderWindow& window, Joueur& j1, Joueur& j2);
//void entryManager(Event event, RenderWindow& window, Joueur& j1, Joueur& j2);

int main() {
    RenderWindow window(VideoMode(width,height), "Rungeon!");
    
    // Premier joueur
    Joueur j1(2, 960-16*4/2, 360-28*4/2);
    Joueur j2(1, 320-16*4/2, 360-28*4/2);

    std::vector<Joueur> lJoueurs;
    lJoueurs.push_back(j1);
    lJoueurs.push_back(j2);

    Ennemi e1(1, 600,300);
    Ennemi e2(2,1278, 56);
    Ennemi e3(3,1074, 449);
    Ennemi e4(4,612, 273);
    Ennemi e5(5,532, 145);

    std::vector<Ennemi> lEnnemis;
    lEnnemis.push_back(e1);
    lEnnemis.push_back(e2);
    lEnnemis.push_back(e3);
    lEnnemis.push_back(e4);
    lEnnemis.push_back(e5);

    CorpsaCorps c1(0);
    Distance d1(0);

    std::vector<Armes*> listeArmes;
    listeArmes.push_back(&c1);
    listeArmes.push_back(&d1);

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
                    game.entryManager(event, window, j1, j2, listeArmes);   // Page de jeu
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
            //for (Joueur j : listeJoueurs) j.debug_mvt(); 
            //for (Joueur& j : lJoueurs) j.mouvement();
            j1.mouvement();
            j2.mouvement();

            //for (Ennemi e : listeEnnemis) e.debug_mvt(); 
            //for (Ennemi e : lEnnemis) e.aleatoire_mvt();
            e1.aleatoire_mvt();
            e2.aleatoire_mvt();
            e3.aleatoire_mvt();
            e4.aleatoire_mvt();
            e5.aleatoire_mvt();
            //for (Ennemi e : listeEnnemis) e.suivi();

            startTime = currentTime;
        }

        // Clear the window
        window.clear();

        // Draw background
        if (etatJeu == 0) {
            window.draw(backgroundSprite);
        }

        // Draw the sprite
        // Joueur
        //for (Joueur j : lJoueurs) window.draw(j.sprite);
        window.draw(j1.sprite);
        window.draw(j2.sprite);
        // Ennemi
        //for (Ennemi e : lEnnemis) window.draw(e.sprite);
        window.draw(e1.sprite);
        window.draw(e2.sprite);
        window.draw(e3.sprite);
        window.draw(e4.sprite);
        window.draw(e5.sprite);
        // Armes
        
        if (j1.armes != nullptr) window.draw(j1.armes->sprite);
        if (j2.armes != nullptr) window.draw(j2.armes->sprite);
        if (c1.portee == false) window.draw(c1.sprite);
        if (d1.portee == false) window.draw(d1.sprite);
        // Barre de vie
        window.draw(j1.barrevie.rectangle_red); window.draw(j1.barrevie.rectangle_white);
        window.draw(j2.barrevie.rectangle_red); window.draw(j2.barrevie.rectangle_white);

        // Display the contents of the window
        window.display();
    }

    return EXIT_SUCCESS;
}