#include "Salles.hpp"

std::vector<Point> contourList1 = {Point(384,0),Point(432,0),Point(432,96),Point(1104,96),Point(1104,192),Point(1280,192),Point(1280,336),Point(1152,336),Point(1152,528),Point(1200,528),Point(1200,576),Point(1152,576),Point(1152,672),Point(624,672),Point(624,576),Point(528,576),Point(528,672),Point(480,672),Point(480,576),Point(384,576),Point(384,672),Point(144,672),Point(144,576),Point(336,576),Point(336,480),Point(144,480),Point(144,384),Point(240,384),Point(240,288),Point(144,288),Point(144,96),Point(288,96),Point(288,48),Point(336,48),Point(336,0),Point(384,0)};
std::vector<Rectangle> obstacleList1 = {Rectangle(Point(144,288), 96, 96),Rectangle(Point(480,144), 96, 96),Rectangle(Point(480,240), 96, 96),Rectangle(Point(336,384), 96, 96),Rectangle(Point(432,432), 96, 96),Rectangle(Point(528,144), 96, 96),Rectangle(Point(768,288), 96, 96),Rectangle(Point(816,384), 96, 96),Rectangle(Point(720,480), 96, 96),Rectangle(Point(816,528), 96, 96)};
std::string nom1 = "map1.png";
std::vector<Point> ES1 = {Point(384, 50), Point(1200, 240)};

std::vector<Point> contourList2 = {Point(0,192),Point(288,192),Point(288,96),Point(864,96),Point(868,192),Point(960,192),Point(960,96),Point(1008,96),Point(1008,384),Point(1104,384),Point(1104,336),Point(1152,336),Point(1152,384),Point(1296,384),Point(1296,528),Point(624,528),Point(624,432),Point(528,432),Point(582,528),Point(288,528),Point(288,336),Point(0,336),Point(0, 196)};
std::vector<Rectangle> obstacleList2 = {Rectangle(Point(672,240),96,96)};
std::string nom2 = "map2.png";
std::vector<Point> ES2 = {Point(50, 240), Point(1100, 388)};

std::vector<Point> contourList3 = {Point(0, 384),Point(96,384),Point(96,192),Point(192,192),Point(192,288),Point(288,288),Point(288,192),Point(816,192),Point(816,0),Point(960,0),Point(960,288),Point(1056,288),Point(1056,192),Point(1152,192),Point(1152,336),Point(1056,336),Point(1056,432),Point(1153,432),Point(1152,624),Point(768,624),Point(768,672),Point(720,672),Point(720,624),Point(240,624),Point(240,528),Point(144,528),Point(144,624),Point(96,624),Point(96,528),Point(0,528),Point(0,384)};
std::vector<Rectangle> obstacleList3 = {Rectangle(Point(336,240), 96, 96), Rectangle(Point(528,240), 96, 96), Rectangle(Point(672,432), 96, 96), Rectangle(Point(912,336), 96, 96)};
std::string nom3 = "map3.png";
std::vector<Point> ES3 = {Point(0, 432), Point(864, 10)};

void Salles::getLine() {
    for (size_t i = 0; i < planContour[planID].size()-1; i++) {
        sf::RectangleShape rectangle;
        rectangle.setPosition(sf::Vector2f(planContour[planID][i].getX(), planContour[planID][i].getY()));
        rectangle.setSize(sf::Vector2f(planContour[planID][i+1].getX() - planContour[planID][i].getX()+thicknessLine, planContour[planID][i+1].getY() - planContour[planID][i].getY()+thicknessLine));
        rectangle.setOutlineColor(color);
        lineList.push_back(rectangle);
    }
    //std::cout << lineList.size() << std::endl;

    for (Rectangle& r : planObstacle[planID]) {
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
}

bool Salles::isIn(Point p) {
    int l = planContour[planID].size();
    int cpt1 = 0, cpt2 = 0;
    for (int i=0; i < l-1; i++) {
        if (planContour[planID][i].getX() > p.getX() && planContour[planID][i+1].getX() > p.getX() && ( (planContour[planID][i].getY() < p.getY() && planContour[planID][i+1].getY() >= p.getY()) || (planContour[planID][i+1].getY() < p.getY() && planContour[planID][i].getY() >= p.getY()) ) && planContour[planID][i].getY() != planContour[planID][i+1].getY() ) cpt1++;
    }
    
    for (int i=0; i < l-1; i++) {
        if ( ( (planContour[planID][i].getX() < p.getX() && planContour[planID][i+1].getX() >= p.getX()) || (planContour[planID][i+1].getX() < p.getX() && planContour[planID][i].getX() >= p.getX()) ) && planContour[planID][i].getY() < p.getY() && planContour[planID][i+1].getY() < p.getY() && planContour[planID][i].getX() != planContour[planID][i+1].getX()) cpt2++;
    }
    for (Rectangle& r : planObstacle[planID]) {
        if (r.inrectangle(p)) {
            return false;
        }
    }

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