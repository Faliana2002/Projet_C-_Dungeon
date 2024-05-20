#include "SallesV2.hpp"

// Affichage des map pointMap et pointMapInverted
void Salles::printPoints() {
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

// Affichage des map pointMap et pointMapInverted
void Salles::printContour() {
    std::cout << "Vertical : " << std::endl;
    for (const auto& pair : contourList) {
        std::cout << pair.getX() << " : " << pair.getY() << std::endl;
    }
}

Salles::Salles(Point p, int w, int h, int porte1, int porte2) {
    std::cout << "Création de la salle" << std::endl;
    // Point de la salle centrale
    for (int dx = 0; dx <= 1; dx++) {
        for (int dy = 0; dy <= 1; dy++) {
            pointMap[Point(p.getX() + w*dx, p.getY() + h*dy)]++;
            pointMapInverted[Point(p.getY() + h*dy, p.getX() + w*dx)]++;
        }
    }
    std::cout << "Salle centrale ajoutée" << std::endl;

    // Distance autour de la salle centrale
    int d1 = p.getX();
    int d2 = p.getY();
    int d3 = 1280 - w - d1;
    int d4 = 720 - h - d2;
    int addX, addY;

    std::vector<int> listePortes;
    listePortes.push_back(porte1);
    listePortes.push_back(porte2);

    // Point des portes
    for (int i : listePortes) {
        std::cout << "porte vu " << i << std::endl;
        // Point haut-gauche
        addX = 0, addY = 0;
        if (i == 4 || i == 5) addX = - (d3-48);
        if (i == 6 || i == 7) addY = - (d4-48);
        pointMap[Point(positionPortes[i].getX() + addX, positionPortes[i].getY() + addY - 48)]++;
        pointMapInverted[Point(positionPortes[i].getY() + addY - 48, positionPortes[i].getX() + addX)]++;
        
        // Point haut-droite
        addX = 0, addY = 0;
        if (i == 0 || i == 1) addX = d1 - 48;
        if (i == 6 || i == 7) addY = -(d4-48); 
        pointMap[Point(positionPortes[i].getX() + addX + 48, positionPortes[i].getY() + addY - 48)]++;
        pointMapInverted[Point(positionPortes[i].getY() + addY - 48, positionPortes[i].getX() + addX + 48)]++;

        // Point bas-droite
        addX = 0, addY = 0;
        if (i == 0 || i == 1) addX = d1 - 48;
        if (i == 2 || i == 3) addY = d2-48; 
        pointMap[Point(positionPortes[i].getX() + addX + 48, positionPortes[i].getY() + addY + 48*2)]++;
        pointMapInverted[Point(positionPortes[i].getY() + addY + 48*2, positionPortes[i].getX() + addX + 48)]++;

        // Point bas-gauche
        addX = 0, addY = 0;
        if (i == 4 || i == 5) addX = - (d3-48);
        if (i == 2 || i == 3) addY = d2-48; 
        pointMap[Point(positionPortes[i].getX() + addX, positionPortes[i].getY() + addY + 48*2)]++;
        pointMapInverted[Point(positionPortes[i].getY() + addY + 48*2, positionPortes[i].getX() + addX)]++;
    }
    std::cout << "Portes ajoutées" << std::endl;

    printPoints();

    // Construire la liste des contours
    contour();
    std::cout << "Contours construit" << std::endl;
    printContour();
    // Construction des lignes de contours
    getLine();
    std::cout << "Lignes crées" << std::endl;

    // Tableau des voisins
    voisins.resize(n, std::vector<std::vector<Point>>(m));
    buildListeAvailable();
    buildVoisins();
    std::cout << "Voisins terminés" << std::endl;

    //init_texture();
    //std::cout << "Init texture terminé" << std::endl;
};

// Calcul des points du contour de la salle (alternance horizontale-vertical)
void Salles::contour() {
    std::cout << "Création des contours" << std::endl;
    int maxX = 1280;  // Taille max de la salle en x
    int maxY = 720;  // Taille max de la salle en y
    int i;

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
    }
    contourList.push_back(actualPoint); // Ajout du point
    std::cout << "Point de départ trouvé" << std::endl;

    int actualX = actualPoint.getX(), actualY = actualPoint.getY();
    Point newPoint(actualX+1, actualY);
    
    // Création de la liste des contours
    while (newPoint != actualPoint) {
        std::cout << "(" << newPoint.getX() << " ; " << newPoint.getY() << ") = " << pointMap[newPoint] << std::endl;
        std::cout << "Recherche d'un point horizontal" << std::endl;
        // Horizontal
        i = 1;
        // Calcul du prochain point selon x (X et Y inversé car la liste est inversé)
        while (pointMapInverted[Point(actualY, actualX + i)] != 1 && (pointMapInverted[Point(actualY, actualX - i)] != 1 || actualX-i < 0) && i < maxX) {
            //std::cout << pointMapInverted[Point(actualY, actualX + i)] << " " << pointMapInverted[Point(actualY, actualX - i)] << " " << i << " " << actualX-i << " " << (pointMapInverted[Point(actualY, actualX + i)] != 1 && (pointMapInverted[Point(actualY, actualX - i)] != 1 || actualX-i < 0) && i < maxX) << std::endl;
            i++;
        }
        std::cout << pointMapInverted[Point(actualY, actualX + i)] << " " << pointMapInverted[Point(actualY, actualX - i)] << " " << i << " " << actualX-i << " " << (pointMapInverted[Point(actualY, actualX + i)] != 1 && (pointMapInverted[Point(actualY, actualX - i)] != 1 || actualX-i < 0) && i < maxX) << std::endl;
        std::cout << "Point horizontal trouvé" << std::endl;
        // Séparation entre devant ou derriere
        if (pointMapInverted[Point(actualY, actualX + i)] == 1) newPoint = Point(actualX+i, actualY);
        else newPoint = Point(actualX-i, actualY);
        
        contourList.push_back(newPoint);    // Ajout du nouveau point selon horizontale
        
        // Suppresion dans les listes
        pointMapInverted[Point(newPoint.getY(), newPoint.getX())] = 0;
        pointMap[newPoint] = 0;

        actualX = newPoint.getX();  // Mise à jour de actualX

        std::cout << "(" << newPoint.getX() << " ; " << newPoint.getY() << ") = " << pointMap[newPoint] << std::endl;
        std::cout << "Recherche d'un point vertical" << std::endl;
        // Vertical
        i = 1;
        // Calcul du prochain point selon y
        while (pointMap[Point(actualX, actualY+i)] != 1 && (pointMap[Point(actualX, actualY-i)] != 1 || actualY-i<0) && i < maxY) {
            //std::cout << pointMap[Point(actualX, actualY+i)] << " " << pointMap[Point(actualX, actualY-i)] << " " << i << " " << actualY-i << " " << (pointMap[Point(actualX, actualY+i)] != 1 && (pointMap[Point(actualX, actualY-i)] != 1 || actualY-i<0) && i < maxY) << std::endl;
            i++;
        }
        std::cout << pointMap[Point(actualX, actualY+i)] << " " << pointMap[Point(actualX, actualY-i)] << " " << i << " " << actualY-i << " " << (pointMap[Point(actualX, actualY+i)] != 1 && (pointMap[Point(actualX, actualY-i)] != 1 || actualY-i<0) && i < maxY) << std::endl;
        std::cout << "Point vertical trouvé" << std::endl;
        // Séparation entre haut et bas
        if (pointMap[Point(actualX, actualY+i)] == 1) newPoint = Point(actualX, actualY+i);
        else newPoint = Point(actualX, actualY-i);

        contourList.push_back(newPoint);    // Ajout du point
        
        // Suppresion dans les listes
        pointMapInverted[Point(newPoint.getY(), newPoint.getX())] = 0;
        pointMap[newPoint] = 0;

        actualY = newPoint.getY();  // Mise à jour du actualY
    }
    // Ajout du point de départ pour fermer la boucle
    //contourList.push_back(contourList[0]);

    std::cout << "Création de la liste finie" << std::endl;
}

// Construction des lignes de contours à partir de la liste contoursList
void Salles::getLine() {
    for (size_t i = 0; i < contourList.size()-1; i++) {
        sf::RectangleShape rectangle;
        rectangle.setPosition(sf::Vector2f(contourList[i].getX(), contourList[i].getY()));
        rectangle.setSize(sf::Vector2f(contourList[i+1].getX() - contourList[i].getX()+thicknessLine, contourList[i+1].getY() - contourList[i].getY()+thicknessLine));
        rectangle.setOutlineColor(color);
        lineList.push_back(rectangle);
    }
    //std::cout << lineList.size() << std::endl;
    /*
    for (Rectangle& r : obstacleList) {
        sf::RectangleShape rectangle1;
        rectangle1.setPosition(sf::Vector2f(r.getX() - r.getWidth()/2, r.getY() - r.getHeight()/2));
        rectangle1.setSize(sf::Vector2f(r.getWidth(), thicknessLine));
        rectangle1.setOutlineColor(color);
        
        sf::RectangleShape rectangle2;
        rectangle2.setPosition(sf::Vector2f(r.getX() + r.getWidth()/2, r.getY() - r.getHeight()/2));
        rectangle2.setSize(sf::Vector2f(thicknessLine, r.getHeight()));
        rectangle2.setOutlineColor(color);

        sf::RectangleShape rectangle3;
        rectangle3.setPosition(sf::Vector2f(r.getX() - r.getWidth()/2, r.getY() + r.getHeight()/2));
        rectangle3.setSize(sf::Vector2f(r.getWidth(), thicknessLine));
        rectangle3.setOutlineColor(color);

        sf::RectangleShape rectangle4;
        rectangle4.setPosition(sf::Vector2f(r.getX() - r.getWidth()/2, r.getY() - r.getHeight()/2));
        rectangle4.setSize(sf::Vector2f(thicknessLine, r.getHeight()));
        rectangle4.setOutlineColor(color);

        lineObstacle.push_back(rectangle1);
        lineObstacle.push_back(rectangle2);
        lineObstacle.push_back(rectangle3);
        lineObstacle.push_back(rectangle4);
    }
    */
}

bool Salles::isIn(Point p) {
    int l = contourList.size();
    int cpt1 = 0, cpt2 = 0;
    for (int i=0; i < l-1; i++) {
        if (contourList[i].getX() > p.getX() && contourList[i+1].getX() > p.getX() && ( (contourList[i].getY() < p.getY() && contourList[i+1].getY() >= p.getY()) || (contourList[i+1].getY() < p.getY() && contourList[i].getY() >= p.getY()) ) && contourList[i].getY() != contourList[i+1].getY() ) cpt1++;
    }
    
    for (int i=0; i < l-1; i++) {
        if ( ( (contourList[i].getX() < p.getX() && contourList[i+1].getX() >= p.getX()) || (contourList[i+1].getX() < p.getX() && contourList[i].getX() >= p.getX()) ) && contourList[i].getY() < p.getY() && contourList[i+1].getY() < p.getY() && contourList[i].getX() != contourList[i+1].getX()) cpt2++;
    }
    /*
    for (Rectangle& r : obstacleList) {
        if (r.inrectangle(p)) {
            return false;
        }
    }
    */
    if (cpt1%2 != 0 && cpt2%2 != 0) return true;
    return false;
}

bool Salles::isAtteignable(int** ll, Point p, Point f) {
    int cas;
    if ((p.getX() > f.getX() && p.getY() > f.getY()) || (p.getX() < f.getX() && p.getY() < f.getY() )) cas = 0;
    else if ((p.getX() > f.getX() && p.getY() < f.getY()) || (p.getX() < f.getX() && p.getY() > f.getY() )) cas = 1;

    if (p.getX() != f.getX() && p.getY() != f.getY()) {
        // Ne fonctionne que pour la diagonale principale (pas l'autre, pas verticale et pas horizontale)
        if (p.getX() > f.getX() && abs(f.getX() - p.getX()) > abs(f.getY() - p.getY())) {
            p.inverse(f);
            //std::cout << "On inverse selon x" << std::endl;
        }
        else if (p.getY() > f.getY() && abs(f.getX() - p.getX()) <= abs(f.getY() - p.getY())) {
            p.inverse(f);
            //std::cout << "On inverse selon y" << std::endl;
        }
        float dx = f.getX() - p.getX();
        float dy = f.getY() - p.getY();
        
        //std::cout << "(" << p.getX() << " " << p.getY() << ")" << std::endl;
        //std::cout << "(" << f.getX() << " " << f.getY() << ")" << std::endl;
        //std::cout << dx << " " << dy << std::endl;
    
        // Paramètres de la droite
        float a = dx/dy;
        float b1 = f.getX() - a*f.getY();
        float b2, b3;
        if (cas == 0) {
            b2 = (f.getX() - 0.5) - a*(f.getY() + 0.5);
            b3 = (f.getX() + 0.5) - a*(f.getY() - 0.5);
        }
        else  {
            b2 = (f.getX() - 0.5) - a*(f.getY() - 0.5);
            b3 = (f.getX() + 0.5) - a*(f.getY() + 0.5);
        }
        //std::cout << a << " " << b1 << " " << b2 << " " << b3 << std::endl;
        float cur_x1, cur_x2, cur_x3;
        float cur_y1, cur_y2, cur_y3;
        // Plus H que V
        if (abs(dy) >= abs(dx)) {
            //std::cout << "Etude selon y" << std::endl;
            for (float cur_y = p.getY() - 0.5; cur_y < f.getY() + 0.5; cur_y += 0.1) {
                if (cur_y >= p.getY() && cur_y <= f.getY()) { // Droite 1
                    cur_x1 = a*cur_y + b1;
                    //std::cout << "1 : (" << (int) round(cur_x1) << "," << (int) round(cur_y) << ")" << std::endl;
                    //std::cout << "(" << (int) round(cur_x1) << "," << (int) round(cur_y) << ") = " << ll[(int) round(cur_x1)][(int) round(cur_y)] << std::endl;
                    if (ll[(int) round(cur_x1)][(int) round(cur_y)] != 1) return false;
                }
                if ( (cur_y > p.getY() + 0.501 && cur_y < f.getY() + 0.499 && cas == 0) || (cur_y > p.getY() - 0.499 && cur_y < f.getY() - 0.502 && cas == 1) ) {   // Droite 2
                    cur_x2 = a*cur_y + b2;
                    //std::cout << "2 : (" << cur_x2 << "," << cur_y << ")" << std::endl;
                    //std::cout << "(" << (int) round(cur_x2) << "," << (int) round(cur_y) << ") = " << ll[(int) round(cur_x2)][(int) round(cur_y)] << std::endl;
                    if (ll[(int) round(cur_x2)][(int) round(cur_y)] != 1) return false;
                }
                if ( (cur_y > p.getY() - 0.499 && cur_y < f.getY() - 0.501 && cas == 0) || (cur_y > p.getY() + 0.501 && cur_y < f.getY() + 0.499 && cas == 1)) {   // Droite 3
                    cur_x3 = a*cur_y + b3;
                    //std::cout << "3 : (" << (int) round(cur_x3) << "," << (int) round(cur_y) << ")" << std::endl;
                    //std::cout << "(" << (int) round(cur_x3) << "," << (int) round(cur_y) << ") = " << ll[(int) round(cur_x3)][(int) round(cur_y)] << std::endl;
                    if (ll[(int) round(cur_x3)][(int) round(cur_y)] != 1) return false;
                }
            }
        }
        else {
            //std::cout << "Etude selon x" << std::endl;
            for (float cur_x = p.getX() - 0.5; cur_x < f.getX() + 0.5; cur_x += 0.1) {
                //std::cout << "(" << round(cur_x) << " " << 0 << ")" << std::endl;
                if (cur_x >= p.getX() && cur_x <= f.getX()) { // Droite 1
                    cur_y1 = (cur_x - b1)/a;
                    //std::cout << "(" << (int) round(cur_x) << "," << (int) round(cur_y1) << ") = " << ll[(int) round(cur_x)][(int) round(cur_y1)] << std::endl;
                    if (ll[(int) round(cur_x)][(int) round(cur_y1)] != 1) return false;
                }
                if ( (cur_x > p.getX() - 0.499 && cur_x < f.getX() - 0.501 && cas == 0) || (cur_x > p.getX() - 0.499 && cur_x < f.getX() - 0.501 && cas == 1)) {   // Droite 2
                    cur_y2 = (cur_x - b2)/a;
                    //std::cout << "(" << (int) round(cur_x) << "," << (int) round(cur_y2) << ") = " << ll[(int) round(cur_x)][(int) round(cur_y2)] << std::endl;
                    if (ll[(int) round(cur_x)][(int) round(cur_y2)] != 1) return false;
                }
                if ( (cur_x > p.getX() + 0.501 && cur_x < f.getX() + 0.499 && cas == 0) || (cur_x > p.getX() + 0.501 && cur_x < f.getX() + 0.499 && cas == 1)) {   // Droite 3
                    cur_y3 = (cur_x - b3)/a;
                    //std::cout << "(" << (int) round(cur_x) << "," << (int) round(cur_y3) << ") = " << ll[(int) round(cur_x)][(int) round(cur_y3)] << std::endl;
                    if (ll[(int) round(cur_x)][(int) round(cur_y3)] != 1) return false;
                }
            }
        }
    }
    else {  // Déplacement Vertical ou horizontal
        if (p.getX() == f.getX()) {   // H
            if (p.getY() > f.getY()) {
                p.inverse(f);
                //std::cout << "On inverse selon x" << std::endl;
            }
            
            for (float cur_y = p.getY(); cur_y <= f.getY(); cur_y++) {
                if (ll[(int) p.getX()][(int) cur_y] != 1) return false;
            }
        }
        else if (p.getY() == f.getY()) {
            if (p.getX() > f.getX()) {
                p.inverse(f);
                //std::cout << "On inverse selon y" << std::endl;
            }

            for (float cur_x = p.getX(); cur_x <= f.getX(); cur_x++) {
                if (ll[(int) cur_x][(int) p.getY()] != 1) return false;
            }            
        }
    }
    
    return true;
}

void Salles::buildVoisins() {
    for (int row = 0; row < n; row++) {
        for (int col = 0; col < m; col++) {
            //std::cout << "Etude de (" << row << "," << col << ")" << std::endl;
            for (int i = 0; i < n; i++) {
                for (int j = 0; j < m; j++) {
                    //std::cout << "En (" << i << "," << j << ")" << std::endl;                    
                    if (isAtteignable(listeAvailable, Point(row, col), Point(i,j))) voisins[row][col].push_back(Point(i,j));
                }
            }
            /*
            for (const Point& p : voisins[row][col]) {
                std::cout << "Point accessible depuis (" << row << "," << col << ") : (" << p.getX() << "," << p.getY() << ")" << std::endl;
            }
            std::cout << std::endl;
            */
        }
    }
}

void Salles::buildListeAvailable() {
    // Initialisation du tableau
    for (int i = 0; i < n; i++) {
        listeAvailable[i] = new int[m];
    }

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (isIn(Point(j*48 + 24, i*48 + 24))) listeAvailable[i][j] = 1;
            else listeAvailable[i][j] = 0;
        }
    }
}

void Salles::printArray(int** ll) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            std::cout << std::setw(1) << ll[i][j] << " "; 
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;
}