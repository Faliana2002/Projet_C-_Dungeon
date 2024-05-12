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
	if (w%(w-1)==1){
        float x1=c.getX()+w/2+1/2;
        float x2=c.getX()-w/2-1/2;
	}
	else {
        float x1=c.getX()+w/2;
        float x2=c.getX()-w/2;
    }
	if (h%(h-1)==1){
        float y1=c.getY()+h/2+1/2;
        float y2=c.getY()-h/2-1/2;
	}
	else {
        float y1=c.getX()+h/2;
        float y2=c.getX()-h/2;
    }
	pointMap.push_back(Point(x1,y1));
	pointMap.push_back(Point(x1,y2));
	pointMap.push_back(Point(x2,y2));
	pointMap.push_back(Point(x2,y1));

	pointMapInverted.push_back(Point(y1,x1));
	pointMapInverted.push_back(Point(y2,x1));
	pointMapInverted.push_back(Point(y2,x2));
	pointMapInverted.push_back(Point(y1,x2));

	n=4;
}

Salles::Salles(){
//on intialise le random
	srand (time(NULL));
    float start=rand()%4;
    float x;
    float y;
    if (start==0){
        x=-widths/2;
        y=rand()%heights -heights/2;
    }
    else if (start==1){
        y=heights/2;
        x=rand()%widths -widths/2;
    }
    else if (start==2){
        x=widths/2;
        y=rand()%heights -heights/2;
    }
    else{
        x=-heights/2;
        y=rand()%widths -widths/2;
    }

}

bool Salles::insalles(Point pos){
    bool ans=false;
    float distyh=heights+1;
    float distyl=-heights-1;
    for (Point &P: pointMap){
        if (P.getX()==pos.getX()  && P.getY()-pos.getY()<distyh && P.getY()-pos.getY()>0)
            {distyh=P.getY()-pos.getY();}
        if (P.getX()==pos.getX()  && P.getY()-pos.getY()>distyl && P.getY()-pos.getY()<0)
            {distyl=P.getY()-pos.getY();}
    }
    if (distyh!=heights+1 && distyl!=-heights-1){
        ans=true;
    }
    return(ans);
}
//ajoute les obstacles de taille 1,1 en vérifiant qu'ils sont bien contenu dans la salle
bool Salles::addobst(Point pos){
	bool ans=false;
	float ymax=30,ymin=-30;
    for (Point &O: Obst){
        if (O==pos)
            {return (ans);}
	}
	ans=insalles(pos);
    obst.push_back(pos);
	return (ans);
}

//met a jour le centre de la salle pour la placer dans le plan
void Salles::setcenter(Point p){
	int varX=p.getX()-center.getX();
	int varY=p.getY()-center.getY();
	center=p;
	Point j,i;
	for (Point& P : pointMap){
		P.setX(P.getX()+varX);
		P.setX(P.getY()+varY);
		}
    for (Point& P : pointMapInverted){
		P.setX(P.getX()+varY);
		P.setX(P.getY()+varX);
		}
	}
//ajoute les portes, en vérifiant quelles sont dans une zone accesible
bool Salles::setdoor(Point pos){
	Point p1(pos.getX(), pos.getY());
	Point p2(pos.getX(), pos.getY()-1.0);
	Point p3(pos.getX() +1.0,pos.getY()-1.0);
	Point p4(pos.getX() +1.0,pos.getY());
	if (pos.getX()!=heights/2 && pos.getX()!=-heights/2 && pos.getY()!=widths/2 && pos.getY()!=-widths/2)
		{return false;}
	if (insalles(pos)==true){
        door.push_back(pos);
        return true;
        }
	return false;
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
	int maxX = (widths/2)*valpix;  // Taille max de la salle en x
	int minX=((widths/2)-widths)*valpix;
	int maxY = (heights/2)*valpix;  // Taille max de la salle en y
	int minY=((heights/2)-heights)*valpix;
	int i;
    getPoints();
	// Calcul point de départ du contour
	Point actualPoint(minX,minY);
	while (pointMapInverted[actualPoint] != 1) {
		if (actualPoint.getX() < maxX) actualPoint.setX(actualPoint.getX()+1);
		else
            {actualPoint.setY(actualPoint.getY()+1);
            actualPoint.setX(minX);}
	}
	contourList.push_back(actualPoint); // Ajout du point

	int actualX = actualPoint.getX(), actualY = actualPoint.getY();
	Point newPoint(1,1);

	while (newPoint != actualPoint) {
		// Horizontal
		i = 1;

		// Calcul du prochain point selon x
		while ((pointMapInverted[Point(actualY, actualX + i)] < 1) && (pointMapInverted[Point(actualY, actualX - i)] < 1) && i < maxX*2) {
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
		while (pointMap[Point(actualX, actualY+i)] != 1 && (pointMap[Point(actualX, actualY-i)] != 1 || actualY-i<0) && i < maxY*2) {
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
