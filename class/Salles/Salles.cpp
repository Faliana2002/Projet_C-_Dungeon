#include "Salles.hpp"
#include <stdlib.h>
#include <time.h>
#include <iostream>

int valpix=48;
int widths=26;
int heights=14;
//constructeur ne créant que le premier rectangle
Salles::Salles(const Point& c, float w, float h){
	center=c;
	sect.push_back(Rectangle(c,w,h));
	n=1;
}

Salles::Salles(){
//on intialise le random
	printf("test0");
	srand (time(NULL));
	int val;
	int pos;
	int w;
	int h;
	int errcount=0;
	Point newp;
//on intialise la première section
	int wi=rand()%(widths/2) +4;
	int hi=rand()%(heights/2) +4;
	Point p(0,0);
	center=p;
	sect.push_back(Rectangle(p,wi*valpix,hi*valpix));
	n=1;
//on définie le nombre de section et d'obstacle a ajouter
	int nbrelief=rand()%4+ 2;
	int nbobst=rand()%5;
//on place les 2 sections contenant les portes
	for (int k=0; k<2;k++){
		contour();
		int cote=rand()%4*k;
		Point q=contourList[cote];
		Point r=contourList[cote+1];
		if (q.getX()-r.getX()!=0){
			val=(q.getX()-r.getX())/valpix;
			pos=rand()%val+p.getX()/valpix;
			w=rand()%4 +1;
			if (q.getY()>this->center.getY()){
				h=(heights/2)-q.getY();
				newp=Point(pos,q.getY()+valpix/(h/2));
				}
			else{
				h=(heights/2)+q.getY();
				newp=Point(pos,q.getY()-valpix/(h/2));
				}

			if (this->addsect(w*valpix,h*valpix,newp)==false){
				k--;}
			printf("test1");
			}
		else{
			val=(q.getY()-r.getY())/valpix;
			pos=rand()%val+p.getY()/valpix;
			h=rand()%4 +1;
			if (q.getX()>(center.getX())){
				w=(widths/2)-q.getX();
				newp=Point(q.getX()+valpix/(h/2),pos);
				}
			else{
				w=(widths/2)+q.getX();
				newp=Point(q.getX()-valpix/(h/2),pos);
				}

			if (this->addsect(w*valpix,h*valpix,newp)==false){
				k--;}
			}
	}
//on fait une boucle pour positionner les sections
	for (int k=0; k<nbrelief; k++){
		contour();
		int cote=rand()%4*k;
		Point q=contourList[cote];
		Point r=contourList[cote+1];
		if (q.getX()-r.getX()!=0){
			val=(q.getX()-r.getX())/valpix;
			pos=rand()%val+p.getX()/valpix;
			w=rand()%4 +1;
			h=rand()%4 +1;
			if (q.getX()>(center.getY())){
				newp=Point(pos,q.getY()+valpix/(h/2));
				}
			else{
				newp=Point(pos,q.getY()-valpix/(h/2));
				}
			if (this->addsect(w*valpix,h*valpix,newp)==false){
				k--;
				errcount++;}
			}
		else{
			val=(q.getY()-r.getY())/valpix;
			pos=rand()%val;
			w=rand()%4 +1;
			h=rand()%4 +1;
			if (q.getX()>this->center.getX()){
				newp=Point(q.getX()+valpix/(h/2),pos);
				}
			else{
				newp=Point(q.getX()-valpix/(h/2),pos);
				}
			if (this->addsect(w*valpix,h*valpix,newp)==false){
				k--;
				errcount++;}
			}
		if (errcount>5)
			{break;}

	}
}

//ajoute les obstacles en vérifiant qu'ils sont bien contenu dans la salle
bool Salles::addobst(int width, int height, Point pos){
	 bool ans=false;
	 for (Rectangle& r : sect){
	 	if (r.inrectangle(pos))
	 		{ans=true;
	 		obst.push_back(Obstacles(pos,width*valpix,height*valpix));
	 		return (ans);
	 		}
	 }
	return (ans);
}
//ajoute des sections pour ajouter des variations dans les salles, en érifiant que ces variations sont compatibles
bool Salles::addsect(int width, int height, Point pos){
	int maxX=widths/2;
	int minX=(widths/2)-widths;
	int maxY=heights/2;
	int minY=(heights/2)-heights;
	Point p1(pos.getX() -width*valpix/2, pos.getY()-height*valpix/2);
	Point p2(pos.getX() -width*valpix/2, pos.getY()+height*valpix/2);
	Point p3(pos.getX() +width*valpix/2, pos.getY()+height*valpix/2);
	Point p4(pos.getX() +width*valpix/2, pos.getY()-height*valpix/2);
	if (height<2 || width<2)	// Trop petit
		{return false;}
	if (pos.getX() -width*valpix/2<minX*valpix || pos.getX() +width*valpix/2>maxX*valpix || pos.getY() +height*valpix/2>maxY*valpix || pos.getY() -height*valpix/2<minY*valpix)	// En dehors du cadre
		{return false;}
	for (Rectangle& r : sect){	// superpose pas
		if (r.inrectangle(p1)||r.inrectangle(p2)||r.inrectangle(p3)||r.inrectangle(p4)){
			return false;
		}
	}
	for (Rectangle& r : sect){	// En contact avec un autre rectangle
		if (r.nearrectangle(p1)||r.nearrectangle(p2)||r.nearrectangle(p3)||r.nearrectangle(p4)){
			sect.push_back(Rectangle(pos,width*valpix,height*valpix));
			n=n+1;
			return true;
		}
	}
	return false;
}
//met a jour le centre de la salle pour la placer dans le plan
void Salles::setcenter(Point p){
	int varX=p.getX()-center.getX();
	int varY=p.getY()-center.getY();
	center=p;
	Point j,i;
	for (Rectangle& r : sect){
		j=r.getCenter();
		i.setX(j.getX()+varX);
		i.setY(j.getY()+varY);
		r.setcenter(i);
		}
	}
//ajoute les portes, en vérifiant quelles sont dans une zone accesible
bool Salles::setdoor(Point pos){
	Point p1(pos.getX(), pos.getY()-valpix/2);
	Point p2(pos.getX(), pos.getY()+valpix/2);
	Point p3(pos.getX() -valpix/2,pos.getY());
	Point p4(pos.getX() +valpix/2,pos.getY());
	if (pos.getX()!=(heights/2)*valpix && pos.getX()!=-(heights/2)*valpix && pos.getY()!=(widths/2)*valpix && pos.getY()!=-(widths/2)*valpix)
		{return false;}
	for (Rectangle& r : sect){
		if (r.inrectangle(p1)&&r.inrectangle(p2)){
			door.push_back(pos);
			return true;
			}
		else if (r.inrectangle(p3)&&r.inrectangle(p4)){
			door.push_back(pos);
			return true;
			}
		}
	return false;
	}

// Décomposition des rectangles en une liste de points
void Salles::getPoints() {
	for (int k=0; k<n; k++) {
		Rectangle r=sect[k];
	        // Tri selon x
	        Point p=r.getCenter();
	        float x1=p.getX() -r.getWidth()/2;
	        float x2=p.getX() +r.getWidth()/2;
	        float y1=p.getY()-r.getHeight()/2;
	        float y2=p.getY()+r.getHeight()/2;
	        pointMap[Point(x1,y1)]++;
	        pointMap[Point(x2,y1)]++;
	        pointMap[Point(x2,y2)]++;
	        pointMap[Point(x1,y2)]++;

	        // Tri selon y
	        pointMapInverted[Point(y1, x1)]++;
	        pointMapInverted[Point(y1, x2)]++;
	        pointMapInverted[Point(y2, x2)]++;
	        pointMapInverted[Point(y2, x1)]++;
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
	int maxX = widths/2;  // Taille max de la salle en x
	int minX=(widths/2)-widths;
	int maxY = heights/2;  // Taille max de la salle en y
	int minY=(heights/2)-heights;
	int i;

	// Calcul point de départ du contour
	Point actualPoint(minX,minY);
	while (pointMapInverted[actualPoint] != 1) {
		if (actualPoint.getX() < maxX) actualPoint.setX(actualPoint.getX()+1);
		else
            {actualPoint.setY(actualPoint.getY()+1);
            actualPoint.setX(minX)
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
