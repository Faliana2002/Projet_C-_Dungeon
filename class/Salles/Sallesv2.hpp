#ifndef SALLES_HPP
#define SALLES_HPP

#include "../point.hpp"
#include "Obstacles.hpp"
#include <vector>
#include <map>
class Salles {
//classe Salles, plusieurs chose à disposition, le center qui permettra de possitionner les sections par rapport à ce dernier, mais qui permettra aussi de positionner la salle dans le plan
// la liste de rectangle section va constituer l'espace de la salle, si on veut faire une grande pièce on crée un grand rectangle, puis on peut lui ajouter de plus petit rectangle pour ajouter du relief
// la liste d'obstacle permet d'empécher le joueur d'aller à certains endroit dans une salle, si l'on décide de faire une grande salle avec des pilliers par exemple, on peut modéliser les pilliers
// la liste de point door permettra de choisir le positionnement de portes par rapport à certaines salles, et donc d'organiser le trajet sur le plan
//l'entier n permettra de connaitre le nombre de section dont est constituer la salle
private:
	Point center;
	std::vector<Point> door;
	std::map<Point, int> pointMap;          // Map pour stocker les points avec leurs occurrences (l'entier associé)
	std::map<Point, int> pointMapInverted;  // Map inversée pour stocker les points avec leurs occurrences
	std::vector<Point> obst;            //liste des obstacles
	std::vector<Point> contourList;         // Points qui composent le contour
	int n;


public:
	Salles();
	//le constructeur de salle permettra d'initialiser les salles avec une section, pas d'obstacle, pas de portes et un placement
	Salles(const Point& c, float w, float h);
	Salles(const std::vector<Point> P){
		int t=l.size();
		float x;
		float y;
		for (int k=0; k<t; k++)
			{PointMap.push_back(P[k]);
			x=P[k].getX();
			y=P[k].getY();
			pointMapInverted.push_back(Point(y,x));
			}
	}
	//la fonction addobs prend en entrée des entiers et 1 point, les obstacles seront constitué de carré d'un certains nombres de pixels, pour faciliter l'affichage, il suffira donc d'indiquer ou on veut ajouter l'obstacle et de combien de portions il doit être constitué, si l'obstacle n'est pas positionnable, il renvoit false, sinon il renvoit true
	bool addobst(Point pos);
	//la fonction setcenter permet de positionner la salle
	void setcenter(Point p);
	//la ou les fonction setdoor permet de positionner la porte d'une salle
	bool setdoor(Point pos);
	//les fonctions get permette de récupérer les informations d'une salle
	Obstacles getobst(int i){return obst[i];};
	Rectangle getsect(int i){return sect[i];};
	Point getcenter(){return center;};
	Point getdoor(int i){return door[i];};
	int getnbsect(){return n;};
	void getPoints();       // Décomposition des rectangles en une liste de points          Trié selon x
	void printPoints();     // Affichage des map pointMap et pointMapInverted (terminal)    Trié selon y
	void contour();         // Calcul du contour de la salle
	void printContour();    // Affichage de contourList (terminal)
	bool Salles::insalles(Point pos);



};


#endif // SALLES_HPP
