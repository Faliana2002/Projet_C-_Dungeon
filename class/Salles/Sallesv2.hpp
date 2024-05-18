#ifndef SALLES_HPP
#define SALLES_HPP

#include "../point.hpp"
#include "Obstacles.hpp"
#include <vector>
#include <map>
#include <SFML/Graphics.hpp>

extern std::string reference;

class Salles {
//classe Salles, plusieurs chose à disposition, le center qui permettra de possitionner les sections par rapport à ce dernier, mais qui permettra aussi de positionner la salle dans le plan
// la liste de rectangle section va constituer l'espace de la salle, si on veut faire une grande pièce on crée un grand rectangle, puis on peut lui ajouter de plus petit rectangle pour ajouter du relief
// la liste d'obstacle permet d'empécher le joueur d'aller à certains endroit dans une salle, si l'on décide de faire une grande salle avec des pilliers par exemple, on peut modéliser les pilliers
// la liste de point door permettra de choisir le positionnement de portes par rapport à certaines salles, et donc d'organiser le trajet sur le plan
//l'entier n permettra de connaitre le nombre de section dont est constituer la salle
private:
	std::vector<Point> door;
	std::map<Point, int> pointMap;          // Map pour stocker les points avec leurs occurrences (l'entier associé)
	std::map<Point, int> pointMapInverted;  // Map inversée pour stocker les points avec leurs occurrences
	std::vector<Point> obst;            //liste des obstacles
	std::vector<Point> contourList;         // Points qui composent le contour
	int n;
    sf::Texture texture[8];
    sf::Texture wall[5];
    sf::Texture wallsection[8];

public:
    sf::Sprite sprite[26*14];
    sf::Sprite sprite2[26*14];
	Salles();
	//le constructeur de salle permettra d'initialiser les salles avec une section, pas d'obstacle, pas de portes et un placement
	Salles(const Point& c, float w, float h);
	Salles(const std::vector<Point> P){
		int t=P.size();
		float x;
		float y;
		for (int k=0; k<t; k++)
			{pointMap[P[k]]++;
			x=P[k].getX();
			y=P[k].getY();
			pointMapInverted[Point(y,x)]++;
			}
	}
	//la fonction addobs prend en entrée des entiers et 1 point, les obstacles seront constitué de carré d'un certains nombres de pixels, pour faciliter l'affichage, il suffira donc d'indiquer ou on veut ajouter l'obstacle et de combien de portions il doit être constitué, si l'obstacle n'est pas positionnable, il renvoit false, sinon il renvoit true
	bool addobst(Point pos);
	//la ou les fonction setdoor permet de positionner la porte d'une salle
	bool setdoor(Point pos);
	//les fonctions get permette de récupérer les informations d'une salle
	Point getobst(int i){return obst[i];};
	Point getsect(int i){return contourList[i];};
	Point getdoor(int i){return door[i];};
	int getnbsect(){return n;};
	//void getPoints();       // Décomposition des rectangles en une liste de points          Trié selon x
	void printPoints();     // Affichage des map pointMap et pointMapInverted (terminal)    Trié selon y
	//void contour();         // Calcul du contour de la salle
	void printContour();    // Affichage de contourList (terminal)
	bool insalles(Point pos);
    void init_texture();

};


#endif // SALLES_HPP
