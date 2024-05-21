#include <SFML/Graphics.hpp>
#include "../declaration.hpp"
#include "../point.hpp"
#include "../rectangle.hpp"
#include <random>
#include <iostream>

using namespace sf;

extern std::string reference;
extern std::string listeWallsEdge[];
extern std::string listeWallsFountainAnim[];
extern std::string listeWallsOther[];
extern std::string listeFloor[];
extern std::string listeWalls[];
extern std::string banner[];
extern std::string floor_str;
extern std::string wall_str;
extern std::string fin_str;
extern std::string wall_edge_str;

int n = 27;
int m = 15;
int nb_wall_edge = 8;

RectangleShape tabTiles[27][15];
RectangleShape tabTilesWall[8][27][15];
Texture texture_floor[8];
Texture texture_walls[5];
Texture texture_edge[12];
Texture texture_banner[2];
int listeAvailable[27][15];
std::vector<Point> positionPortes = {Point(0, 9), Point(0, 5), Point(8, 0), Point(18, 0), Point(27, 5), Point(27, 9), Point(18, 15), Point(8, 15)};

std::map<Point, int> pointMap;          // Map pour stocker les points avec leurs occurrences (l'entier associé)
std::map<Point, int> pointMapInverted;  // Map inversée pour stocker les points avec leurs occurrences
std::vector<Point> contourList;         // Points qui composent le contour
std::vector<Rectangle> obstacleList;

void initAvailable();
void generate_walls();
void addSallePP(Point p, int w, int h);
void printTerminal();
void addPortes(int n);
void generate_floor();
void addZone();
int nbAvailable(int x, int y);
void buildWallEdge();
void addFlag(int n1, int n2);
void printPoints();
void printContour();
void contour();
void printObstable();

int main() {
    RenderWindow window(VideoMode(1280,720), "My map");
    
    for (int i = 0; i < 8; i++) {
        texture_floor[i].loadFromFile("../" + reference + floor_str + listeFloor[i] + fin_str);
    }

    for (int i = 0; i < 5; i++) {
        texture_walls[i].loadFromFile("../" + reference + wall_str + listeWalls[i] + fin_str);
    }

    for (int i = 0; i < 12; i++) {
        texture_edge[i].loadFromFile("../" + reference + wall_edge_str + listeWallsEdge[i] + fin_str);
    }

    for (int i = 0; i < 2; i++) {
        texture_banner[i].loadFromFile("../" + reference + wall_str + banner[i] + fin_str);
    }

    std::cout << "0" << std::endl;
    int n1 = 6;
    int n2 = 1;
    // Initialisation
    initAvailable();
    generate_walls();
    // Salle principale
    addSallePP(Point(100,200), 1050, 400);
    //Portes
    addPortes(n1);
    addPortes(n2);
    // Add obstable et zone
    addZone();
    std::cout << "1" << std::endl;
    printTerminal();
    // sol
    generate_floor();
    std::cout << "2" << std::endl;
    // add wall edge
    buildWallEdge();
    std::cout << "3" << std::endl;
    // addFlag
    addFlag(n1,n2);
    std::cout << "4" << std::endl;

    printPoints();
    printObstable();
    //contour(),
    //printContour();

    Texture texture_save;
    Image screenshot;

    // Main loop
    bool test = true; 
    while (test) {

        // Handle events
        Event event;
        while (window.pollEvent(event)) {
            if (event.type == Event::Closed) {
                test = false;
            }
        }

        // Clear the window
        window.clear();
        //window.draw(shape);
        for (int x = 0; x < n; x++) {
            for (int y = 0; y < m; y++) {
                window.draw(tabTiles[x][y]);
                for (int j = 0; j < nb_wall_edge; j++) window.draw(tabTilesWall[j][x][y]);
            }
        }

        // Display the contents of the window
        window.display();

    }

    texture_save.create(window.getSize().x, window.getSize().y);
    texture_save.update(window);
    screenshot = texture_save.copyToImage();
    //screenshot.flipVertically();

    if (screenshot.saveToFile("map.png")) {
        std::cout << "Screenshot saved to screenshot.png" << std::endl;
    } else {
        std::cout << "Failed to save screenshot" << std::endl;
    }

    window.close();

    return 0;
}

void initAvailable() {
    for (int x = 0; x < n; x++) {
        for (int y = 0; y < m; y++) {
            listeAvailable[x][y] = 0;
        }
    }
}

void printTerminal() {
    for (int y = 0; y < m; y++) {
        for (int x = 0; x < n; x++) {
            std::cout << listeAvailable[x][y];
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;
}

void generate_walls() {
    // Initialiser le générateur de nombres aléatoires
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(0, 4); // Pour générer des indices entre 0 et 7
    std::uniform_int_distribution<> dis2(0, 1); // Pour générer des indices entre 0 et 3

    for (int x = 0; x < n; x++) {
        for (int y = 0; y < m; y++) {
            tabTiles[x][y].setSize(Vector2f(48,48));
            tabTiles[x][y].setPosition(x*48,y*48);
            tabTiles[x][y].setFillColor(Color::White);
            tabTiles[x][y].setTexture(&texture_walls[dis(gen)]);

            // Réinitialiser l'origine et l'échelle pour éviter les transformations accumulatives
            tabTiles[x][y].setOrigin(0, 0);
            tabTiles[x][y].setScale(1, 1);
            
            switch (dis2(gen)) {
                case 0:
                    tabTiles[x][y].setScale(-1, 1);
                    tabTiles[x][y].setOrigin(tabTiles[x][y].getSize().x, 0);
                    break;
                default:
                    break;
            }
        }
    }
}

void addSallePP(Point p, int w, int h) {
    for (int x = p.getX()/48; x < (p.getX() + w)/48; x++) {
        for (int y = p.getY()/48; y < (p.getY() + h)/48; y++) {
            listeAvailable[x][y] = 1;
        }
    }
    pointMap[Point(p.getX(), p.getY())]++;
    pointMap[Point(p.getX()+w, p.getY())]++;
    pointMap[Point(p.getX(), p.getY()+h)]++;
    pointMap[Point(p.getX()+w, p.getY()+h)]++;
    pointMapInverted[Point(p.getY(), p.getX())]++;
    pointMapInverted[Point(p.getY()+h, p.getX())]++;
    pointMapInverted[Point(p.getY(), p.getX()+w)]++;
    pointMapInverted[Point(p.getY()+h, p.getX()+w)]++;
}

void addPortes(int n) {
    int x = positionPortes[n].getX();
    int y = positionPortes[n].getY();
    int dx = 0, dy = 0;
    if (n == 0 || n == 1) dx = 1;
    else if (n == 2 || n == 3) dy = 1;
    else if (n == 4 || n == 5) dx = -1;
    else dy = -1;
    while (listeAvailable[x][y] != 1) {
        listeAvailable[x][y] = 1;
        listeAvailable[x+dy][y+dx] = 1;
        listeAvailable[x-dy][y-dx] = 1;
        
        pointMap[Point(x*48,        y*48)]++;
        pointMap[Point(x*48 + 48,   y*48)]++;
        pointMap[Point(x*48,        y*48+48)]++;
        pointMap[Point(x*48 + 48,   y*48+48)]++;
        pointMapInverted[Point(y*48,       x*48)]++;
        pointMapInverted[Point(y*48+48,    x*48)]++;
        pointMapInverted[Point(y*48,       x*48+48)]++;
        pointMapInverted[Point(y*48+48,    x*48+48)]++;
        
        x += dx;
        y += dy;
    }
}

void addZone() {
    // Initialiser le générateur de nombres aléatoires
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(0, 25); // Pour générer des indices entre 0 et 7
    for (int x = 0; x < n; x++) {
        for (int y = 0; y < m; y++) {
            if (listeAvailable[x][y] == 0 && nbAvailable(x, y) != 0) {
                if (dis(gen) == 0) {
                    listeAvailable[x][y] = 1;

                    pointMap[Point(x*48,        y*48)]++;
                    pointMap[Point(x*48 + 48,   y*48)]++;
                    pointMap[Point(x*48,        y*48+48)]++;
                    pointMap[Point(x*48 + 48,   y*48+48)]++;
                    pointMapInverted[Point(y*48,       x*48)]++;
                    pointMapInverted[Point(y*48+48,    x*48)]++;
                    pointMapInverted[Point(y*48,       x*48+48)]++;
                    pointMapInverted[Point(y*48+48,    x*48+48)]++;
                }
            }
        }
    }

    for (int x = 0; x < n-1; x++) {
        for (int y = 0; y < m-1; y++) {
            if (listeAvailable[x][y] == 1 && listeAvailable[x+1][y+1] == 1) {
                if (dis(gen) == 0) {
                    listeAvailable[x][y] = 0;
                    listeAvailable[x+1][y] = 0;
                    listeAvailable[x+1][y+1] = 0;
                    listeAvailable[x][y+1] = 0;
                    obstacleList.push_back(Rectangle(Point(x,y), 2, 2));
                }
                //else if (nbAvailable(x,y) != 4 && dis(gen) < 2) listeAvailable[x][y] = 0;
            }
        }
    }
}

int nbAvailable(int x, int y) {
    int cpt = 0;
    if (x > 0 && x < n-1 && y > 0 && y < m-1) {
        cpt += listeAvailable[x-1][y] + listeAvailable[x+1][y] + listeAvailable[x][y+1] + listeAvailable[x][y-1];
    }
    return cpt;
}

void generate_floor() {
    // Initialiser le générateur de nombres aléatoires
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(0, 7); // Pour générer des indices entre 0 et 7
    std::uniform_int_distribution<> dis2(0, 3); // Pour générer des indices entre 0 et 3

    for (int x = 0; x < n; x++) {
        for (int y = 0; y < m; y++) {
            if (listeAvailable[x][y] == 1) {
                tabTiles[x][y].setSize(Vector2f(48,48));
                tabTiles[x][y].setPosition(x*48,y*48);
                tabTiles[x][y].setTexture(&texture_floor[dis(gen)]);

                // Réinitialiser l'origine et l'échelle pour éviter les transformations accumulatives
                tabTiles[x][y].setOrigin(0, 0);
                tabTiles[x][y].setScale(1, 1);
                
                switch (dis2(gen)) {
                    case 0:
                        tabTiles[x][y].setScale(1, -1);
                        tabTiles[x][y].setOrigin(0, tabTiles[x][y].getSize().y);
                        break;
                    case 1:
                        tabTiles[x][y].setScale(-1, -1);
                        tabTiles[x][y].setOrigin(tabTiles[x][y].getSize().x, tabTiles[x][y].getSize().y);
                        break;
                    case 2:
                        tabTiles[x][y].setScale(-1, 1);
                        tabTiles[x][y].setOrigin(tabTiles[x][y].getSize().x, 0);
                        break;
                    default:
                        break;
                }
            }
        }
    }
}

void buildWallEdge() {
    // Initialiser le générateur de nombres aléatoires
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(0, 1); // Pour générer des indices entre 0 et 7
    for (int x = 0; x < n; x++) {
        for (int y = 0; y < m; y++) {
            // top
            if (y < m-1 && x < n-1 && x > 0) {
                if (listeAvailable[x][y] == 0 && listeAvailable[x][y+1] == 1 && listeAvailable[x+1][y] == 0 && listeAvailable[x-1][y] == 0) {
                    tabTilesWall[0][x][y].setSize(Vector2f(48,48));
                    tabTilesWall[0][x][y].setPosition(x*48,y*48);
                    tabTilesWall[0][x][y].setTexture(&texture_edge[6 + dis(gen)]);
                    tabTilesWall[0][x][y].setOrigin(0, 0);
                    tabTilesWall[0][x][y].setScale(1, 1);
                }
            }
            // bottom
            if (y > 0 && x < n-1 && x > 0) {
                if (listeAvailable[x][y-1] == 1 && listeAvailable[x][y] == 0 && listeAvailable[x+1][y] == 0 && listeAvailable[x-1][y] == 0) {
                    tabTilesWall[1][x][y].setSize(Vector2f(48,48));
                    tabTilesWall[1][x][y].setOrigin(tabTilesWall[1][x][y].getSize().x, tabTilesWall[1][x][y].getSize().y);
                    tabTilesWall[1][x][y].setPosition(x*48,y*48);
                    tabTilesWall[1][x][y].setTexture(&texture_edge[6 + dis(gen)]);
                    tabTilesWall[1][x][y].setScale(1, 1);
                    tabTilesWall[1][x][y].setRotation(180);
                }
            }
            // right
            if (x > 0 && y < m-1 && y > 0) {
                if (listeAvailable[x-1][y] == 1 && listeAvailable[x][y] == 0 && listeAvailable[x][y+1] == 0 && listeAvailable[x][y+1] == 0) {
                    tabTilesWall[1][x][y].setSize(Vector2f(48,48));
                    tabTilesWall[1][x][y].setOrigin(tabTilesWall[1][x][y].getSize().x, tabTilesWall[1][x][y].getSize().y);
                    tabTilesWall[1][x][y].setPosition(x*48,y*48+48);
                    tabTilesWall[1][x][y].setTexture(&texture_edge[6 + dis(gen)]);
                    tabTilesWall[1][x][y].setScale(1, 1);
                    tabTilesWall[1][x][y].setRotation(90);
                }
            }
            // left
            if (x < n-1 && y < m-1 && y > 0) {
                if (listeAvailable[x+1][y] == 1 && listeAvailable[x][y] == 0 && listeAvailable[x][y+1] == 0 && listeAvailable[x][y+1] == 0) {
                    tabTilesWall[1][x][y].setSize(Vector2f(48,48));
                    tabTilesWall[1][x][y].setOrigin(tabTilesWall[1][x][y].getSize().x, tabTilesWall[1][x][y].getSize().y);
                    tabTilesWall[1][x][y].setPosition(x*48+48,y*48);
                    tabTilesWall[1][x][y].setTexture(&texture_edge[6 + dis(gen)]);
                    tabTilesWall[1][x][y].setScale(1, 1);
                    tabTilesWall[1][x][y].setRotation(270);
                }
            }
            // coin top-left
            if (y > 0 && x < n-1 && x > 0) {
                if (listeAvailable[x][y-1] == 1 && listeAvailable[x][y] == 0 && listeAvailable[x+1][y] == 1) {
                    tabTilesWall[2][x][y].setSize(Vector2f(48,48));
                    tabTilesWall[2][x][y].setPosition(x*48,y*48);
                    tabTilesWall[2][x][y].setTexture(&texture_edge[8*dis(gen)]);
                    tabTilesWall[2][x][y].setScale(1, 1);
                    tabTilesWall[2][x][y].setOrigin(tabTilesWall[2][x][y].getSize().x, tabTilesWall[2][x][y].getSize().y);
                    tabTilesWall[2][x][y].setRotation(180);
                }
            }
            // coin top-right
            if (y > 0 && x < n-1 && x > 0) {
                if (listeAvailable[x][y-1] == 1 && listeAvailable[x][y] == 0 && listeAvailable[x-1][y] == 1) {
                    tabTilesWall[3][x][y].setSize(Vector2f(48,48));
                    tabTilesWall[3][x][y].setPosition(x*48+48,y*48);
                    tabTilesWall[3][x][y].setTexture(&texture_edge[8*dis(gen)]);
                    tabTilesWall[3][x][y].setOrigin(tabTilesWall[3][x][y].getSize().x, tabTilesWall[3][x][y].getSize().y);
                    //tabTilesWall[3][x][y].setRotation(90);
                    //tabTilesWall[3][x][y].setOrigin(tabTilesWall[3][x][y].getSize().x/2, tabTilesWall[3][x][y].getSize().y/2);
                    tabTilesWall[3][x][y].setScale(1, -1);
                }
            }
            // coin bottom-left
            if (y < m-1 && x < n-1 && x > 0) {
                if (listeAvailable[x][y+1] == 1 && listeAvailable[x][y] == 0 && listeAvailable[x-1][y] == 1) {
                    tabTilesWall[4][x][y].setSize(Vector2f(48,48));
                    tabTilesWall[4][x][y].setPosition(x*48+48,y*48+48);
                    tabTilesWall[4][x][y].setTexture(&texture_edge[8*dis(gen)]);
                    tabTilesWall[4][x][y].setOrigin(tabTilesWall[4][x][y].getSize().x, tabTilesWall[4][x][y].getSize().y);
                    //tabTilesWall[3][x][y].setRotation(90);
                    //tabTilesWall[3][x][y].setOrigin(tabTilesWall[3][x][y].getSize().x/2, tabTilesWall[3][x][y].getSize().y/2);
                    //tabTilesWall[3][x][y].setScale(1, -1);
                }
            }
            // coin bottom-right
            if (y < m-1 && x < n-1 && x > 0) {
                if (listeAvailable[x][y+1] == 1 && listeAvailable[x][y] == 0 && listeAvailable[x+1][y] == 1) {
                    tabTilesWall[5][x][y].setSize(Vector2f(48,48));
                    tabTilesWall[5][x][y].setPosition(x*48+48,y*48);
                    tabTilesWall[5][x][y].setTexture(&texture_edge[8*dis(gen)]);
                    tabTilesWall[5][x][y].setOrigin(0, 0);
                    //tabTilesWall[5][x][y].setOrigin(tabTilesWall[5][x][y].getSize().x, tabTilesWall[5][x][y].getSize().y);
                    //tabTilesWall[3][x][y].setRotation(90);
                    //tabTilesWall[3][x][y].setOrigin(tabTilesWall[3][x][y].getSize().x/2, tabTilesWall[3][x][y].getSize().y/2);
                    tabTilesWall[5][x][y].setScale(-1, 1);
                }
            }
        }
    }
    // Ligne gauche
    for (int x = 0; x < n; x+= n-1) {
        for (int y = 0; y < m; y++) {
            if (y < m-1) {
                if (listeAvailable[x][y] == 0 && listeAvailable[x][y+1] == 1) {
                    tabTilesWall[0][x][y].setSize(Vector2f(48,48));
                    tabTilesWall[0][x][y].setPosition(x*48,y*48);
                    tabTilesWall[0][x][y].setTexture(&texture_edge[6 + dis(gen)]);
                    tabTilesWall[0][x][y].setOrigin(0, 0);
                    tabTilesWall[0][x][y].setScale(1, 1);
                }
            }
            if (y > 0) {
                if (listeAvailable[x][y] == 0 && listeAvailable[x][y-1] == 1) {
                    tabTilesWall[1][x][y].setSize(Vector2f(48,48));
                    tabTilesWall[1][x][y].setPosition(x*48,y*48);
                    tabTilesWall[1][x][y].setTexture(&texture_edge[6 + dis(gen)]);
                    //tabTilesWall[1][x][y].setOrigin(0, 0);
                    tabTilesWall[1][x][y].setOrigin(tabTilesWall[1][x][y].getSize().x, tabTilesWall[1][x][y].getSize().y);
                    tabTilesWall[1][x][y].setScale(1, 1);
                    tabTilesWall[1][x][y].setRotation(180);
                }
            }
        }
    }
    for (int y = 0; y < m; y+= m-1) {
        for (int x = 0; x < n; x++) {
            if (x < n-1) {
                if (listeAvailable[x][y] == 0 && listeAvailable[x+1][y] == 1) {
                    tabTilesWall[2][x][y].setSize(Vector2f(48,48));
                    tabTilesWall[2][x][y].setPosition(x*48+48,y*48);
                    tabTilesWall[2][x][y].setTexture(&texture_edge[6 + dis(gen)]);
                    tabTilesWall[2][x][y].setScale(1, 1);
                    tabTilesWall[2][x][y].setOrigin(tabTilesWall[2][x][y].getSize().x, tabTilesWall[2][x][y].getSize().y);
                    tabTilesWall[2][x][y].setRotation(270);
                }
            }
            if (x > 0) {
                if (listeAvailable[x][y] == 0 && listeAvailable[x-1][y] == 1) {
                    tabTilesWall[1][x][y].setSize(Vector2f(48,48));
                    tabTilesWall[1][x][y].setOrigin(tabTilesWall[1][x][y].getSize().x, tabTilesWall[1][x][y].getSize().y);
                    tabTilesWall[1][x][y].setPosition(x*48,y*48+48);
                    tabTilesWall[1][x][y].setTexture(&texture_edge[6 + dis(gen)]);
                    tabTilesWall[1][x][y].setScale(1, 1);
                    tabTilesWall[1][x][y].setRotation(90);
                }
            }
        }
    }
}

void addFlag(int n1, int n2) {
    std::vector<Point> positionPortes = {Point(0, 9), Point(0, 5), Point(8, 0), Point(18, 0), Point(26, 5), Point(26, 9), Point(18, 15), Point(8, 15)};
    std::cout << n1 << " : " << positionPortes[n1].getX() << " ; " << positionPortes[n1].getY() << std::endl;
    std::cout << n2 << " : " << positionPortes[n2].getX() << " ; " << positionPortes[n2].getY() << std::endl;
    tabTiles[(int) positionPortes[n1].getX()][(int) positionPortes[n1].getY()].setPosition((int) positionPortes[n1].getX()*48, (int) positionPortes[n1].getY()*48);
    tabTiles[(int) positionPortes[n1].getX()][(int) positionPortes[n1].getY()].setTexture(&texture_banner[1]);
    tabTiles[(int) positionPortes[n2].getX()][(int) positionPortes[n2].getY()].setPosition((int) positionPortes[n2].getX()*48, (int) positionPortes[n2].getY()*48);
    tabTiles[(int) positionPortes[n2].getX()][(int) positionPortes[n2].getY()].setTexture(&texture_banner[0]);
}

// Affichage des map pointMap et pointMapInverted
void printPoints() {
    std::cout << "Vertical : " << std::endl;
    for (const auto& pair : pointMap) {
        if (pair.second == 1) // Si l'occurrence du point est égale à 1, imprimez le point
            std::cout << pair.first.getX() << " : " << pair.first.getY() << std::endl;
    }
    std::cout << std::endl << "horizontal : " << std::endl;
    for (const auto& pair : pointMapInverted) {
        if (pair.second == 1) // Si l'occurrence du point est égale à 1, imprimez le point
            std::cout << pair.first.getY() << " : " << pair.first.getX() << std::endl;
    }
}

// Affichage du vector contourList
void printContour() {
    std::cout << "\nContour : " << std::endl;
    for (const Point& point : contourList) {
        std::cout << point.getX() << " : " << point.getY() << std::endl;
    }
}

void printObstable() {
    std::cout << "\nObstacles : " << std::endl;
    for (const Rectangle& r : obstacleList) {
        std::cout << r.getX()-r.getWidth()/2 << " " << r.getY()-r.getHeight()/2 << " " << r.getWidth() << " " << r.getHeight() << std::endl;
    }
}

// Calcul des points du contour de la salle (alternance horizontale-vertical)
void contour() {
    int maxX = 1280;  // Taille max de la salle en x
    int maxY = 720;  // Taille max de la salle en y
    int i;
    std::cout << "debut contour" << std::endl;
    // Calcul point de départ du contour
    Point actualPoint(0,0);
    while (pointMap[actualPoint] != 1) {
        if (actualPoint.getX() < maxX) {
            actualPoint.setX(actualPoint.getX() + 1);
        }
        else {
            actualPoint.setX(0);
            actualPoint.setY(actualPoint.getY() + 1);
        }
        //std::cout << "depart " << actualPoint.getX() << " " << actualPoint.getY() << " " << pointMapInverted[actualPoint] << std::endl;
    }
    contourList.push_back(actualPoint); // Ajout du point
    std::cout << "point depart trouve" << std::endl;

    int actualX = actualPoint.getX(), actualY = actualPoint.getY();
    Point newPoint(1,1);
    std::cout << "depart " << actualX << " " << actualY << std::endl;
    
    while (newPoint != actualPoint) {
        // Horizontal
        i = 1;
        
        // Calcul du prochain point selon x
        while (pointMapInverted[Point(actualY, actualX + i)] != 1 && (pointMapInverted[Point(actualY, actualX - i)] != 1 || actualX-i < 0) && i < maxX) {
            i++;
        }
        std::cout << "h " << actualX << " " << actualY << std::endl;
        // Séparation entre devant ou derriere
        if (pointMapInverted[Point(actualY, actualX + i)] == 1) newPoint = Point(actualX+i, actualY);
        else newPoint = Point(actualX-i, actualY);
        
        contourList.push_back(newPoint);    // Ajout du point
        
        // Suppresion dans les listes
        pointMapInverted[Point(newPoint.getY(), newPoint.getX())] = 0;
        pointMap[newPoint] = 0;

        actualX = newPoint.getX();  // Mise à jour de actualX

        //if (newPoint.x_ >= 0 && newPoint.y_ >= 0) std::cout << newPoint << std::endl;

        // Vertical
        i = 1;
        // Calcul du prochain point selon y
        while (pointMap[Point(actualX, actualY+i)] != 1 && (pointMap[Point(actualX, actualY-i)] != 1 || actualY-i<0) && i < maxY) {
            i++;
        }
        std::cout << "v " << actualX << " " << actualY << std::endl;
        // Séparation entre haut et bas
        if (pointMap[Point(actualX, actualY+i)] == 1) newPoint = Point(actualX, actualY+i);
        else newPoint = Point(actualX, actualY-i);

        contourList.push_back(newPoint);    // Ajout du point
        
        // Suppresion dans les listes
        pointMapInverted[Point(newPoint.getY(), newPoint.getX())] = 0;
        pointMap[newPoint] = 0;

        actualY = newPoint.getY();  // Mise à jour du actualY
        
        //if (newPoint.x_ >= 0 && newPoint.y_ >= 0) std::cout << newPoint << std::endl;
    }

}