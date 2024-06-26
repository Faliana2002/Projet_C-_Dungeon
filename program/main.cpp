#include <SFML/Graphics.hpp>
#include <iostream>
#include <chrono>

#include "../class/Personnages/Joueurs.hpp"
#include "../class/Personnages/Ennemi.hpp"
#include "../class/declaration.hpp"
#include "../class/Gestion.hpp"
#include "../class/Armes/CorpsaCorps.hpp"
#include "../class/Armes/Distance.hpp"
#include "../class/point.hpp"

#include "../class/Salles-test/Salles.hpp"

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

    Salles salle_test;
    //Salles salle_test(Point(144,96), 960, 540, 0, 4);
    
    // Premier joueur
    Joueur j1(2, 960-16*4/2, 360-28*4/2);
    Joueur j2(1, 320-16*4/2, 360-28*4/2);
    //Joueur j3(3, 640-16*4/2, 360-16*4/2);

    std::vector<Joueur*> lJoueurs;
    lJoueurs.push_back(&j1);
    lJoueurs.push_back(&j2);
    //lJoueurs.push_back(&j3);

    //Ennemi e1(1, 600,400);
    //Ennemi e2(2,300, 384);
    //Ennemi e3(3,1000, 432);
    //Ennemi e4(4,700, 353);
    //Ennemi e5(14,532, 528);
    Ennemi e1(1, salle_test, -1);
    Ennemi e2(2, salle_test, -1);
    Ennemi e3(3, salle_test, -1);
    Ennemi e4(4, salle_test, -1);
    Ennemi e5(14,salle_test, -1);

    std::vector<Ennemi*> lEnnemis;
    lEnnemis.push_back(&e1);
    lEnnemis.push_back(&e2);
    lEnnemis.push_back(&e3);
    lEnnemis.push_back(&e4);
    lEnnemis.push_back(&e5);

    //cout << "On crée des armes" << endl;
    CorpsaCorps c1(0, salle_test, -1);
    CorpsaCorps c2(1, salle_test, -1);
    CorpsaCorps c3(2, salle_test, -1);
    CorpsaCorps c4(1, salle_test, -1);
    Distance d1(0, salle_test, -1);
    //cout << "On a créé des armes" << endl;

    CorpsaCorps c5(0, salle_test, -1);
    e1.armes = &c5;
    e2.armes = &c1;

    std::vector<Armes*> listeArmes;
    //cout << "On ajoute des armes" << endl;
    listeArmes.push_back(&c1);
    listeArmes.push_back(&c2);
    listeArmes.push_back(&c3);
    listeArmes.push_back(&c4);
    listeArmes.push_back(&d1);
    listeArmes.push_back(&c5);
    //cout << "On a ajouté des armes" << endl;

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

    // Gestion du frame rate
    auto now = std::chrono::system_clock::now();
    auto duration = now.time_since_epoch();
    long startTime = std::chrono::duration_cast<std::chrono::milliseconds>(duration).count();
    long currentTime;

    int etatJeu = 0;
    int memEtatJeu = 0;

    // Affichage du tableau des cases accessibles 
    salle_test.printArray(salle_test.listeAvailable);
    for (const Point& p : salle_test.voisins[0][0]) {
        std::cout << "Point accessible depuis (" << 0 << "," << 0 << ") : (" << p.getX() << "," << p.getY() << ")" << std::endl;
    }

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
                    game.startManager(event, window, lJoueurs);   // Page choix personnages
                    break;                
                case 1:
                    game.entryManager(event, window, lJoueurs, listeArmes, lEnnemis);   // Page de jeu
                    break;
                default:
                    break;
            }
        }
        
        etatJeu = 1;
        for (Joueur* j : lJoueurs) {
            if (j->rtp == 0) etatJeu = 0;
        }
        
        // Gestion du frame rate
        auto now = std::chrono::system_clock::now();
        auto duration = now.time_since_epoch();
        currentTime = std::chrono::duration_cast<std::chrono::milliseconds>(duration).count();
        
        if (currentTime - startTime > 20) { // frame rate 50 Hz (20 ms)

            //cout << j1.position.getX() << " - " << j1.position.getY() << endl;

            //cout << "On commence la bucle" << endl;
            //for (Joueur j : listeJoueurs) j.debug_mvt(); 
            for (Joueur* j : lJoueurs) {
                if (j->estVivant) j->mouvement(salle_test);
                //if (j->estVivant) j->debug_mvt();
            
            }
            if (etatJeu == 1){
                //for (Ennemi e : listeEnnemis) e.debug_mvt(); 
                //for (Ennemi* e : lEnnemis) e->aleatoire_mvt(salle_test);
                for (Ennemi* e : lEnnemis) {
                    if (e->estVivant) e->aleatoire_mvt_2(lJoueurs ,salle_test);
                    //if (e->estVivant) e->debug_mvt();
                    //if (e->estVivant) e->suivi(j1);
                    //if (e->estVivant) e->mouvement(1,1);
                }
                for (Ennemi* e : lEnnemis) {
                    if (e->estVivant && e->armes != nullptr) e->hitEnnemis(lJoueurs);
                }
                //for (Ennemi e : listeEnnemis) e.suivi();
            }

            startTime = currentTime;
        }

        // Clear the window
        window.clear();

        int d = 0;
        for (Joueur* j : lJoueurs) {
            d += sqrt( pow(j->position.getX() - salle_test.planES[salle_test.planID][1].getX(), 2) + pow(j->position.getY() - salle_test.planES[salle_test.planID][1].getY(), 2) );
        }
        //std::cout << d << std::endl;
        int nb_ennemi = 0;
        for (Ennemi* e : lEnnemis) {
            if (e->estVivant) nb_ennemi++;
        }
        if (d < 100 && nb_ennemi != 0-1) {
            salle_test.planID++;
            if (salle_test.planID > 3) salle_test.planID = 0;
            for (Joueur* j : lJoueurs) {
                j->vie = j->vieMax;
                j->estVivant = true;
                j->position = salle_test.planES[salle_test.planID][0];
                j->mouvement(0,0);
            }
            for (Ennemi* e : lEnnemis) {
                e->respawn(salle_test);
                e->mouvement(0,0);
            }
            for (int i = 0; i < 5; i++) {
                if (listeArmes[i]->portee == false && lEnnemis[i]->armes == nullptr) {
                    listeArmes[i]->portee == true;
                    lEnnemis[i]->armes = listeArmes[i];
                }
            }
            salle_test.respawn();
        }

        if (etatJeu == 1) window.draw(salle_test.sprite);
        /*if (etatJeu == 1) {
            for (sf::RectangleShape r : salle_test.lineList) window.draw(r);
        }*/

        // Draw background
        if (etatJeu == 0) {
            window.draw(backgroundSprite);
        }

        if (memEtatJeu == 0 && etatJeu == 1) {
            for (Joueur* j : lJoueurs) {
                j->position = salle_test.planES[salle_test.planID][0];
                j->mouvement(0,0);
            }
        }

        // Draw the sprite
        
        // Joueur
        for (Joueur* j : lJoueurs)  {
            if (j->estVivant) {
                window.draw(j->sprite);
                if (etatJeu == 1) {
                    if (j->armes != nullptr) window.draw(j->armes->sprite);
                    window.draw(j->barrevie.rectangle_red); window.draw(j->barrevie.rectangle_white);
                }
            }
        }

        // Ennemi
        if (etatJeu == 1) {
            for (Ennemi* e : lEnnemis) {
                if (e->estVivant) {
                    window.draw(e->sprite);
                    if (e->armes != nullptr) window.draw(e->armes->sprite);
                    window.draw(e->barrevie.rectangle_red); window.draw(e->barrevie.rectangle_white);
                }
            }
            for (Armes* a : listeArmes) {
                //cout << a->portee << " "; 
                if (a->portee == false) window.draw(a->sprite);    
            }
            //cout << endl;
        }


        // Pour le calcul du framerate
        //cout << std::chrono::duration_cast<std::chrono::milliseconds>(duration).count() << endl;

        // Display the contents of the window
        window.display();

        memEtatJeu = etatJeu;
    }

    return EXIT_SUCCESS;
}