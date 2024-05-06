#include "Salles.hpp"

Salles::Salles(const Point& c, float w, float h){
	center=c;
	sect.push_back(Rectangle(c,w,h);
	n=n+1;
}
bool addobst(int width, int height, Point pos){
	 bool ans=false;
	 for (Rectangle* r : sect){
	 	if r.inrectangle(pos)
	 		{ans=true;
	 		obst.push_back(Rectangle(pos,width*4*16,height*4*16));
	 		}
	 return (ans);
	 } 
}
bool addsect(int width, int height, Point pos){
	Point p1(p.getX() -width*16*4/2, p.getY()-height*16*4/2);
	Point p2(p.getX() -width*16*4/2, p.getY()+height*16*4/2);
	Point p3(p.getX() +width*16*4/2, p.getY()+height*16*4/2);
	Point p4(p.getX() +width*16*4/2, p.getY()-height*16*4/2);
	for (Rectangle* r : sect){
		if (r.inrectangle(p1)||r.inrectangle(p2)||r.inrectangle(p3)||r.inrectangle(p4)){
			return false;
		}	
	}
	for (Rectangle* r : sect){
		if (r.inrectangle(p1)||r.inrectangle(p2)||r.inrectangle(p3)||r.inrectangle(p4)){
			return false;
		}	
	}
}
void setcenter(Point p);
void setdoor(Point p);

// Décomposition des rectangles en une liste de points
void Salles::getPoints() {
	for (Rectangle* r : sect) {
	        // Tri selon x
	        Point p=r.getCenter();
	        pointMap[Point(p.getX() -r.getWidth()/2, p.getY()-r.getHeight/2)]++;
	        pointMap[Point(p.getX() +r.getWidth()/2, p.getY()-r.getHeight/2)]++;
	        pointMap[Point(p.getX() +r.getWidth()/2, p.getY()+r.getHeight/2)]++;
	        pointMap[Point(p.getX() -r.getWidth()/2, p.getY()+r.getHeight/2)]++;
	
	        // Tri selon y
	        pointMapInverted[Point(p.getY() -r.getHeight()/2, p.getX()-r.getWidth/2)]++;
	        pointMapInverted[Point(p.getY() -r.getHeight()/2, p.getX()+r.getWidth/2)]++;
	        pointMapInverted[Point(p.getY() +r.getHeight()/2, p.getX()+r.getWidth/2)]++;
	        pointMapInverted[Point(p.getY() +r.getHeight()/2, p.getX()-r.getWidth/2)]++;
	}
}

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

// Affichage du vector contourList
void Salles::printContour() {
	std::cout << "\nContour : " << std::endl;
	for (const Point& point : contourList) {
		std::cout << point.getX() << " : " << point.getY() << std::endl;
	}
}

// Calcul des points du contour de la salle (alternance horizontale-vertical)
void Salles::contour() {
	int maxX = 50;  // Taille max de la salle en x
	int maxY = 50;  // Taille max de la salle en y
	int i;

	// Calcul point de départ du contour
	Point actualPoint(0,0);
	while (pointMapInverted[actualPoint] != 1) {
		if (actualPoint.getX() < maxX) actualPoint.setX()=actualPoint.getX()+1;
		else actualPoint.setY()=actual.getY()+1;
	}
	contourList.push_back(actualPoint); // Ajout du point

	int actualX = actualPoint.getX(), actualY = actualPoint.getY();
	Point newPoint(1,1);
    
	while (newPoint != actualPoint) {
		// Horizontal
		i = 1;
        
		// Calcul du prochain point selon x
		while (pointMapInverted[Point(actualY, actualX + i)] != 1 && (pointMapInverted[Point(actualY, actualX - i)] != 1 || actualX-i < 0) && i < maxX) {
			i++;
		}
		// Séparation entre devant ou derriere
		if (pointMapInverted[Point(actualY, actualX + i)] == 1) newPoint = Point(actualX+i, actualY);
		else newPoint = Point(actualX-i, actualY);
        
		contourList.push_back(newPoint);    // Ajout du point
        
		// Suppresion dans les listes
		pointMapInverted[Point(newPoint.y_, newPoint.x_)] = 0;
		pointMap[newPoint] = 0;

		actualX = newPoint.x_;  // Mise à jour de actualX

		//if (newPoint.x_ >= 0 && newPoint.y_ >= 0) std::cout << newPoint << std::endl;
		// Vertical
		i = 1;
		// Calcul du prochain point selon y
		while (pointMap[Point(actualX, actualY+i)] != 1 && (pointMap[Point(actualX, actualY-i)] != 1 || actualY-i<0) && i < maxY) {
			i++;
		}
		// Séparation entre haut et bas
		if (pointMap[Point(actualX, actualY+i)] == 1) newPoint = Point(actualX, actualY+i);
		else newPoint = Point(actualX, actualY-i);

		contourList.push_back(newPoint);    // Ajout du point
        
		// Suppresion dans les listes
		pointMapInverted[Point(newPoint.y_, newPoint.x_)] = 0;
		pointMap[newPoint] = 0;

		actualY = newPoint.y_;  // Mise à jour du actualY
        
		//if (newPoint.x_ >= 0 && newPoint.y_ >= 0) std::cout << newPoint << std::endl;
	}

}
